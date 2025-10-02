/*
 * startup_sequence.h
 *
 *  Created on: 29 maj 2025
 *      Author: Krystian
 */

#ifndef INC_STARTUP_SEQUENCE_H_
#define INC_STARTUP_SEQUENCE_H_

#include "main.h"
#include <stdbool.h>

/**
 * @brief Rozpoczyna nieblokującą sekwencję startową.
 */
void startup_sequence_start(void);

/**
 * @brief Przetwarza kolejne kroki sekwencji startowej.
 * @note Powinna być wywoływana cyklicznie w pętli głównej.
 * @return true, jeśli sekwencja jest wciąż aktywna, false po jej zakończeniu.
 */
bool startup_sequence_process(void);


#endif /* INC_STARTUP_SEQUENCE_H_ */