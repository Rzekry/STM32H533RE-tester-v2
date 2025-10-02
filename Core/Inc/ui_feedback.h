/*
 * ui_feedback.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_UI_FEEDBACK_H_
#define INC_UI_FEEDBACK_H_

#include "main.h"

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

#endif /* INC_UI_FEEDBACK_H_ */