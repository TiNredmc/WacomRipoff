/* Wacom I2C digitizer w9013 driver code, ported from Linux mainline kernel driver
 * Ported by TinLethax 2021/06/07 +7
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef INC_W9013_H_
#define INC_W9013_H_

#define WACOM_ADDR			0x09 << 1// Wacom i2c address (7-bit)

#define WACOM_CMD_QUERY0	0x04
#define WACOM_CMD_QUERY1	0x00
#define WACOM_CMD_QUERY2	0x33
#define WACOM_CMD_QUERY3	0x02
#define WACOM_CMD_THROW0	0x05
#define WACOM_CMD_THROW1	0x00
#define WACOM_QUERY_SIZE	19

struct wacom_features {
	int x_max;
	int y_max;
	int pressure_max;
	char fw_version;
};

struct wacom_i2c {
	I2C_HandleTypeDef *hi2c;
	GPIO_TypeDef* GPIOx;
	GPIO_TypeDef* GPIOxLED;
	uint8_t data[WACOM_QUERY_SIZE];
	uint16_t rst,irq;
//	bool prox;// pen is in-range
};


void wacom_query_device(I2C_HandleTypeDef *hi2c, struct wacom_features *features);// digitizer feature query
void wacom_i2c_irq();// IRQ handling the incoming HID cata from w9013
void wacom_i2c_probe(I2C_HandleTypeDef *hi2c, GPIO_TypeDef* GPIOx, uint16_t RST_pin, GPIO_TypeDef* GPIOxLED, uint16_t IRQ_stat_pin);// i2c probe

#endif /* INC_W9013_H_ */
