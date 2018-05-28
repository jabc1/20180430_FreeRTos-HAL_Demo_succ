#include "MyTask.h"
#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h" 
#include "stm32f1xx.h" 
extern TaskHandle_t StartTask_Handler;
//�������ȼ�
#define KEY_TASK_PRIO		2
//�����ջ��С	
#define KEY_STK_SIZE 		128  
//������
TaskHandle_t KeyTask_Handler;
//������
void key_task(void *pvParameters);

//�������ȼ�
#define TASK1_TASK_PRIO		3
//�����ջ��С	
#define TASK1_STK_SIZE 		128  
//������
TaskHandle_t Task1Task_Handler;
//������
void task1_task(void *pvParameters);

//�������ȼ�
#define TASK2_TASK_PRIO		4
//�����ջ��С	
#define TASK2_STK_SIZE 		128  
//������
TaskHandle_t Task2Task_Handler;
//������
void task2_task(void *pvParameters);
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	//����KEY����
	xTaskCreate((TaskFunction_t )key_task,             
                (const char*    )"key_task",           
                (uint16_t       )KEY_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )KEY_TASK_PRIO,        
                (TaskHandle_t*  )&KeyTask_Handler);  
    //����TASK1����
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
    //����TASK2����
    xTaskCreate((TaskFunction_t )task2_task,     
                (const char*    )"task2_task",   
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_TASK_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler); 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}
//key������
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
//					vTaskSuspend(Task1Task_Handler);//��������
//					printf("��������1������!\r\n");
//				}
//				else if(statflag==0)
//				{
//					vTaskResume(Task1Task_Handler);	//�ָ�����1
//					printf("�ָ�����1������!\r\n");
//				}		
//				break;
//			case KEY1_PRES:
//				vTaskSuspend(Task2Task_Handler);//��������2
//				printf("��������2������!\r\n");
//				break;
//		}
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4));
		vTaskDelay(200);			//��ʱ10ms 
	}
}

//task1������
void task1_task(void *pvParameters)
{
	u8 task1_num=0;
	while(1)
	{
		task1_num++;	//����ִ1�д�����1 ע��task1_num1�ӵ�255��ʱ������㣡��
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1));
		//printf("����1�Ѿ�ִ�У�%d��\r\n",task1_num);
    vTaskDelay(1000);                           //��ʱ1s��Ҳ����1000��ʱ�ӽ���	
	}
}

//task2������
void task2_task(void *pvParameters)
{
	u8 task2_num=0;
	while(1)
	{
		task2_num++;	//����2ִ�д�����1 ע��task1_num2�ӵ�255��ʱ������㣡��
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,(GPIO_PinState)!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0));
		//printf("����2�Ѿ�ִ�У�%d��\r\n",task2_num);
    vTaskDelay(500);                           //��ʱ1s��Ҳ����1000��ʱ�ӽ���	
	}
}





