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
	char cmd[9];
	int i;
	int ZKB_A0,ZKB_A1,ZKB_A2,ZKB_A3;
	int ZKB_I0,ZKB_H10,ZKB_H11,ZKB_H12;
	
  /* 初始化通用定时器PWM输出 */
	TIMx_Configuration01(20,40,60,80);				//PA0-PA3口的PWM波输出占空比
  TIMx_Configuration02(30,50,70,90);				//PH10-PH12，PI0口的PWM波输出占空比
	
	/*初始化USART 配置模式为 8-N-1，中断接收*/
  Debug_USART_Config();
	
	/* 发送一个字符串 */
	//Usart_SendString( DEBUG_USART,"这是一个串口中断接收回显实验\n");
	printf("这是一个串口中断接收回显实验\n");
	
  while(1)
  {       
		/* 获取字符指令 */
    for(i=0;i<8;i++)
		{
			cmd[i]=getchar();
		}
		cmd[8]='\0';
    printf("recieved command：%s\n",cmd);
		getchar();
		
		ZKB_A0=(cmd[0]-'0')*10+(cmd[1]-'0');
		ZKB_A1=(cmd[2]-'0')*10+(cmd[3]-'0');
		ZKB_A2=(cmd[4]-'0')*10+(cmd[5]-'0');
		ZKB_A3=(cmd[6]-'0')*10+(cmd[7]-'0');
		TIMx_Configuration01(ZKB_A0,ZKB_A1,ZKB_A2,ZKB_A3);				//PA0-PA3口的PWM波输出占空比
		
		ZKB_I0=100-ZKB_A3;
		ZKB_H10=100-ZKB_A0;
		ZKB_H11=100-ZKB_A1;
		ZKB_H12=100-ZKB_A2;
		TIMx_Configuration02(ZKB_H10,ZKB_H11,ZKB_H12,ZKB_I0);				//PH10-PH12，PI0口的PWM波输出占空比
		
  }
}



/*********************************************END OF FILE**********************/

