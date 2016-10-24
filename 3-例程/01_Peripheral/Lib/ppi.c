#include "nrf52.h"
#include "ppi.h"

/** @brief Function for initializing the PPI peripheral.
*/
 void ppi_init(void)
{
    // Configure PPI channel 0 to stop Timer 0 counter at TIMER1 COMPARE[0] match, which is every even number of seconds.
    NRF_PPI->CH[0].EEP = (uint32_t)(&NRF_TIMER1->EVENTS_COMPARE[0]);
    NRF_PPI->CH[0].TEP = (uint32_t)(&NRF_TIMER0->TASKS_STOP);

    // Configure PPI channel 1 to start timer0 counter at TIMER2 COMPARE[0] match, which is every odd number of seconds.
    NRF_PPI->CH[1].EEP = (uint32_t)(&NRF_TIMER2->EVENTS_COMPARE[0]);
    NRF_PPI->CH[1].TEP = (uint32_t)(&NRF_TIMER0->TASKS_START);

    // Enable only PPI channels 0 and 1.
    NRF_PPI->CHEN = (PPI_CHEN_CH0_Enabled << PPI_CHEN_CH0_Pos) | (PPI_CHEN_CH1_Enabled << PPI_CHEN_CH1_Pos);
}


