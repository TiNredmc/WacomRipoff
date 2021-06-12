/* Wacom I2C digitizer w9013 driver code, ported from Linux mainline kernel driver 
 * Ported by TinLethax 2021/06/07 +7
 */

#include "main.h"
#include "w9013.h"
#include "usb_device.h"
#include <stdint.h>
#include <stdbool.h>

struct wacom_i2c wacom_i2c;
extern USBD_HandleTypeDef hUsbDeviceFS;
extern uint8_t USBD_HID_SendReport(USBD_HandleTypeDef *pdev, uint8_t *report, uint16_t len);
uint8_t hid_report[8]={2,0,0,0,0,0,0,0};// store HID report for sending via usb

void wacom_query_device(I2C_HandleTypeDef *hi2c, struct wacom_features *features)
{

	uint8_t cmd1[4] = { WACOM_CMD_QUERY0, WACOM_CMD_QUERY1,
			WACOM_CMD_QUERY2, WACOM_CMD_QUERY3 };
	uint8_t cmd2[2] = { WACOM_CMD_THROW0, WACOM_CMD_THROW1 };
	uint8_t data[WACOM_QUERY_SIZE];

	HAL_I2C_Master_Transmit(hi2c, WACOM_ADDR, cmd1, sizeof(cmd1), 150);// send the query cmd

	HAL_I2C_Master_Transmit(hi2c, WACOM_ADDR, cmd2, sizeof(cmd2), 150);// send the throw (Unknown reason)

	HAL_I2C_Master_Receive(hi2c, WACOM_ADDR, data, sizeof(data), 150);// receive the info properties of Digitizer chip (W9013)
 
	//Store the necessary data for HID
	features->x_max = data[3] | data[4] << 8;
	features->y_max = data[5] | data[6] << 8;
	features->pressure_max = data[11] | data[12] << 8;
	features->fw_version = data[13] | data[14] << 8;

}

void wacom_i2c_irq()
{
	uint8_t *data = wacom_i2c.data;
//	unsigned int x, y, pressure;
//	unsigned char tsw, f1, f2, ers;

	// receive data from w9013
	do{
	HAL_I2C_Master_Receive(wacom_i2c.hi2c, WACOM_ADDR, data, 19, 150);
	}while(HAL_GPIO_ReadPin(wacom_i2c.GPIOx, 0x0020) == 0);
	HAL_GPIO_WritePin(wacom_i2c.GPIOxLED, wacom_i2c.irq, GPIO_PIN_SET);

/*
	tsw = data[3] & 0x01;
	ers = data[3] & 0x04;
	f1 = data[3] & 0x02;
	f2 = data[3] & 0x10;
	x = le16_to_cpup((__le16 *)&data[4]);
	y = le16_to_cpup((__le16 *)&data[6]);
	pressure = le16_to_cpup((__le16 *)&data[8]);

	wac_i2c->prox = data[3] & 0x20;*/

	// Store HID report packet before sending to host
	// hid_report[0] = (tip << 0) | (eraser << 1) | (f1 << 2) | (f2 << 3) | (prox << 4);
	hid_report[1] = ((data[3] & 0x01 ? 1 : 0) << 4) | ((data[3] & 0x04 ? 1 : 0) << 3) | ((data[3] & 0x02 ? 1 : 0) << 2) | ((data[3] & 0x10 ? 1 : 0) << 1) | ((data[3] & 0x20 ? 1 : 0) << 0);
	hid_report[1] |= ((data[3] & 0x0C ? 1 : 0) << 3);// Also report the eraser tip

    // hid_report[1] and hid_report[2] is for X position
	hid_report[2] = data[6];// Send lower byte first
	hid_report[3] = data[7];// Then send higher byte

    // hid_report[3] and hid_report[4] is for Y position
	hid_report[4] = data[4];// Send lower byte first
	hid_report[5] = data[5];// Then send higher byte

    // hid_report[5] and hid_report[6] is for pressure
	hid_report[6] = data[8];// Send lower byte first
	hid_report[7] = data[9];// Then send higher byte

// TODO : if the array copy like that is sending correct HID data, Then use memcpy instead

	// Send USB report
	USBD_HID_SendReport(&hUsbDeviceFS, hid_report, sizeof(hid_report));
	//printf("Wacom Raw Read %x , HID Raw Send %x\n", data[3], hid_report[1]);
	// DONE
	HAL_GPIO_WritePin(wacom_i2c.GPIOxLED, wacom_i2c.irq, GPIO_PIN_RESET);
}


void wacom_i2c_probe(I2C_HandleTypeDef *hi2c, GPIO_TypeDef* GPIOx, uint16_t RST_pin, GPIO_TypeDef* GPIOxLED, uint16_t IRQ_stat_pin)
{
	struct wacom_features features = { 0 };

	wacom_i2c.hi2c = hi2c;// Get the typedef of I2C
	wacom_i2c.GPIOxLED = GPIOxLED;// Get the GPIO port
	wacom_i2c.irq = IRQ_stat_pin;// LED indicate Interrupt is happening
	wacom_i2c.GPIOx = GPIOx;// Get the reset pin GPIO
	wacom_i2c.rst = RST_pin;// Reset pin


	// Reset the w9013 before initializing
	HAL_GPIO_WritePin(wacom_i2c.GPIOx, wacom_i2c.rst, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(wacom_i2c.GPIOx, wacom_i2c.rst, GPIO_PIN_SET);
	// Init
	wacom_query_device(wacom_i2c.hi2c, &features);

}
