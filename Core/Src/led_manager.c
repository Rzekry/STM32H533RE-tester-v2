/*
 * led_manager.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "led_manager.h"

// Struktura przechowująca informacje o pojedynczej diodzie
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    GPIO_PinState on_state;  // Stan, który włącza diodę
    GPIO_PinState off_state; // Stan, który wyłącza diodę
} led_config_t;

// Tablica konfiguracyjna dla wszystkich diod
// Kolejność MUSI odpowiadać kolejności w enum led_id_t
static const led_config_t leds[LED_ID_COUNT] = {
    [LED_ID_RED]          = {LED_RED_GPIO_Port,   LED_RED_Pin,   GPIO_PIN_RESET, GPIO_PIN_SET},
    [LED_ID_BLUE]         = {LED_BLUE_GPIO_Port,  LED_BLUE_Pin,  GPIO_PIN_RESET, GPIO_PIN_SET},
    [LED_ID_GREEN]        = {LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET, GPIO_PIN_SET},
    [LED_ID_NUCLEO_GREEN] = {LED2_GPIO_PORT,      LED2_PIN,      GPIO_PIN_SET,   GPIO_PIN_RESET} // Dioda na Nucleo ma odwrotną logikę
};

void leds_init(void) {
    // Inicjalizacja diody z BSP
    BSP_LED_Init(LED_GREEN);

    // Twoje diody są już inicjalizowane w MX_GPIO_Init(),
    // ale tutaj moglibyśmy dodać dodatkową logikę, jeśli byłaby potrzebna.

    // Upewnijmy się, że wszystkie są zgaszone na starcie
    for (int i = 0; i < LED_ID_COUNT; i++) {
        led_off((led_id_t)i);
    }
}

void led_on(led_id_t led_id) {
    if (led_id < LED_ID_COUNT) {
        HAL_GPIO_WritePin(leds[led_id].port, leds[led_id].pin, leds[led_id].on_state);
    }
}

void led_off(led_id_t led_id) {
    if (led_id < LED_ID_COUNT) {
        HAL_GPIO_WritePin(leds[led_id].port, leds[led_id].pin, leds[led_id].off_state);
    }
}