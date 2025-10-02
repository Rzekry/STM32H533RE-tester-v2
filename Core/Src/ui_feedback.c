/*
 * ui_feedback.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "ui_feedback.h"
#include "led_manager.h"
#include "buzzer.h"

#define ACTION_FEEDBACK_DURATION_MS 10

/**
 * @brief Uruchamia standardową, krótką sygnalizację akcji użytkownika.
 * @note Ta funkcja jest blokująca na czas trwania sygnalizacji.
 */
void ui_feedback_signal_action(void) {
    led_on(LED_ID_BLUE);
    buzzer_on();
    HAL_Delay(ACTION_FEEDBACK_DURATION_MS);
    led_off(LED_ID_BLUE);
    buzzer_off();
}