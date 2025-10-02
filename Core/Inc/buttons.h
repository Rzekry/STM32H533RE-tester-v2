/*
 * buttons.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include "main.h"
#include <stdbool.h>

// Identyfikatory wszystkich przycisków w systemie
typedef enum {
    BUTTON_ID_ENCODER,
    BUTTON_ID_TEST,
    BUTTON_ID_USER,
    BUTTON_ID_COUNT // Ilość przycisków
} button_id_t;

/**
 * @brief Inicjalizuje moduł przycisków.
 * @note Ta funkcja powinna być wywołana po inicjalizacji GPIO.
 */
void buttons_init(void);

/**
 * @brief Przetwarza stan przycisków (debouncing).
 * @note Ta funkcja powinna być wywoływana cyklicznie, np. co 1-10 ms w pętli głównej lub przerwaniu timera.
 */
void buttons_process(void);

/**
 * @brief Sprawdza, czy przycisk został właśnie wciśnięty.
 * @param button_id Identyfikator przycisku.
 * @return true, jeśli przycisk został wciśnięty (zdarzenie jednorazowe), w przeciwnym razie false.
 */
bool button_is_pressed(button_id_t button_id);

/**
 * @brief Funkcja zwrotna (callback) wywoływana z przerwania EXTI.
 * @param GPIO_Pin Numer pinu, który wywołał przerwanie.
 */
void buttons_irq_callback(uint16_t GPIO_Pin);

#endif /* INC_BUTTONS_H_ */