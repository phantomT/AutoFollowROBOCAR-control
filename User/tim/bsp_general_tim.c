/**
  ******************************************************************************
  * @file    bsp_general_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2017-10-10
  * @brief   通用定时器PWM
  ******************************************************************************
  */
  
#include "./tim/bsp_general_tim.h"

/**
  * @brief  配置TIM复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */
static void TIMx_GPIO_Config_A(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (G_OCPWM_GPIO_CLK01, ENABLE);
	
	/* 定时器通道引脚复用 */
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS00,G_OCPWM_AF01);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS01,G_OCPWM_AF01);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS02,G_OCPWM_AF01);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT01,G_OCPWM_PS03,G_OCPWM_AF01);

	/* 定时器通道引脚配置 */															   
	GPIO_InitStructure.GPIO_Pin = G_OCPWM_PIN01;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_Init(G_OCPWM_GPIO_PORT01, &GPIO_InitStructure);
}

static void TIMx_GPIO_Config_B(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (G_OCPWM_GPIO_CLK02, ENABLE);
	RCC_AHB1PeriphClockCmd (G_OCPWM_GPIO_CLK03, ENABLE);
	
	/* 定时器通道引脚复用 */
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT03,G_OCPWM_PS09,G_OCPWM_AF02);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT02,G_OCPWM_PS10,G_OCPWM_AF02);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT02,G_OCPWM_PS11,G_OCPWM_AF02);
	GPIO_PinAFConfig(G_OCPWM_GPIO_PORT02,G_OCPWM_PS12,G_OCPWM_AF02);

  
	/* 定时器通道引脚配置 */															   
	GPIO_InitStructure.GPIO_Pin = G_OCPWM_PIN02;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_Init(G_OCPWM_GPIO_PORT02, &GPIO_InitStructure);
	GPIO_Init(G_OCPWM_GPIO_PORT03, &GPIO_InitStructure);
}

/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         都有
 * TIM_CounterMode			 TIMx,x[6,7]没有，其他都有（基本定时器）
 * TIM_Period            都有
 * TIM_ClockDivision     TIMx,x[6,7]没有，其他都有(基本定时器)
 * TIM_RepetitionCounter TIMx,x[1,8]才有(高级定时器)
 *-----------------------------------------------------------------------------
 */
static void TIM_PWMOUTPUT_Config01(int CCR0,int CCR1,int CCR2,int CCR3)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// 开启TIMx_CLK,x[2,3,4,5,12,13,14] 
	RCC_APB1PeriphClockCmd(G_TIM_CLK01, ENABLE); 
	
	uint32_t Freq=1000;
	uint32_t TimerPeriod = (TIM_COUNTER_CLOCK/ Freq ) - 1;

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到TimerPeriod 为一个定时周期
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;       
	
	// 通用控制定时器时钟源TIMxCLK = HCLK/2=90MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PRESCALER_VALUE;	
  // 采样时钟分频
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // 计数方式
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// 初始化定时器TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(G_TIM01, &TIM_TimeBaseStructure);
	
	uint32_t ccr0,ccr1,ccr2,ccr3;
	ccr0=(TimerPeriod+1)*CCR0/100;
	ccr1=(TimerPeriod+1)*CCR1/100;
	ccr2=(TimerPeriod+1)*CCR2/100;
	ccr3=(TimerPeriod+1)*CCR3/100;
	
	/*PWM模式配置*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = ccr0-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为高电平
	
	TIM_OC1Init(G_TIM01, &TIM_OCInitStructure);	 //使能通道1
	
	TIM_OCInitStructure.TIM_Pulse = ccr1-1;
	TIM_OC2Init(G_TIM01, &TIM_OCInitStructure);	 //使能通道2
	
	TIM_OCInitStructure.TIM_Pulse = ccr2-1;
	TIM_OC3Init(G_TIM01, &TIM_OCInitStructure);	 //使能通道3
	
	TIM_OCInitStructure.TIM_Pulse = ccr3-1;
	TIM_OC4Init(G_TIM01, &TIM_OCInitStructure);	 //使能通道4
  
	/*使能通道重载*/
	TIM_OC1PreloadConfig(G_TIM01, TIM_OCPreload_Enable);
		
	// 使能定时器
	TIM_Cmd(G_TIM01, ENABLE);	
}

static void TIM_PWMOUTPUT_Config02(int CCR0,int CCR1,int CCR2,int CCR3)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// 开启TIMx_CLK,x[2,3,4,5,12,13,14] 
	RCC_APB1PeriphClockCmd(G_TIM_CLK02, ENABLE); 
	
	uint32_t Freq=1000;
	uint32_t TimerPeriod = (TIM_COUNTER_CLOCK/ Freq ) - 1;

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到TimerPeriod 为一个定时周期
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;       
	
	// 通用控制定时器时钟源TIMxCLK = HCLK/2=90MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PRESCALER_VALUE;	
  // 采样时钟分频
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // 计数方式
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// 初始化定时器TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(G_TIM02, &TIM_TimeBaseStructure);	
	
	uint32_t ccr0,ccr1,ccr2,ccr3;
	ccr0=(TimerPeriod+1)*CCR0/100;
	ccr1=(TimerPeriod+1)*CCR1/100;
	ccr2=(TimerPeriod+1)*CCR2/100;
	ccr3=(TimerPeriod+1)*CCR3/100;
	
	/*PWM模式配置*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = ccr0-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为高电平
	
	TIM_OC1Init(G_TIM02, &TIM_OCInitStructure);	 //使能通道1
	
	TIM_OCInitStructure.TIM_Pulse = ccr1-1;
	TIM_OC2Init(G_TIM02, &TIM_OCInitStructure);	 //使能通道2
	
	TIM_OCInitStructure.TIM_Pulse = ccr2-1;
	TIM_OC3Init(G_TIM02, &TIM_OCInitStructure);	 //使能通道3
	
	TIM_OCInitStructure.TIM_Pulse = ccr3-1;
	TIM_OC4Init(G_TIM02, &TIM_OCInitStructure);	 //使能通道4
  
	/*使能通道重载*/
	TIM_OC4PreloadConfig(G_TIM02, TIM_OCPreload_Enable);
	// 使能定时器
	TIM_Cmd(G_TIM02, ENABLE);	
}

/**
  * @brief  初始化通用控制定时器定时
  * @param  无
  * @retval 无
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
