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

void encoder_init(void) {
    // Uruchomienie timera w trybie enkodera na wszystkich kanałach
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

    // Ustawienie licznika na środku zakresu, aby móc swobodnie
    // zliczać w górę i w dół bez natychmiastowego przepełnienia.
    // Zakładamy, że Period timera to 65535 (16-bit).
    uint16_t middle_value = 32768;
    __HAL_TIM_SET_COUNTER(&htim2, middle_value);

    last_counter_value = middle_value;
}

int16_t encoder_get_change(void) {
    uint16_t current_counter = __HAL_TIM_GET_COUNTER(&htim2);

    // Oblicz różnicę od ostatniego odczytu
    int16_t diff = (int16_t)(current_counter - last_counter_value);

    // Zapisz aktualną wartość jako ostatnią
    last_counter_value = current_counter;

    // Enkoder w trybie TIM_ENCODERMODE_TI1 zlicza co drugi krok (2 impulsy na ząbek).
    // Aby uzyskać liczbę pełnych "ząbków", można podzielić wynik przez 2.
    // Jednak zwracanie surowej zmiany daje większą elastyczność.
    // W Twojej konfiguracji (TI1), jeden "ząbek" to zmiana o 2 lub -2.
    // Aby to ujednolicić, dzielimy przez 2.
    // Jeśli zauważysz, że enkoder jest zbyt czuły lub niedokładny, zmień dzielnik na 1 lub 4.

    return diff / 2;
}