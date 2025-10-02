/*
 * startup_sequence.c
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#include "startup_sequence.h"
#include "led_manager.h"
#include "buzzer.h"

// Definicja stanów sekwencji
typedef enum {
    SEQ_STATE_IDLE,
    SEQ_STATE_RED_ON,
    SEQ_STATE_RED_OFF,
    SEQ_STATE_BLUE_ON,
    SEQ_STATE_BLUE_OFF,
    SEQ_STATE_GREEN_ON,
    SEQ_STATE_DONE
} sequence_state_t;

static sequence_state_t current_state = SEQ_STATE_IDLE;
static uint32_t last_change_time = 0;

void startup_sequence_start(void) {
    current_state = SEQ_STATE_RED_ON;
    last_change_time = HAL_GetTick();
}

bool startup_sequence_process(void) {
    if (current_state == SEQ_STATE_IDLE || current_state == SEQ_STATE_DONE) {
        return false; // Sekwencja nieaktywna lub zakończona
    }

    uint32_t current_time = HAL_GetTick();

    switch (current_state) {
        case SEQ_STATE_RED_ON:
            led_on(LED_ID_RED);
            buzzer_on();
            last_change_time = current_time;
            current_state = SEQ_STATE_RED_OFF;
            break;

        case SEQ_STATE_RED_OFF:
            if (current_time - last_change_time >= 30) {
                led_off(LED_ID_RED);
                buzzer_off();
                last_change_time = current_time;
                current_state = SEQ_STATE_BLUE_ON;
            }
            break;

        case SEQ_STATE_BLUE_ON:
            if (current_time - last_change_time >= 30) { // Czas pauzy
                led_on(LED_ID_BLUE);
                buzzer_on();
                last_change_time = current_time;
                current_state = SEQ_STATE_BLUE_OFF;
            }
            break;

        case SEQ_STATE_BLUE_OFF:
            if (current_time - last_change_time >= 30) {
                led_off(LED_ID_BLUE);
                buzzer_off();
                last_change_time = current_time;
                current_state = SEQ_STATE_GREEN_ON;
            }
            break;

        case SEQ_STATE_GREEN_ON:
            if (current_time - last_change_time >= 30) { // Czas pauzy
                led_on(LED_ID_GREEN);
                buzzer_beep(30); // Ostatni może być blokujący, bo i tak kończymy
                led_off(LED_ID_GREEN);
                current_state = SEQ_STATE_DONE;
            }
            break;

        default:
            // Stany IDLE i DONE są obsługiwane na początku
            break;
    }

    return (current_state != SEQ_STATE_DONE);
}