/*
 * app.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_APP_H_
#define INC_APP_H_

/**
 * @brief Inicjalizuje moduł aplikacji.
 */
void app_init(void);

/**
 * @brief Główna funkcja przetwarzająca logikę aplikacji.
 * @note Powinna być wywoływana cyklicznie w pętli while(1).
 */
void app_process(void);

#endif /* INC_APP_H_ */