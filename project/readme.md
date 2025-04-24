#   mythread应用层
#   驱动层需要添加bsp
##  adc的bsp ，参考stm32f103minimum的stm32_adc.c
文件路径    /home/kingadam/nuttxspace/nuttx/boards/arm/stm32/stm32f103-minimum/src/stm32_adc.c
### 1.  首先需要在stm32_bringup.c文件中加入stm32_adc_setup（这是adc的bsp的驱动函数）
### 2.  还需要把stm32_adc.c加入编译选项。cmake、defs、等文件都要加
### 3.  然后再复制并修改stm32_adc.c文件,这里主要是修改引脚使用就好了