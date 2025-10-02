/*
 * encoder.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"

/**
 * @brief Inicjalizuje i uruchamia timer w trybie enkodera.
 */
void encoder_init(void);

/**
 * @brief Odczytuje zmianę pozycji enkodera od ostatniego wywołania.
 *
 * @note Funkcja akumuluje impulsy z licznika timera i zwraca wyłącznie
 *       pełne kroki (ząbki) enkodera. Dodatni wynik oznacza obrót w prawo,
 *       ujemny w lewo.
 *
 * @return int16_t Zmiana pozycji (w krokach) od ostatniego wywołania.
*/
int16_t encoder_get_change(void);


#endif /* INC_ENCODER_H_ */
