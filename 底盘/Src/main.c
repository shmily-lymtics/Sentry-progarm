/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "BSP.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
IWDG_HandleTypeDef iwdg_handler;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void MX_FREERTOS_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */



	HAL_Init();
  
   iwdg_handler.Instance=IWDG;
	 iwdg_handler.Init.Prescaler=IWDG_PRESCALER_64;  
	 iwdg_handler.Init.Reload=1500;
	 HAL_IWDG_Init(&iwdg_handler);
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
	taskENTER_CRITICAL();  //进入临界段
  /* USER CODE BEGIN 2 */
	BSP_Init();
	MX_FREERTOS_Init();
	taskEXIT_CRITICAL();	//退出临界段
  /* USER CODE END 2 */
  /* Call init function for freertos objects (in freertos.c) */
  
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin); //Red
		
//		TIM5_PWM_Init(1950,1950);//1850
//	  HAL_Delay(1500);
////	  TIM5_PWM_Init(50,50);//1950
////		HAL_Delay(1000);

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
//    HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
//		
//		osDelay(100);

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}
/*测速模块*/
#define GunLength 0.05
#define MicroTime 0.000005

uint32_t Micro_Tick; //单位0.005ms
uint32_t Photoelectric_gate1 = 0,Photoelectric_gate2 = 0;
uint16_t gate1_counter = 0,gate2_counter = 0;
static float Golf_speed = 0;
int16_t Golf_counter = 0; 
/*测速down*/

void testTask(void const * argument)
{
	
//	char InfoBuffer[100];

	static double micro_timenow = 0;
	static double micro_timelast = 0;
	static double micro_time = 0;
	int16_t angle[4];	
	osDelay(200);//延时200ms
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
	
	
	for(;;)
	{ 				
		static uint16_t counter_last;
		
		RefreshTaskOutLineTime(testTask_ON);
//		if(gate1_counter == gate2_counter)
//		{
//			Golf_speed = (float)(GunLength / MicroTime / (Photoelectric_gate1 - Photoelectric_gate2));

//			if(counter_last != gate1_counter)
//			{
//				printf("Golf_speed = %4f\n",Golf_speed);
//			}
//			counter_last = gate1_counter;
//		}
//		vTaskGetRunTimeStats(InfoBuffer);
//		printf("%s\r\n",InfoBuffer);
//		vTaskList(InfoBuffer);
//		printf("%s\n\r",InfoBuffer);
      HAL_IWDG_Refresh(&iwdg_handler);
		  int16_t  *ptr = angle; //初始化指针
			angle[0]	= (yaw_get.total_angle);
			angle[1]	= (-imu_data.gz);
			angle[2]	= ((int16_t)pid_yaw.pos_out);
			angle[3]	= (int16_t)(-pid_yaw_jy901_spd.pos_out);
			/*用虚拟示波器，发送数据*/
//			vcan_sendware((uint8_t *)ptr,4*sizeof(angle[0]));
//		  vcan_sendware((uint8_t *)ptr,4*sizeof(angle[1]));
//		  vcan_sendware((uint8_t *)ptr,4*sizeof(angle[2]));
//		  vcan_sendware((uint8_t *)ptr,4*sizeof(angle[3]));
		
//		printf("  yaw_get.total_angle=%d \n\t",yaw_get.total_angle);
//	  printf("  -imu_data.gz=%d \n\t",-imu_data.gz);
//		printf("  pid_yaw.pos_out=%f \n\t",pid_yaw.pos_out);
//	  printf("  -pid_yaw_jy901_spd.pos_out=%f \n\t",-pid_yaw_jy901_spd.pos_out);
//		
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin); //Red
		
		osDelayUntil(&xLastWakeTime,100);
	}
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
	while(1) 
  {

  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
//	printf("FILE:%s,LINE:%d\n\r",file,line);
	for(;;)
	{	
#if BoardNew
//		HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_1); 
#endif
		HAL_Delay(500);
	}	 //断言，闪烁LEDGRE_H（新板子）

	
}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
