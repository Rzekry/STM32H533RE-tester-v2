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
 * @note Zwraca liczbę "kroków" enkodera. W zależności od konfiguracji
 *       i typu enkodera, jeden "ząbek" może odpowiadać 2 lub 4 krokom.
 *       Np. jeśli funkcja zwróci 4, oznacza to obrót o jeden ząbek w prawo.
 *       Jeśli zwróci -4, oznacza to obrót o jeden ząbek w lewo.
 *
 * @return int16_t Zmiana pozycji (dodatnia dla obrotu w prawo, ujemna dla obrotu w lewo).
 */
int16_t encoder_get_change(void);


#endif /* INC_ENCODER_H_ */