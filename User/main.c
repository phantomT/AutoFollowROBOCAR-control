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
	char cmd[9];
	int i;
	int ZKB_A0,ZKB_A1,ZKB_A2,ZKB_A3;
	int ZKB_I0,ZKB_H10,ZKB_H11,ZKB_H12;
	
  /* ��ʼ��ͨ�ö�ʱ��PWM��� */
	TIMx_Configuration01(20,40,60,80);				//PA0-PA3�ڵ�PWM�����ռ�ձ�
  TIMx_Configuration02(30,50,70,90);				//PH10-PH12��PI0�ڵ�PWM�����ռ�ձ�
	
	/*��ʼ��USART ����ģʽΪ 8-N-1���жϽ���*/
  Debug_USART_Config();
	
	/* ����һ���ַ��� */
	//Usart_SendString( DEBUG_USART,"����һ�������жϽ��ջ���ʵ��\n");
	printf("����һ�������жϽ��ջ���ʵ��\n");
	
  while(1)
  {       
		/* ��ȡ�ַ�ָ�� */
    for(i=0;i<8;i++)
		{
			cmd[i]=getchar();
		}
		cmd[8]='\0';
    printf("recieved command��%s\n",cmd);
		getchar();
		
		ZKB_A0=(cmd[0]-'0')*10+(cmd[1]-'0');
		ZKB_A1=(cmd[2]-'0')*10+(cmd[3]-'0');
		ZKB_A2=(cmd[4]-'0')*10+(cmd[5]-'0');
		ZKB_A3=(cmd[6]-'0')*10+(cmd[7]-'0');
		TIMx_Configuration01(ZKB_A0,ZKB_A1,ZKB_A2,ZKB_A3);				//PA0-PA3�ڵ�PWM�����ռ�ձ�
		
		ZKB_I0=100-ZKB_A3;
		ZKB_H10=100-ZKB_A0;
		ZKB_H11=100-ZKB_A1;
		ZKB_H12=100-ZKB_A2;
		TIMx_Configuration02(ZKB_H10,ZKB_H11,ZKB_H12,ZKB_I0);				//PH10-PH12��PI0�ڵ�PWM�����ռ�ձ�
		
  }
}



/*********************************************END OF FILE**********************/

