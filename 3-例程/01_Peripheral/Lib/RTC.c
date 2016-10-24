#include "nrf52.h"
#include "nrf_gpio.h"
#include "rtc.h"
#include "led.h"
#include <stdbool.h>

#define LFCLK_FREQUENCY           (32768UL)                               /**< LFCLK频率为HZ. */
#define RTC_FREQUENCY             (8UL)                                   /**< 所需的RTC工作时钟 RTC_FREQUENCY 为HZ. */
#define COMPARE_COUNTERTIME       (3UL)                                   /**< Get Compare event COMPARE_TIME seconds after the counter starts from 0. */
#define COUNTER_PRESCALER         ((LFCLK_FREQUENCY/RTC_FREQUENCY) - 1)   /* f = LFCLK/(prescaler + 1) */


/** @brief 启动内部LFCLK晶振功能
 */
 void lfclk_config(void)
{
    NRF_CLOCK->LFCLKSRC             = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED  = 0;
    NRF_CLOCK->TASKS_LFCLKSTART     = 1;
    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0)
    {
        //Do nothing.
    }
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
}


/** @brief Function for configuring the RTC with TICK to 100Hz and COMPARE0 to 10 sec.
 */
 void rtc_config(void)
{
    NVIC_EnableIRQ(RTC0_IRQn);                                      // 使能 RTC中断.
    NRF_RTC0->PRESCALER     = COUNTER_PRESCALER;                    // 设置预分频值prescaler to a TICK of RTC_FREQUENCY.
    NRF_RTC0->CC[0]         = COMPARE_COUNTERTIME * RTC_FREQUENCY;  // Compare0 after approx COMPARE_COUNTERTIME seconds.

    // Enable TICK event and TICK interrupt:
    NRF_RTC0->EVTENSET      = RTC_EVTENSET_TICK_Msk;
    NRF_RTC0->INTENSET      = RTC_INTENSET_TICK_Msk;

    // Enable COMPARE0 event and COMPARE0 interrupt:
    NRF_RTC0->EVTENSET      = RTC_EVTENSET_COMPARE0_Msk;
    NRF_RTC0->INTENSET      = RTC_INTENSET_COMPARE0_Msk;
}

/** @brief: Function for handling the RTC0 interrupts.
 * Triggered on TICK and COMPARE0 match.
 */
void RTC0_IRQHandler()
{
    if ((NRF_RTC0->EVENTS_TICK != 0) && 
        ((NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Msk) != 0))
    {
        NRF_RTC0->EVENTS_TICK = 0;
        LED_Toggle(LED_1);
    }
    
    if ((NRF_RTC0->EVENTS_COMPARE[0] != 0) && 
        ((NRF_RTC0->INTENSET & RTC_INTENSET_COMPARE0_Msk) != 0))
    {
        NRF_RTC0->EVENTS_COMPARE[0] = 0;
        LED_Toggle(LED_2);
    }
}

