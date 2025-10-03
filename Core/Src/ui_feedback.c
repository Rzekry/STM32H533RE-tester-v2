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

// Definicja typów sygnałów zwrotnych
typedef enum {
    FEEDBACK_TYPE_NONE,
    FEEDBACK_TYPE_ACTION,
    FEEDBACK_TYPE_TEST_SUCCESS,
    FEEDBACK_TYPE_TEST_FAIL,
} feedback_type_t;

// Zmienne stanu
static feedback_type_t active_feedback = FEEDBACK_TYPE_NONE;
static uint32_t feedback_start_time = 0;

/**
 * @brief Rozpoczyna nowy sygnał zwrotny, jeśli żaden inny nie jest aktywny.
 * @param type Typ sygnału do uruchomienia.
 */
static void start_feedback(feedback_type_t type) {
    if (active_feedback == FEEDBACK_TYPE_NONE) {
        active_feedback = type;
        feedback_start_time = HAL_GetTick();
    }
}

/**
 * @brief Rozpoczyna standardową, krótką sygnalizację akcji użytkownika.
 * @note Ta funkcja jest nieblokująca.
 */
void ui_feedback_signal_action(void) {
    start_feedback(FEEDBACK_TYPE_ACTION);
}

/**
 * @brief Sygnalizuje pozytywny wynik testu.
 */
void ui_feedback_signal_test_success(void) {
    start_feedback(FEEDBACK_TYPE_TEST_SUCCESS);
}

/**
 * @brief Sygnalizuje negatywny wynik testu.
 */
void ui_feedback_signal_test_fail(void) {
    start_feedback(FEEDBACK_TYPE_TEST_FAIL);
}

/**
 * @brief Sprawdza, czy jakakolwiek sekwencja zwrotna jest aktualnie odtwarzana.
 */
bool ui_feedback_is_busy(void) {
    return active_feedback != FEEDBACK_TYPE_NONE;
}

/**
 * @brief Przetwarza stan sygnalizacji (wyłącza ją po zadanym czasie).
 * @note Ta funkcja powinna być wywoływana cyklicznie w pętli głównej.
 */
void ui_feedback_process(void) {
    if (active_feedback == FEEDBACK_TYPE_NONE) {
        return;
    }

    uint32_t elapsed_time = HAL_GetTick() - feedback_start_time;

    switch (active_feedback) {
        case FEEDBACK_TYPE_ACTION:
            if (elapsed_time == 0) { // Uruchomienie
                led_on(LED_ID_BLUE);
                buzzer_on();
            } else if (elapsed_time >= 10) { // Zakończenie
                led_off(LED_ID_BLUE);
                buzzer_off();
                active_feedback = FEEDBACK_TYPE_NONE;
            }
            break;

        case FEEDBACK_TYPE_TEST_SUCCESS:
            if (elapsed_time == 0) { // Uruchomienie
                led_on(LED_ID_GREEN);
            }

            // Buzzer: 30ms ON, 30ms OFF, 30ms ON
            if (elapsed_time < 30) buzzer_on();
            else if (elapsed_time < 60) buzzer_off();
            else if (elapsed_time < 90) buzzer_on();
            else buzzer_off();

            // Zakończenie całej sekwencji
            if (elapsed_time >= 200) {
                led_off(LED_ID_GREEN);
                buzzer_off(); // Upewnij się, że buzzer jest wyłączony
                active_feedback = FEEDBACK_TYPE_NONE;
            }
            break;

        case FEEDBACK_TYPE_TEST_FAIL:
            if (elapsed_time == 0) { // Uruchomienie
                led_on(LED_ID_RED);
            }

            // Buzzer: 100ms ON, 50ms OFF, 100ms ON
            if (elapsed_time < 100) buzzer_on();
            else if (elapsed_time < 150) buzzer_off();
            else if (elapsed_time < 250) buzzer_on();
            else buzzer_off();

            // Zakończenie całej sekwencji
            if (elapsed_time >= 500) {
                led_off(LED_ID_RED);
                buzzer_off(); // Upewnij się, że buzzer jest wyłączony
                active_feedback = FEEDBACK_TYPE_NONE;
            }
            break;

        case FEEDBACK_TYPE_NONE:
        default:
            break;
    }
}