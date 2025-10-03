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

// Stany dla sekwencji testowej po starcie
typedef enum {
    APP_STATE_STARTUP_SEQUENCE,
    APP_STATE_RUNNING
} app_state_t;

static app_state_t app_current_state = APP_STATE_STARTUP_SEQUENCE;

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
    // Cykliczne przetwarzanie modułów, które muszą działać zawsze
    ui_feedback_process();
    
    switch (app_current_state) {
        case APP_STATE_STARTUP_SEQUENCE:
            if (!startup_sequence_process()) {
                // Sekwencja startowa zakończona, przejdź do normalnego działania
                app_current_state = APP_STATE_RUNNING;
            }
            break;
            
        case APP_STATE_RUNNING:
            // Normalna pętla aplikacji
            buttons_process();
            breathing_led_process();
            
            bool action_detected = false;
            if (encoder_get_change() != 0) action_detected = true;
            for (button_id_t i = 0; i < BUTTON_ID_COUNT; i++) {
                if (button_is_pressed(i)) {
                    action_detected = true;
                    log_debug("APP", "Button %d pressed", i);
                    if (i == BUTTON_ID_USER) led_toggle(LED_ID_NUCLEO_GREEN);
                }
            }
            if (action_detected) ui_feedback_signal_action();
            break;
    }
}