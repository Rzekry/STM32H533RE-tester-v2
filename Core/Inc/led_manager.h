/*
 * led_manager.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_LED_MANAGER_H_
#define INC_LED_MANAGER_H_

#include "main.h"

// Definicja wszystkich diod w systemie
typedef enum {
    LED_ID_RED,
    LED_ID_BLUE,
    LED_ID_GREEN,
    LED_ID_NUCLEO_GREEN,
    LED_ID_YELLOW,
    // Tutaj możesz dodać kolejne diody, np. LED_ID_ORANGE
    LED_ID_COUNT // Liczba wszystkich diod
} led_id_t;

/**
 * @brief Inicjalizuje wszystkie diody LED.
 */
void leds_init(void);

/**
 * @brief Włącza określoną diodę LED.
 * @param led_id Identyfikator diody z enum led_id_t.
 */
void led_on(led_id_t led_id);

/**
 * @brief Wyłącza określoną diodę LED.
 * @param led_id Identyfikator diody z enum led_id_t.
 */
void led_off(led_id_t led_id);

/**
 * @brief Przełącza stan określonej diody LED.
 * @param led_id Identyfikator diody z enum led_id_t.
 */
void led_toggle(led_id_t led_id);

#endif /* INC_LED_MANAGER_H_ */