/*
 * RTOS_Example.c
 *
 * Created: 10/9/2020 4:46:32 PM
 * Author : loola
 */ 

#include "FreeRtos.h"
#include "task.h"
#include "queue.h"
#include "LCD.h"
#include "KP.h"
#define LED0        2
#define LED1        7
#define LED2        3
#define F_CPU   16000000
#include <avr/io.h>
#include <util/delay.h>

void Sender(void *p);
void Receiver(void *p);

TaskHandle_t led2_handle;
TaskHandle_t task1_handle;
QueueHandle_t xqueue;
int main(void)
{  
	LCD_init();
	KP_Init();
	xqueue= xQueueCreate(1, sizeof(char));
	if(xqueue !=NULL)
	{
		xTaskCreate(Sender,"Sender_Task",300,NULL,1,&task1_handle);
		xTaskCreate(Receiver,"Recv_Task",300,NULL,2,NULL);
		
		vTaskStartScheduler();
	}
	
	while (1)
	{
	}
}

void Sender(void *p){
	
	while(1){
		
			xQueueSendToBack(xqueue,KP_GetKey(),portMAX_DELAY);
			
	        vTaskDelay(100/portTICK_PERIOD_MS);

	}
}
//*********************************
void Receiver(void *p){

	unsigned char value=0;
	while(1){
		KP_GetKey()==value;
		xQueueReceive(xqueue,&value,portMAX_DELAY);
		if(value!=0)
		{
			LCD_SendNumber(value);
			vTaskDelay(100/portTICK_PERIOD_MS);
			
		}
		}
		}


