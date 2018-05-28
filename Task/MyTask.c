#include "MyTask.h"
#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h" 
#include "stm32f1xx.h" 
extern TaskHandle_t StartTask_Handler;
//任务优先级
#define KEY_TASK_PRIO		2
//任务堆栈大小	
#define KEY_STK_SIZE 		128  
//任务句柄
TaskHandle_t KeyTask_Handler;
//任务函数
void key_task(void *pvParameters);

//任务优先级
#define TASK1_TASK_PRIO		3
//任务堆栈大小	
#define TASK1_STK_SIZE 		128  
//任务句柄
TaskHandle_t Task1Task_Handler;
//任务函数
void task1_task(void *pvParameters);

//任务优先级
#define TASK2_TASK_PRIO		4
//任务堆栈大小	
#define TASK2_STK_SIZE 		128  
//任务句柄
TaskHandle_t Task2Task_Handler;
//任务函数
void task2_task(void *pvParameters);
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	//创建KEY任务
	xTaskCreate((TaskFunction_t )key_task,             
                (const char*    )"key_task",           
                (uint16_t       )KEY_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )KEY_TASK_PRIO,        
                (TaskHandle_t*  )&KeyTask_Handler);  
    //创建TASK1任务
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
    //创建TASK2任务
    xTaskCreate((TaskFunction_t )task2_task,     
                (const char*    )"task2_task",   
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_TASK_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler); 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}
//key任务函数
void key_task(void *pvParameters)
{
	//u8 key,statflag=0;
	while(1)
	{
//		key=KEY_Scan(0);
//		switch(key)
//		{
//			case WKUP_PRES:
//				statflag=!statflag;
//				if(statflag==1)
//				{
//					vTaskSuspend(Task1Task_Handler);//挂起任务
//					printf("挂起任务1的运行!\r\n");
//				}
//				else if(statflag==0)
//				{
//					vTaskResume(Task1Task_Handler);	//恢复任务1
//					printf("恢复任务1的运行!\r\n");
//				}		
//				break;
//			case KEY1_PRES:
//				vTaskSuspend(Task2Task_Handler);//挂起任务2
//				printf("挂起任务2的运行!\r\n");
//				break;
//		}
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4));
		vTaskDelay(200);			//延时10ms 
	}
}

//task1任务函数
void task1_task(void *pvParameters)
{
	u8 task1_num=0;
	while(1)
	{
		task1_num++;	//任务执1行次数加1 注意task1_num1加到255的时候会清零！！
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1));
		//printf("任务1已经执行：%d次\r\n",task1_num);
    vTaskDelay(1000);                           //延时1s，也就是1000个时钟节拍	
	}
}

//task2任务函数
void task2_task(void *pvParameters)
{
	u8 task2_num=0;
	while(1)
	{
		task2_num++;	//任务2执行次数加1 注意task1_num2加到255的时候会清零！！
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0));
		//printf("任务2已经执行：%d次\r\n",task2_num);
    vTaskDelay(500);                           //延时1s，也就是1000个时钟节拍	
	}
}





