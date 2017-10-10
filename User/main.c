/**
  ******************************************************************************
  * @file    main.c
  * @author  FireIce
  * @version V1.0
  * @date    2017-10-10
  * @brief   通用定时器PWM输出
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./tim/bsp_general_tim.h"

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
  while(1)
  {       
  }
}



/*********************************************END OF FILE**********************/

