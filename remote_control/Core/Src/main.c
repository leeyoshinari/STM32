/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <protocol.h>
#include "string.h"
#include "stdio.h"
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
// ����ģ���ģʽ��ѧ�� - 0  ���� - 1
int codeFlag = 1;
// �յ���������ʱ�䣬��λ s
int runningTime = 480;
// �յ���ͣ�����´ο�����ʱ�䣬��λ s
int waitTime = 3600;
// �յ�ÿ������������ʱ����24Сʱ�ƣ�ʱ�ֱ�ʾ�� 08:30��ʾ����8Сʱ30���ӡ�
// ��Ƭ��������10s���յ���ʼ�����ԵĿ�����ͣ����ÿ������ʱ��Ϊ runningTime + waitTime��
// ֱ�� interval ��ֹͣ���������У�24Сʱ���ٿ�ʼ���������С������Ƭ�����ػ������Ͽ�ʵ��ÿ�������Զ����ƿյ����С�
char interval[6] = "08:30";

//�ڲ�����(��1��)���յ�������
uint8_t SendCode1[] = "68 08 00 FF 12 00 11 16";
//�ڲ�����(��2��)���յ��ػ���
uint8_t SendCode2[] = "68 08 00 FF 12 01 12 16";
//�ڲ�����(��3��)
//uint8_t SendCode3[] = "68 08 00 FF 12 02 13 16";
//�ڲ�����(��4��)
//uint8_t SendCode4[] = "68 08 00 FF 12 03 14 16";
//�ڲ�����(��5��)
//uint8_t SendCode5[] = "68 08 00 FF 12 04 15 16";
//,�ڲ�����(��6��)
//uint8_t SendCode6[] = "68 08 00 FF 12 05 16 16";
//�ڲ�����(��7��)
//uint8_t SendCode7[] = "68 08 00 FF 12 06 17 16";


// -------����Ĳ�Ҫ�޸� ----------
// ���ڽ��ջ���
uint8_t uart1_RxBuff[255];
uint8_t uart2_RxBuff[255];
RTC_TimeTypeDef currentTime = {0};
// �������� - 1; ͣ���ȴ� - 0
int runFlag = 1;
// ��ʱ���жϺ�ļ�ʱʱ�䣬��λ s
int systemRunningTime = 0;
int counter = 0;
char t_buff[6];
// �յ�ÿ�������Կ�ʼ����ʱ�䣬24Сʱ�ƣ�ʱ��
char startTime[6] = "00:01";
int isInterval = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
	void IR_Send_Code(uint8_t *sendCode);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1, uart1_RxBuff, 255);
	HAL_UART_Receive_IT(&huart2, uart2_RxBuff, 255);
	if(codeFlag == 1)
	{
		HAL_TIM_Base_Start_IT(&htim2);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// ��ʱ���жϻص�����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	counter ++;
	if(counter == 20)	// ʱ��Ƶ��Ϊ20Hz����1�����20�Σ�ÿ��0.05��
	{
		counter = 0;
		systemRunningTime ++;
		HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
		sprintf(t_buff, "%02d:%02d", currentTime.Hours, currentTime.Minutes);
		if(isInterval == 1 && runFlag == 1 && systemRunningTime >= runningTime)
		{
			systemRunningTime = 0;
			runFlag = 0;
			uint16_t codeLen = IR_Send_Pack(SendCode2, 1);
			HAL_UART_Transmit_IT(&huart1, SendCode2, codeLen);
		}
		if(isInterval == 1 && runFlag == 0 && systemRunningTime >= waitTime)
		{
			systemRunningTime = 0;
			runFlag = 1;
			uint16_t codeLen = IR_Send_Pack(SendCode1, 0);
			HAL_UART_Transmit_IT(&huart1, SendCode1, codeLen);
		}
		if(isInterval == 1 && strcmp(t_buff, interval) == 0)
		{
			isInterval = 0;
			systemRunningTime = 0;
			runFlag = 0;
			uint16_t codeLen = IR_Send_Pack(SendCode2, 1);
			HAL_UART_Transmit_IT(&huart1, SendCode2, codeLen);
		}
		if(isInterval == 0 && strcmp(t_buff, startTime) == 0)
		{
			isInterval = 1;
			runFlag = 1;
			systemRunningTime = 0;
			if(codeFlag == 1)
			{
				uint16_t codeLen = IR_Send_Pack(SendCode1, 0);
				HAL_UART_Transmit_IT(&huart1, SendCode1, codeLen);
			}
		}
		if(isInterval == 0 && systemRunningTime > 7200)
		{
			systemRunningTime = 0;	// ��ֹ���
		}
	}
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
