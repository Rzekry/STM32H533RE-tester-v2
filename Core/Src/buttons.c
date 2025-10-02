/*
 * buttons.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "buttons.h"
#include <stdbool.h>

#define DEBOUNCE_TIME_MS 50

// Definicja stanu dla pojedynczego przycisku
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    bool pressed_flag;      // Flaga ustawiana po wykryciu wciśnięcia
    bool is_debouncing;     // Czy przycisk jest w trakcie debouncingu
    uint32_t debounce_start; // Czas rozpoczęcia debouncingu
} button_state_t;

// Tablica przechowująca stan wszystkich przycisków
static button_state_t buttons[BUTTON_ID_COUNT];

void buttons_init(void) {
    // Konfiguracja dla przycisku enkodera
    buttons[BUTTON_ID_ENCODER].port = ENC_BTN_GPIO_Port;
    buttons[BUTTON_ID_ENCODER].pin = ENC_BTN_Pin;

    // Konfiguracja dla przycisku testowego
    buttons[BUTTON_ID_TEST].port = TEST_BTN_GPIO_Port;
    buttons[BUTTON_ID_TEST].pin = TEST_BTN_Pin;

    // Konfiguracja dla przycisku USER
    buttons[BUTTON_ID_USER].port = BUTTON_USER_GPIO_PORT;
    buttons[BUTTON_ID_USER].pin = BUTTON_USER_PIN;

    // Inicjalizacja GPIO dla przycisków jest już zrobiona w main.c (MX_GPIO_Init i BSP_PB_Init)
}

void buttons_process(void) {
    uint32_t current_time = HAL_GetTick();

    for (int i = 0; i < BUTTON_ID_COUNT; i++) {
        if (buttons[i].is_debouncing) {
            // Sprawdź, czy minął czas debouncingu
            if ((uint32_t)(current_time - buttons[i].debounce_start) > DEBOUNCE_TIME_MS) {
                // Odczytaj stan pinu PO debouncingu
                GPIO_PinState pin_state = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);

                // Sprawdź, czy przycisk jest nadal wciśnięty
                // Nasze przyciski mają logikę odwróconą (wciśnięty = stan niski), z wyjątkiem USER (wciśnięty = stan wysoki)
                bool is_pressed_now = (i == BUTTON_ID_USER) ? (pin_state == GPIO_PIN_SET) : (pin_state == GPIO_PIN_RESET);

                if (is_pressed_now) {
                    buttons[i].pressed_flag = true;
                }
                buttons[i].is_debouncing = false;
            }
        }
    }
}

bool button_is_pressed(button_id_t button_id) {
    if (button_id >= BUTTON_ID_COUNT) {
        return false;
    }

    // Atomowe odczytanie i skasowanie flagi
    if (buttons[button_id].pressed_flag) {
        buttons[button_id].pressed_flag = false;
        return true;
    }
    return false;
}

void buttons_irq_callback(uint16_t GPIO_Pin) {
    for (int i = 0; i < BUTTON_ID_COUNT; i++) {
        if (GPIO_Pin == buttons[i].pin) {
            // Rozpocznij debouncing tylko jeśli nie jest już w trakcie
            if (!buttons[i].is_debouncing) {
                buttons[i].is_debouncing = true;
                buttons[i].debounce_start = HAL_GetTick();
            }
            break; // Znaleziono przycisk, można wyjść z pętli
        }
    }
}
