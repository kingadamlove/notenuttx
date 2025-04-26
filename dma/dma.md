config STM32_ADC1
	bool "ADC1"
	select STM32_HAVE_ADC1_DMA if !STM32_STM32F10XX && STM32_DMA2


STM32_HAVE_ADC1_DMA



# 开启usart3的dma，需要在stm32discovery.h添加 #define DMAMAP_USART3_TX DMAMAP_USART3_TX_1 .
1. 因为有两个可用的dma的通道流，需要自己去选择
2. dma有两个版本，stm32_dma_v1.h和stm32_dma_v2.h，f4属于版本2（文件开头有说明）


