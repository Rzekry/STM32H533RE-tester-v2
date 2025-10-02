/*
 * breathing_led.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_BREATHING_LED_H_
#define INC_BREATHING_LED_H_

#include "main.h"

/**
 * @brief Inicjalizuje moduł "oddychającej" diody LED.
 * @note Uruchamia PWM na odpowiednim kanale timera.
 */
void breathing_led_init(void);

/**
 * @brief Przetwarza efekt oddychania diody LED.
 * @note Powinna być wywoływana cyklicznie w pętli głównej.
 */
void breathing_led_process(void);

#endif /* INC_BREATHING_LED_H_ */