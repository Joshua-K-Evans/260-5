/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int password_index = 0, num_attempts = 0;
int current_password[10], temporary_password[10];
bool saving_password = false, entering_password = false, locked = false, alarm = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
uint8_t keypad_decode();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // check to see if alarm is true and set flashing light
  	  if(alarm == true){
  		HAL_GPIO_TogglePin(R_LED_GPIO_Port, R_LED_Pin); //makes red led blink on and off
  		HAL_Delay(100);//delays the blinking so it's visible
  	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, KEY_LED_Pin|R_LED_Pin|Y_LED_Pin|G_LED_Pin
                          |B_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : DISARM_BUTTON_Pin */
  GPIO_InitStruct.Pin = DISARM_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DISARM_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DATA_AVAILABLE_Pin */
  GPIO_InitStruct.Pin = DATA_AVAILABLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DATA_AVAILABLE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DATA0_Pin DATA1_Pin DATA2_Pin */
  GPIO_InitStruct.Pin = DATA0_Pin|DATA1_Pin|DATA2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY_LED_Pin R_LED_Pin Y_LED_Pin G_LED_Pin
                           B_LED_Pin */
  GPIO_InitStruct.Pin = KEY_LED_Pin|R_LED_Pin|Y_LED_Pin|G_LED_Pin
                          |B_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DATA3_Pin */
  GPIO_InitStruct.Pin = DATA3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DATA3_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Make sure to update comments so they don't say things like "add code here"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	// Check if the interrupt was for Disarm Button
	if (GPIO_Pin == DISARM_BUTTON_Pin) {

		// Reset system
		alarm = false;
		locked = false;
		entering_password = false;
		saving_password = false;
		num_attempts = 0;
		password_index = 0;

		// Turn off lights
		HAL_GPIO_WritePin(R_LED_GPIO_Port, R_LED_Pin,   0); // turn off R_LED
		HAL_GPIO_WritePin(Y_LED_GPIO_Port, Y_LED_Pin,   0); // turn off Y_LED
		HAL_GPIO_WritePin(G_LED_GPIO_Port, G_LED_Pin,   0); // turn off G_LED
		HAL_GPIO_WritePin(B_LED_GPIO_Port, B_LED_Pin,   0); // turn off B_LED
	}

	// Check if the interrupt was for Data Available Pin
	if (HAL_GPIO_ReadPin(DATA_AVAILABLE_GPIO_Port, DATA_AVAILABLE_Pin) != 0){

		// Turn on LED2 to show key press detected
		HAL_GPIO_WritePin(KEY_LED_GPIO_Port, KEY_LED_Pin,   1); // add code here to turn on the KEY_LED (LED2)

		// Read data
		uint8_t key = keypad_decode();  // determine which key was pressed

		if (!alarm) {

			// Based on what key was pressed, do something (each case)
			switch (key) {

			case 0xA: // button "A" was pressed

				if (locked == false) { // if not already locked

					// Clear temporary password
					for (int i = 0; i < 10; i++){
						temporary_password[i] = -1;
					}

					// Change status (user is saving a new password)
					saving_password = true;
					password_index = 0;  // reset password index

					// Turn off indicator lights while entering new password
							HAL_GPIO_WritePin(R_LED_GPIO_Port, R_LED_Pin,   0); // turn off R_LED
							HAL_GPIO_WritePin(Y_LED_GPIO_Port, Y_LED_Pin,   0); // turn off Y_LED
							HAL_GPIO_WritePin(G_LED_GPIO_Port, G_LED_Pin,   0); // turn off G_LED
							HAL_GPIO_WritePin(B_LED_GPIO_Port, B_LED_Pin,   0); // turn off B_LED
						}

				break; // end case 0xA

			case 0xB: // button "B" was pressed

				if (locked == false) { // if not already locked

					// Store temp password as current password
					for (int i = 0; i < 10; i++){
						current_password[i] = temporary_password[i];
					}

					// Turn on blue (new password successfully saved - system is locked)
					HAL_GPIO_WritePin(B_LED_GPIO_Port, B_LED_Pin,   1); //to turn on B_LED

					// Change status (user is finished saving a new password)
					saving_password = false;
					locked = true;
				}

				break; // end case 0xB

			case 0xC: // button "C" was pressed

				// Clear temporary password
				for (int i = 0; i < 10; i++){
					temporary_password[i] = -1;
				}

				// Change status (user is entering password to check)
				entering_password = true;
				password_index = 0; // reset password index

				// Turn off password indicator lights while checking new password
							HAL_GPIO_WritePin(R_LED_GPIO_Port, R_LED_Pin,   0); // turn off R_LED
							HAL_GPIO_WritePin(Y_LED_GPIO_Port, Y_LED_Pin,   0); // turn off Y_LED
							HAL_GPIO_WritePin(G_LED_GPIO_Port, G_LED_Pin,   0); // turn off G_LED

				break; // end case 0xC

			case 0xD: // button "D" was pressed

				if (entering_password) { // if password was being entered

					// Change status (user is finished entering password to check)
					entering_password = false;
					password_index = 0;
					locked = false;

					// Compare temporary password with current password
					for (int i = 0; i < 10; i++) {
						if (current_password[i] != temporary_password[i]){
							locked = true; // digit is incorrect, keep locked
						}
					}

					// If password is correct
					if (locked == false) {

						// Reset attempt count
						num_attempts = 0;

						// Turn on green (correct password entered)
						HAL_GPIO_WritePin(G_LED_GPIO_Port, G_LED_Pin,   1); // turn on G_LED

						// Turn off blue (system is unlocked)
						HAL_GPIO_WritePin(B_LED_GPIO_Port, B_LED_Pin,   0); // turn off B_LED

					} else { // password is incorrect

						// Increment attempt count
						num_attempts++;

						// if 3 wrong attempts
						if (num_attempts >= 3) {

							// set alarm to true to trigger rel led flashing in while loop
							alarm = true;


						} else {

							// Turn on yellow (incorrect password entered)
							HAL_GPIO_WritePin(Y_LED_GPIO_Port, Y_LED_Pin,   1); // turn on Y_LED

						}
					}

				}

				break; // end case 0xD

			case 0xE: // key E (*) does nothing
				break;

			case 0xF: // key F (#) does nothing
				break;

			default: // this means a number was pressed

				// if current status == storing new password
				if (saving_password) {

					if (password_index < 10) {

						// store digit into temporary password
						temporary_password[password_index++] = key;

						// if max digits reached, finish and store
						if (password_index == 10) {

							// Store new password
							for (int i = 0; i < 10; i++){
								current_password[i] = temporary_password[i];
							}

							// Turn on blue (new password successfully saved - system is locked)
							HAL_GPIO_WritePin(B_LED_GPIO_Port, B_LED_Pin,   1); //turn on B_LED

							// Change status
							saving_password = false;
							locked = true;
						}
					}
				}

				// if status == entering password to check
				else if (entering_password) {

					// store digit into temporary password
					if (password_index < 10){
						temporary_password[password_index++] = key; // store digit
					}
				}
				break; // end default case
			}
		}

		// wait for user to release key, then turn off LED2
		while (HAL_GPIO_ReadPin(DATA_AVAILABLE_GPIO_Port, DATA_AVAILABLE_Pin) == GPIO_PIN_SET);
		HAL_GPIO_WritePin(KEY_LED_GPIO_Port, KEY_LED_Pin,   0); //turn off the KEY_LED (LED2)

	}

}

// This function reads the four data pins from the keypad encoder and maps them to the key value
unsigned char keypad_decode() {
	unsigned char key = 0x0;
	unsigned char data = 0b0000;

	// read the data pins and combine into the 4-bit value: D3_D2_D1_D0
	data = HAL_GPIO_ReadPin(DATA0_GPIO_Port, DATA0_Pin)<<0 |
		   HAL_GPIO_ReadPin(DATA1_GPIO_Port, DATA1_Pin)<<1 |
		   HAL_GPIO_ReadPin(DATA2_GPIO_Port, DATA2_Pin)<<2 |
		   HAL_GPIO_ReadPin(DATA3_GPIO_Port, DATA3_Pin)<<3;//  reads D3, D2, D1, and D0 and then combine them into a 4-bit number: D3_D2_D1_D0

	// The key encoder gives the following "data" values:
	// 0 1 2 3
	// 4 5 6 7
	// 8 9 A B
	// C D E F

	// The following switch statement re-maps it to these "key" names:
	// 1 2 3 A
	// 4 5 6 B
	// 7 8 9 C
	// E 0 F D, where E is * and F is #

   // Finish this switch statement to remap the "data" to the correct "key"
	switch (data) {
      case 0x0:
         key = 0x1;
         break;
      case 0x1:
         key = 0x2;
         break;
      case 0x2:
         key = 0x3;
         break;
      case 0x3:
         key = 0xA;
         break;
      case 0x4:
         key = 0x4;
         break;
      case 0x5:
         key = 0x5;
         break;
      case 0x6:
         key = 0x6;
         break;
      case 0x7:
         key = 0xB;
         break;
      case 0x8:
         key = 0x7;
         break;
      case 0x9:
         key = 0x8;
         break;
      case 0xA:
         key = 0x9;
         break;
      case 0xB:
         key = 0xC;
         break;
      case 0xC:
         key = 0xE;
         break;
      case 0xD:
         key = 0x0;
         break;
      case 0xE:
         key = 0xF;
         break;
      case 0xF:
         key = 0xD;
         break;
	}

	return key;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
