/*
 * encoder.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "encoder.h"

// Musimy zadeklarować, że będziemy używać htim2 zdefiniowanego w main.c
extern TIM_HandleTypeDef htim2;

// Zmienna przechowująca ostatnią odczytaną wartość licznika enkodera
static uint16_t last_counter_value = 0;

// Liczba impulsów licznika przypadająca na jeden krok (ząbek) enkodera.
// W trybie TIM_ENCODERMODE_TI1 timer zlicza dwa impulsy na pełny krok.
#define ENCODER_COUNTS_PER_STEP 2

// Akumulacja impulsów pozwala zgłaszać wyłącznie pełne kroki enkodera.
static int32_t accumulated_counts = 0;

void encoder_init(void) {
    // Uruchomienie timera w trybie enkodera na wszystkich kanałach
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

    // Ustawienie licznika na środku zakresu, aby móc swobodnie
    // zliczać w górę i w dół bez natychmiastowego przepełnienia.
    // Zakładamy, że Period timera to 65535 (16-bit).
    uint16_t middle_value = 32768;
    __HAL_TIM_SET_COUNTER(&htim2, middle_value);

    last_counter_value = middle_value;
    accumulated_counts = 0;
}

int16_t encoder_get_change(void) {
    uint16_t current_counter = __HAL_TIM_GET_COUNTER(&htim2);

    // Oblicz różnicę od ostatniego odczytu
    int16_t diff = (int16_t)(current_counter - last_counter_value);

    // Zapisz aktualną wartość jako ostatnią
    last_counter_value = current_counter;

    // Akumuluj impulsy i zwróć pełne kroki (np. jeden zwrot = 1).
    accumulated_counts += diff;
    int16_t step_change = (int16_t)(accumulated_counts / ENCODER_COUNTS_PER_STEP);
    accumulated_counts -= (int32_t)step_change * ENCODER_COUNTS_PER_STEP;

    return step_change;
}
