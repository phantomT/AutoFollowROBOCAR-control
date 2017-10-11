/**
  ******************************************************************************
  * @file    main.c
  * @author  FireIce
  * @version V1.1
  * @date    2017-10-11
  * @brief   通用定时器PWM输出+串口
  ******************************************************************************
  */
  
#include <stm32f4xx.h>
#include "./tim/bsp_general_tim.h"
#include "./usart/bsp_debug_usart.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void) 
{	
  /* 初始化通用定时器PWM输出 */
	TIMx_Configuration01(20,40,60,80);				//PA0-PA3口的PWM波输出占空比
  TIMx_Configuration02(30,50,70,90);				//PH9-PH12口的PWM波输出占空比
	
	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	
	/* 发送一个字符串 */
	Usart_SendString( DEBUG_USART,"这是一个串口中断接收回显实验\n");
	printf("这是一个串口中断接收回显实验\n");
	
  while(1)
  {       
  }
}



/*********************************************END OF FILE**********************/

