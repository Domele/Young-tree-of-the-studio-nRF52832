//Copyright (c) 2014 LPµç×Ó

#include "nrf52.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"
#include "pwm.h"
#include <stdbool.h>
#include <stdint.h>
 

uint16_t pwm_seq[4] = {5000, 8000, 12000,15000};

void PWM_init(void)
{
		NRF_PWM0->PSEL.OUT[0] = (PWM_Pin_Number << PWM_PSEL_OUT_PIN_Pos) |
		(PWM_PSEL_OUT_CONNECT_Connected << PWM_PSEL_OUT_CONNECT_Pos);
	
		NRF_PWM0->PSEL.OUT[1] = (PWM_Pin_Number+1 << PWM_PSEL_OUT_PIN_Pos) |
		(PWM_PSEL_OUT_CONNECT_Connected <<PWM_PSEL_OUT_CONNECT_Pos);
	
		NRF_PWM0->PSEL.OUT[2] = (PWM_Pin_Number+2 << PWM_PSEL_OUT_PIN_Pos) |
		(PWM_PSEL_OUT_CONNECT_Connected <<PWM_PSEL_OUT_CONNECT_Pos);
	
	//	NRF_PWM0->PSEL.OUT[3] = (PWM_Pin_Number+3 << PWM_PSEL_OUT_PIN_Pos) |
	//	(PWM_PSEL_OUT_CONNECT_Connected <<PWM_PSEL_OUT_CONNECT_Pos);
	
		NRF_PWM0->ENABLE = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
		NRF_PWM0->MODE = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
	
		NRF_PWM0->PRESCALER = (PWM_PRESCALER_PRESCALER_DIV_1 << PWM_PRESCALER_PRESCALER_Pos);
	
		NRF_PWM0->COUNTERTOP = (16000 << PWM_COUNTERTOP_COUNTERTOP_Pos); //1 msec
	
		NRF_PWM0->LOOP = (PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos);
	
		NRF_PWM0->DECODER = (PWM_DECODER_LOAD_Individual << PWM_DECODER_LOAD_Pos) |
		(PWM_DECODER_MODE_RefreshCount << PWM_DECODER_MODE_Pos);
	
		NRF_PWM0->SEQ[0].PTR = ((uint32_t)(pwm_seq) << PWM_SEQ_PTR_PTR_Pos);
		NRF_PWM0->SEQ[0].CNT = ((sizeof(pwm_seq) / sizeof(uint16_t)) << PWM_SEQ_CNT_CNT_Pos);
		
		NRF_PWM0->SEQ[0].REFRESH = 0;
		NRF_PWM0->SEQ[0].ENDDELAY = 0;
		NRF_PWM0->TASKS_SEQSTART[0] = 1;
}

