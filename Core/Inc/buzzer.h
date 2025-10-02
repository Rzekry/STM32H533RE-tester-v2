/*
 * buzzer.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "stm32h5xx_hal.h"

/*
 * UWAGA: Ta funkcja wymaga, aby timer PWM został wcześniej zainicjalizowany
 * i uruchomiony w main.c!
 *
 * Przykład:
 *   HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
 */

/**
 * @brief Włącza buzzer na określony czas.
 * @param duration_ms Czas trwania dźwięku w milisekundach.
 */
void buzzer_beep(uint32_t duration_ms);

void buzzer_on(void);
void buzzer_off(void);

#endif /* INC_BUZZER_H_ */