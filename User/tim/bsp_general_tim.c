/**
  ******************************************************************************
  * @file    bsp_general_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2017-10-10
  * @brief   ͨ�ö�ʱ��PWM
  ******************************************************************************
  */
  
#include "./tim/bsp_general_tim.h"

/**
  * @brief  ����TIM�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIMx_GPIO_Config_A(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*������ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (G_OCPWM_GPIO_CLK01, ENABLE);
	
	/* ��ʱ��ͨ�����Ÿ��� */
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS00,G_OCPWM_AF01);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS01,G_OCPWM_AF01);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS02,G_OCPWM_AF01);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS03,G_OCPWM_AF01);

	/* ��ʱ��ͨ���������� */															   
	GPIO_InitStructure.GPIO_Pin = G_OCPWM_PIN01;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_Init(G_OCPWM_GPIO_PORT01, &GPIO_InitStructure);
}

static void TIMx_GPIO_Config_B(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*������ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (G_OCPWM_GPIO_CLK02, ENABLE);
	RCC_AHB1PeriphClockCmd (G_OCPWM_GPIO_CLK03, ENABLE);
	
	/* ��ʱ��ͨ�����Ÿ��� */
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT03,G_OCPWM_PS09,G_OCPWM_AF02);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT02,G_OCPWM_PS10,G_OCPWM_AF02);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT02,G_OCPWM_PS11,G_OCPWM_AF02);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT02,G_OCPWM_PS12,G_OCPWM_AF02);

  
	/* ��ʱ��ͨ���������� */															   
	GPIO_InitStructure.GPIO_Pin = G_OCPWM_PIN02;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_Init(G_OCPWM_GPIO_PORT02, &GPIO_InitStructure);
	GPIO_Init(G_OCPWM_GPIO_PORT03, &GPIO_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         ����
 * TIM_CounterMode			 TIMx,x[6,7]û�У��������У�������ʱ����
 * TIM_Period            ����
 * TIM_ClockDivision     TIMx,x[6,7]û�У���������(������ʱ��)
 * TIM_RepetitionCounter TIMx,x[1,8]����(�߼���ʱ��)
 *-----------------------------------------------------------------------------
 */
static void TIM_PWMOUTPUT_Config01(int CCR0,int CCR1,int CCR2,int CCR3)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����TIMx_CLK,x[2,3,4,5,12,13,14] 
	RCC_APB1PeriphClockCmd(G_TIM_CLK01, ENABLE); 
	
	uint32_t Freq=1000;
	uint32_t TimerPeriod = (TIM_COUNTER_CLOCK/ Freq ) - 1;

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������TimerPeriod Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;       
	
	// ͨ�ÿ��ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK/2=90MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PRESCALER_VALUE;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(G_TIM01, &TIM_TimeBaseStructure);
	
	uint32_t ccr0,ccr1,ccr2,ccr3;
	ccr0=(TimerPeriod+1)*CCR0/100;
	ccr1=(TimerPeriod+1)*CCR1/100;
	ccr2=(TimerPeriod+1)*CCR2/100;
	ccr3=(TimerPeriod+1)*CCR3/100;
	
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = ccr0-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	
	TIM_OC1Init(G_TIM01, &TIM_OCInitStructure);	 //ʹ��ͨ��1
	
	TIM_OCInitStructure.TIM_Pulse = ccr1-1;
	TIM_OC2Init(G_TIM01, &TIM_OCInitStructure);	 //ʹ��ͨ��2
	
	TIM_OCInitStructure.TIM_Pulse = ccr2-1;
	TIM_OC3Init(G_TIM01, &TIM_OCInitStructure);	 //ʹ��ͨ��3
	
	TIM_OCInitStructure.TIM_Pulse = ccr3-1;
	TIM_OC4Init(G_TIM01, &TIM_OCInitStructure);	 //ʹ��ͨ��4
  
	/*ʹ��ͨ������*/
	TIM_OC1PreloadConfig(G_TIM01, TIM_OCPreload_Enable);
		
	// ʹ�ܶ�ʱ��
	TIM_Cmd(G_TIM01, ENABLE);	
}

static void TIM_PWMOUTPUT_Config02(int CCR0,int CCR1,int CCR2,int CCR3)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����TIMx_CLK,x[2,3,4,5,12,13,14] 
	RCC_APB1PeriphClockCmd(G_TIM_CLK02, ENABLE); 
	
	uint32_t Freq=1000;
	uint32_t TimerPeriod = (TIM_COUNTER_CLOCK/ Freq ) - 1;

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������TimerPeriod Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;       
	
	// ͨ�ÿ��ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK/2=90MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PRESCALER_VALUE;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(G_TIM02, &TIM_TimeBaseStructure);	
	
	uint32_t ccr0,ccr1,ccr2,ccr3;
	ccr0=(TimerPeriod+1)*CCR0/100;
	ccr1=(TimerPeriod+1)*CCR1/100;
	ccr2=(TimerPeriod+1)*CCR2/100;
	ccr3=(TimerPeriod+1)*CCR3/100;
	
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = ccr0-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	
	TIM_OC1Init(G_TIM02, &TIM_OCInitStructure);	 //ʹ��ͨ��1
	
	TIM_OCInitStructure.TIM_Pulse = ccr1-1;
	TIM_OC2Init(G_TIM02, &TIM_OCInitStructure);	 //ʹ��ͨ��2
	
	TIM_OCInitStructure.TIM_Pulse = ccr2-1;
	TIM_OC3Init(G_TIM02, &TIM_OCInitStructure);	 //ʹ��ͨ��3
	
	TIM_OCInitStructure.TIM_Pulse = ccr3-1;
	TIM_OC4Init(G_TIM02, &TIM_OCInitStructure);	 //ʹ��ͨ��4
  
	/*ʹ��ͨ������*/
	TIM_OC4PreloadConfig(G_TIM02, TIM_OCPreload_Enable);
	// ʹ�ܶ�ʱ��
	TIM_Cmd(G_TIM02, ENABLE);	
}

/**
  * @brief  ��ʼ��ͨ�ÿ��ƶ�ʱ����ʱ
  * @param  ��
  * @retval ��
  */
void TIMx_Configuration01(int CCR0,int CCR1,int CCR2,int CCR3)
{
	TIMx_GPIO_Config_A();
  
  TIM_PWMOUTPUT_Config01(CCR0,CCR1,CCR2,CCR3);
}

void TIMx_Configuration02(int CCR0,int CCR1,int CCR2,int CCR3)
{
	TIMx_GPIO_Config_B();
  
  TIM_PWMOUTPUT_Config02(CCR0,CCR1,CCR2,CCR3);
}

/*********************************************END OF FILE**********************/
