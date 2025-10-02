/*
 * app.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "app.h"

// Sterowniki i moduły używane przez aplikację
#include "main.h"
#include "led_manager.h"
#include "buttons.h"
#include "encoder.h"
#include "ui_feedback.h"
#include "startup_sequence.h"
#include "logger.h"
#include "breathing_led.h"

// Deklaracja zewnętrznej zmiennej dla timera buzzera
extern TIM_HandleTypeDef htim3;

void app_init(void) {
    // Inicjalizacja modułów, które są częścią logiki aplikacji
    leds_init();
    buttons_init();
    logger_init();
    encoder_init();
    breathing_led_init();

    // Uruchomienie PWM dla buzzera
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    // Uruchomienie sekwencji startowej
    startup_sequence_start();
}

void app_process(void) {
    // Przetwarzaj sekwencję startową, dopóki się nie zakończy
    if (startup_sequence_process()) {
        return; // Pomiń resztę logiki, dopóki trwa sekwencja
    }

    // Cykliczne przetwarzanie modułów
    buttons_process();
    ui_feedback_process();
    breathing_led_process();

    bool action_detected = false;

    int16_t enc_change = encoder_get_change();
    if (enc_change != 0) {
        action_detected = true;
        log_debug("APP", "Encoder change: %d", enc_change);
    }

    for (button_id_t i = 0; i < BUTTON_ID_COUNT; i++) {
        if (button_is_pressed(i)) {
            action_detected = true;
            log_debug("APP", "Button %d pressed", i);
            if (i == BUTTON_ID_USER) {
                led_toggle(LED_ID_NUCLEO_GREEN);
            }
        }
    }

    if (action_detected) {
        ui_feedback_signal_action();
    }
}