/*
 * buzzer.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "buzzer.h"

// Musimy zadeklarować, że będziemy używać htim3 zdefiniowanego w main.c
extern TIM_HandleTypeDef htim3;

void buzzer_on(void) {
	// Ustawienie wypełnienia PWM na 50% (wartość 500 przy Period=999)
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 500);
}

void buzzer_off(void) {
	// Ustawienie wypełnienia PWM na 0%
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
}

/**
 * @brief Włącza buzzer na określony czas.
 * @note Ta funkcja jest blokująca! Używa HAL_Delay.
 * @param duration_ms Czas trwania dźwięku w milisekundach.
 */
void buzzer_beep(uint32_t duration_ms) {
	buzzer_on();
	HAL_Delay(duration_ms);
	buzzer_off();
}