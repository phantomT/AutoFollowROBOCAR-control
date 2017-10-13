/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  FireIce
  * @version V1.0
  * @date    2017-10-11
  * @brief   ÖØ¶¨Ïòc¿âprintfº¯Êıµ½usart¶Ë¿Ú£¬ÖĞ¶Ï½ÓÊÕÄ£Ê½
  ******************************************************************************
  */ 
  
#include "./usart/bsp_debug_usart.h"


 /**
  * @brief  ÅäÖÃÇ¶Ì×ÏòÁ¿ÖĞ¶Ï¿ØÖÆÆ÷NVIC
  * @param  ÎŞ
  * @retval ÎŞ
  */
//static void NVIC_Configuration(void)
//{
  //NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ç¶Ì×ÏòÁ¿ÖĞ¶Ï¿ØÖÆÆ÷×éÑ¡Ôñ */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ÅäÖÃUSARTÎªÖĞ¶ÏÔ´ */
  //NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* ÇÀ¶ÏÓÅÏÈ¼¶Îª1 */
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ×ÓÓÅÏÈ¼¶Îª1 */
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* Ê¹ÄÜÖĞ¶Ï */
  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ³õÊ¼»¯ÅäÖÃNVIC */
  //NVIC_Init(&NVIC_InitStructure);	
//}


 /**
  * @brief  DEBUG_USART GPIO ÅäÖÃ,¹¤×÷Ä£Ê½ÅäÖÃ¡  8-N-1 £¬ÖĞ¶Ï½ÓÊÕÄ£Ê½
  * @param  ÎŞ
  * @retval ÎŞ
  */
void Debug_USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
		
  RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK,ENABLE);

  /* Ê¹ÄÜ USART Ê±ÖÓ */
  RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);
  
  /* GPIO³õÊ¼»¯ */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* ÅäÖÃTxÒı½ÅÎª¸´ÓÃ¹¦ÄÜ  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;  
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  /* ÅäÖÃRxÒı½ÅÎª¸´ÓÃ¹¦ÄÜ */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
  
 /* Á¬½Ó PXx µ½ USARTx_Tx*/
  GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);

  /*  Á¬½Ó PXx µ½ USARTx__Rx*/
  GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
  
  /* ÅäÖÃ´®DEBUG_USART Ä£Ê½ */
  /* ²¨ÌØÂÊÉèÖÃ£ºDEBUG_USART_BAUDRATE */
  USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
  /* ×Ö³¤(Êı¾İÎ»+Ğ£ÑéÎ»)£º8 */
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* Í£Ö¹Î»£º1¸öÍ£Ö¹Î» */
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* Ğ£ÑéÎ»Ñ¡Ôñ£º²»Ê¹ÓÃĞ£Ñé */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  /* Ó²¼şÁ÷¿ØÖÆ£º²»Ê¹ÓÃÓ²¼şÁ÷ */
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  /* USARTÄ£Ê½¿ØÖÆ£ºÍ¬Ê±Ê¹ÄÜ½ÓÊÕºÍ·¢ËÍ */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* Íê³ÉUSART³õÊ¼»¯ÅäÖÃ */
  USART_Init(DEBUG_USART, &USART_InitStructure); 
	
  /* Ç¶Ì×ÏòÁ¿ÖĞ¶Ï¿ØÖÆÆ÷NVICÅäÖÃ */
	//NVIC_Configuration();
  
	/* Ê¹ÄÜ´®¿Ú½ÓÊÕÖĞ¶Ï */
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
	
  /* Ê¹ÄÜ´®¿Ú */
  USART_Cmd(DEBUG_USART, ENABLE);
}

/*****************  ·¢ËÍÒ»¸ö×Ö·û **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ·¢ËÍÒ»¸ö×Ö½ÚÊı¾İµ½USART */
	USART_SendData(pUSARTx,ch);
		
	/* µÈ´ı·¢ËÍÊı¾İ¼Ä´æÆ÷Îª¿Õ */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  ·¢ËÍ×Ö·û´® **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* µÈ´ı·¢ËÍÍê³É */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ·¢ËÍÒ»¸ö16Î»Êı **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* È¡³ö¸ß°ËÎ» */
	temp_h = (ch&0XFF00)>>8;
	/* È¡³öµÍ°ËÎ» */
	temp_l = ch&0XFF;
	
	/* ·¢ËÍ¸ß°ËÎ» */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ·¢ËÍµÍ°ËÎ» */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///ÖØ¶¨Ïòc¿âº¯Êıprintfµ½´®¿Ú£¬ÖØ¶¨Ïòºó¿ÉÊ¹ÓÃprintfº¯Êı
int fputc(int ch, FILE *f)
{
		/* ·¢ËÍÒ»¸ö×Ö½ÚÊı¾İµ½´®¿Ú */
		USART_SendData(DEBUG_USART, (uint8_t) ch);
		
		/* µÈ´ı·¢ËÍÍê±Ï */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///ÖØ¶¨Ïòc¿âº¯Êıscanfµ½´®¿Ú£¬ÖØĞ´Ïòºó¿ÉÊ¹ÓÃscanf¡¢getcharµÈº¯Êı
int fgetc(FILE *f)
{
		/* µÈ´ı´®¿ÚÊäÈëÊı¾İ */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}
/*********************************************END OF FILE**********************/
