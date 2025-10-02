/*
 * ui_feedback.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "ui_feedback.h"
#include "led_manager.h"
#include "buzzer.h"
#include <stdbool.h>

#define ACTION_FEEDBACK_DURATION_MS 10

static bool is_feedback_active = false;
static uint32_t feedback_start_time = 0;

/**
 * @brief Rozpoczyna standardową, krótką sygnalizację akcji użytkownika.
 * @note Ta funkcja jest nieblokująca.
 */
void ui_feedback_signal_action(void) {
    if (!is_feedback_active) {
        led_on(LED_ID_BLUE);
        buzzer_on();
        is_feedback_active = true;
        feedback_start_time = HAL_GetTick();
    }
}

/**
 * @brief Przetwarza stan sygnalizacji (wyłącza ją po zadanym czasie).
 * @note Ta funkcja powinna być wywoływana cyklicznie w pętli głównej.
 */
void ui_feedback_process(void) {
    if (is_feedback_active && (HAL_GetTick() - feedback_start_time >= ACTION_FEEDBACK_DURATION_MS)) {
        led_off(LED_ID_BLUE);
        buzzer_off();
        is_feedback_active = false;
    }
}