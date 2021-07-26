/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
// TOTAL REPORT SIZE IS 93
/*
__ALIGN_BEGIN static uint8_t HID_PEN_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END = {
0x05, 0x0D,								// Usage page : Digitizer
0x09, 0x02,								// Usage : Pen
0xA1, 0x01,								// Collection : Application
	0x85, 0x02,							// Report ID for pen (report no 0x02).
	0x09, 0x20,							// Usage : Stylus
	0xA1, 0x00,							// Collection : Physical
		// Boolean 1 and 0 (1 means present, 0 means not present).
		0x09, 0x42,						// Usage : Pen Tip
		0x09, 0x3C,						// Usage : Invert (Eraser Tip)
		0x09, 0x44,						// Usage : 1st Barrel Button
		0x09, 0x45,						// Usage : Eraser Tip
		0x09, 0x5A,						// Usage : 2nd Barrel Button
		0x09, 0x32,						// Usage : pen is in-range
		0x25, 0x01,						// Logical Max is 1
		0x15, 0x00,						// Logical Min is 0
		0x75, 0x05,						// Report size is 6 usages
		0x95, 0x01,						// Report count is 1
		0x81, 0x02,						// Input (Data, Var, Abs)
		// fill all remain bit to make it byte align (8n).
		0x75, 0x01,						// 1 Null usage
		0x95, 0x02,						// fills 2 bits
		0x81, 0x83,						// Input (Const, Var, Abs)

		// Usage Page Generic Desktop will report X,Y coordinate and Pen pressure
		0x05, 0x01,						// Usage Page : Generic Desktop

		0x09, 0x30,						// Usage : X axis
		0x26, 0xB0, 0x53,				// Logical Max is 21424 (according to my w9013 feature report)
		0x15, 0x00,						// Logical Min is 0
		0x55, 0x0d,						// Unit Exponent (-3)
		0x65, 0x11,						// Unit (cm)
		0x75, 0x10,						// Report Size 16 (16bit - 2bytes)
		0x95, 0x01,						// Report count is 1
		0x81, 0x02,						// Input (Data, Var, Abs)

		0x09, 0x31,						// Usage : Y axis
		0x26, 0x4E, 0x34,				// Logical Max is 13390 (according to my w9013 feature report)
		0x15, 0x00,						// Logical Min is 0
		0x55, 0x0d,						// Unit Exponent (-3)
		0x65, 0x11,						// Unit (cm)
		0x75, 0x10,						// Report Size 16 (16bit - 2bytes)
		0x95, 0x01,						// Report count is 1
		0x81, 0x02,						// Input (Data, Var, Abs)

		// Pen tip pressure require Digitizer as a Usage page
		0x05, 0x0D,						// Usage Page : Digitizer
		0x09, 0x30,						// Usage : Tip Pressure
		0x26, 0xFF, 0x07,				// Logical Max is 2047 (according to my w9013 capability, This is Wacom EMR)
		0x15, 0x00,						// Logical Min is  0
		0x75, 0x10,						// Report Size 16 (16bit - 2bytes)
		0x95, 0x01,						// Report count is 1
		0x81, 0x02,						// Input (Data, Var, Abs)

	0xC0,								// End Collection (Phy)
0xC0									// End Collection (App)
};*/

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOF
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOF
#define INIT_STAT_Pin GPIO_PIN_8
#define INIT_STAT_GPIO_Port GPIOE
#define IRQ_STAT_Pin GPIO_PIN_13
#define IRQ_STAT_GPIO_Port GPIOE
#define DM_Pin GPIO_PIN_11
#define DM_GPIO_Port GPIOA
#define DP_Pin GPIO_PIN_12
#define DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define PAD_RST_Pin GPIO_PIN_4
#define PAD_RST_GPIO_Port GPIOB
#define IRQ0_Pin GPIO_PIN_5
#define IRQ0_GPIO_Port GPIOB
#define IRQ0_EXTI_IRQn EXTI9_5_IRQn
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
