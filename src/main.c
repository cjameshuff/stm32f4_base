
#include "stm32f4xx_conf.h"

#include "delay.h"

#include <stdint.h>
#include <stdbool.h>


GPIO_TypeDef * const LED_PORT[] = {GPIOD, GPIOD, GPIOD, GPIOD};
const uint16_t LED_PIN[] = {GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};

void LED_InitGPIO(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    GPIO_InitTypeDef gpioInit = {
        .GPIO_Pin = 0,
        .GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
        .GPIO_PuPd = GPIO_PuPd_UP,
        .GPIO_Speed = GPIO_Speed_50MHz
    };
    for(int j = 0; j < 4; ++j) {
        gpioInit.GPIO_Pin = LED_PIN[j];
        GPIO_Init(LED_PORT[j], &gpioInit);
    }
}

void SetLED(int led, bool state) {
    if(state)
        LED_PORT[led]->BSRRL = LED_PIN[led];
    else
        LED_PORT[led]->BSRRH = LED_PIN[led];
}

void ToggleLED(int led) {
    LED_PORT[led]->ODR ^= LED_PIN[led];
}

static void InitClocks(void);
// static void TIM4_Config(void);

int main(void)
{
    InitClocks();
    
    // Configure for millisecond system ticks
    if(SysTick_Config(SystemCoreClock/1000))
        while(1) {;}
    
    LED_InitGPIO();
    
    SetLED(0, true);
    SetLED(1, true);
    
    int led = 0;
    while(1)
    {
        delay_ms(1);
        ToggleLED(led);
        led = (led + 3)%4;
    }
} // main()


static void InitClocks(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CCMDATARAMEN, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC_Tx, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC_PTP, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_OTG_HS, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_OTG_HS_ULPI, ENABLE);
    
    // RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
    // RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_CRYP, ENABLE);
    // RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_HASH, ENABLE);
    // RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    // RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE);
    
    // RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
    
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
} // InitClocks()


void SysTick_Handler(void) {
    systicks++;
}

