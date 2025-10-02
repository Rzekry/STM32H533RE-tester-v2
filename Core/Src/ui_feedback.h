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
 * @brief Uruchamia standardową, krótką sygnalizację akcji użytkownika.
 * @note Domyślnie: mignięcie niebieską diodą i krótki dźwięk buzzera (10ms).
 */
void ui_feedback_signal_action(void);

#endif /* INC_UI_FEEDBACK_H_ */