#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h"  
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"   
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

int main(void)
{
  HAL_Init();
	SystemClock_Config();
	GPIO_init();
	//创建开始任务
  xTaskCreate((TaskFunction_t )start_task,            //任务函数
              (const char*    )"start_task",          //任务名称
              (uint16_t       )START_STK_SIZE,        //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )START_TASK_PRIO,       //任务优先级
              (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
  vTaskStartScheduler();          //开启任务调度
	
//  while (1)
//  {
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1));
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5));
//		HAL_Delay(1000);
//  }
}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
