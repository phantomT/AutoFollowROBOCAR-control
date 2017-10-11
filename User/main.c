/**
  ******************************************************************************
  * @file    main.c
  * @author  FireIce
  * @version V1.1
  * @date    2017-10-11
  * @brief   ͨ�ö�ʱ��PWM���+����
  ******************************************************************************
  */
  
#include <stm32f4xx.h>
#include "./tim/bsp_general_tim.h"
#include "./usart/bsp_debug_usart.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void) 
{	
  /* ��ʼ��ͨ�ö�ʱ��PWM��� */
	TIMx_Configuration01(20,40,60,80);				//PA0-PA3�ڵ�PWM�����ռ�ձ�
  TIMx_Configuration02(30,50,70,90);				//PH9-PH12�ڵ�PWM�����ռ�ձ�
	
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	
	/* ����һ���ַ��� */
	Usart_SendString( DEBUG_USART,"����һ�������жϽ��ջ���ʵ��\n");
	printf("����һ�������жϽ��ջ���ʵ��\n");
	
  while(1)
  {       
  }
}



/*********************************************END OF FILE**********************/

