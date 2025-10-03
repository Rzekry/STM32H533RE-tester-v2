/*
 * ui_feedback.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_UI_FEEDBACK_H_
#define INC_UI_FEEDBACK_H_

#include "main.h"
#include <stdbool.h>

/**
 * @brief Rozpoczyna standardową, krótką sygnalizację akcji użytkownika.
 * @note Ta funkcja jest nieblokująca. Domyślnie: mignięcie niebieską diodą i krótki dźwięk buzzera.
 */
void ui_feedback_signal_action(void);

/**
 * @brief Przetwarza stan sygnalizacji (wyłącza ją po zadanym czasie).
 * @note Ta funkcja powinna być wywoływana cyklicznie w pętli głównej.
 */
void ui_feedback_process(void);

/**
 * @brief Sygnalizuje pozytywny wynik testu.
 * @note Nieblokująca. Sekwencja:
 *       - LED zielona: włączona na 100ms.
 *       - Buzzer: 30ms ON, 30ms OFF, 30ms ON.
 */
void ui_feedback_signal_test_success(void);

/**
 * @brief Sygnalizuje negatywny wynik testu.
 * @note Nieblokująca. Sekwencja:
 *       - LED czerwona: włączona na 250ms.
 *       - Buzzer: 100ms ON, 50ms OFF, 100ms ON.
 */
void ui_feedback_signal_test_fail(void);

/**
 * @brief Sprawdza, czy jakakolwiek sekwencja zwrotna jest aktualnie odtwarzana.
 * @return true, jeśli moduł jest zajęty, w przeciwnym razie false.
 */
bool ui_feedback_is_busy(void);

#endif /* INC_UI_FEEDBACK_H_ */