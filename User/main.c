#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "portable.h"
#include "FreeRTOSConfig.h"
//usart
#include "HAL_Usart.h"

static void vLED1_Task(void *pvParameters);
static void vLED2_Task(void *pvParameters);


void LED_Init(void);

int main()
{
    LED_Init();
    HAL_Usart_Init();

	xTaskCreate(vLED1_Task,(char *)"LED1",configMINIMAL_STACK_SIZE
		,NULL,tskIDLE_PRIORITY+1,NULL);
		xTaskCreate(vLED2_Task,(char *)"LED2",configMINIMAL_STACK_SIZE
		,NULL,tskIDLE_PRIORITY+2,NULL);
		
		vTaskStartScheduler();
		return 0;

}

void vLED1_Task(void *pvParameters)
{
	while(1)
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void vLED2_Task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(500/portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_3);		
	}
}

void LED_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&gpio);
}
