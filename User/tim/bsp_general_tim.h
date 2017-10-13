#ifndef __GENERAL_TIM_H
#define	__GENERAL_TIM_H

#include "stm32f4xx.h"

#define G_OCPWM_PIN01            		GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
#define G_OCPWM_PIN02            		GPIO_Pin_0|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12

#define G_OCPWM_GPIO_PORT01       	GPIOA                      
#define G_OCPWM_GPIO_CLK01        	RCC_AHB1Periph_GPIOA

#define G_OCPWM_GPIO_PORT02       	GPIOH                      
#define G_OCPWM_GPIO_CLK02        	RCC_AHB1Periph_GPIOH

#define G_OCPWM_GPIO_PORT03       	GPIOI                     
#define G_OCPWM_GPIO_CLK03        	RCC_AHB1Periph_GPIOI

#define G_OCPWM_PS00				GPIO_PinSource0
#define G_OCPWM_PS01				GPIO_PinSource1
#define G_OCPWM_PS02				GPIO_PinSource2
#define G_OCPWM_PS03				GPIO_PinSource3
#define G_OCPWM_PS09				GPIO_PinSource0
#define G_OCPWM_PS10				GPIO_PinSource10
#define G_OCPWM_PS11				GPIO_PinSource11
#define G_OCPWM_PS12				GPIO_PinSource12

#define G_OCPWM_AF01				GPIO_AF_TIM2
#define G_OCPWM_AF02				GPIO_AF_TIM5

#define G_TIM01           		    TIM2
#define G_TIM02           		    TIM5
#define G_TIM_CLK01       		    RCC_APB1Periph_TIM2
#define G_TIM_CLK02       		    RCC_APB1Periph_TIM5

#define G_TIM_IRQn01				TIM2_IRQn
#define G_TIM_IRQHandler01        	TIM2_IRQHandler
#define G_TIM_IRQn02				TIM5_IRQn
#define G_TIM_IRQHandler02        	TIM5_IRQHandler

#define TIM_COUNTER_CLOCK        45000000
#define TIM_PRESCALER_VALUE      (SystemCoreClock/2/TIM_COUNTER_CLOCK - 1)
#define TIM_PERIOD_TIMING    (45000 - 1) 

void TIMx_Configuration01(int CCR0,int CCR1,int CCR2,int CCR3);
void TIMx_Configuration02(int CCR0,int CCR1,int CCR2,int CCR3);

#endif /* __GENERAL_TIM_H */

