#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h"  
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"   
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

int main(void)
{
  HAL_Init();
	SystemClock_Config();
	GPIO_init();
	//������ʼ����
  xTaskCreate((TaskFunction_t )start_task,            //������
              (const char*    )"start_task",          //��������
              (uint16_t       )START_STK_SIZE,        //�����ջ��С
              (void*          )NULL,                  //���ݸ��������Ĳ���
              (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
              (TaskHandle_t*  )&StartTask_Handler);   //������              
  vTaskStartScheduler();          //�����������
	
//  while (1)
//  {
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1));
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5));
//		HAL_Delay(1000);
//  }
}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
