/*
 * breathing_led.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "breathing_led.h"
#include <math.h>

// Zewnętrzna deklaracja timera
extern TIM_HandleTypeDef htim3;

// Konfiguracja
#define BREATHING_TIMER         &htim3
#define BREATHING_CHANNEL       TIM_CHANNEL_2
#define BREATHING_PERIOD_MS     2000 // Czas trwania jednego cyklu "oddechu"
#define PWM_MAX_PULSE           999  // Maksymalna wartość pulsu (zgodnie z Period timera)

static uint32_t start_time = 0;

void breathing_led_init(void) {
    HAL_TIM_PWM_Start(BREATHING_TIMER, BREATHING_CHANNEL);
    start_time = HAL_GetTick();
}

void breathing_led_process(void) {
    uint32_t current_time = HAL_GetTick();
    uint32_t elapsed_time = current_time - start_time;

    // Obliczanie wartości sinusoidalnej dla efektu "oddychania"
    // Używamy funkcji sinus do płynnej zmiany jasności.
    // Argument sinusa jest w radianach, więc skalujemy czas.
    float angle = (float)elapsed_time * 2.0f * M_PI / (float)BREATHING_PERIOD_MS;

    // Funkcja sin zwraca wartości od -1 do 1. Przesuwamy i skalujemy, aby uzyskać 0-1.
    float brightness = (sinf(angle - M_PI / 2.0f) + 1.0f) / 2.0f;

    // Ustawiamy wypełnienie PWM
    uint32_t pulse = (uint32_t)(brightness * PWM_MAX_PULSE);
    __HAL_TIM_SET_COMPARE(BREATHING_TIMER, BREATHING_CHANNEL, pulse);
}