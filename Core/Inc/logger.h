#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include <stdio.h>
#include <stdarg.h>

// Definicja poziomów logowania
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} log_level_t;

// Ustawienie globalnego poziomu logowania
// Wiadomości o niższym priorytecie nie będą drukowane
#define LOGGER_LEVEL LOG_LEVEL_DEBUG

// Funkcja inicjalizująca (na razie pusta, ale może się przydać)
void logger_init(void);

// Główna funkcja logująca (wewnętrzna)
void logger_log(log_level_t level, const char* module, const char* format, ...);

// Makra ułatwiające korzystanie z loggera
// Dzięki __VA_ARGS__ możemy przekazywać zmienną liczbę argumentów jak w printf
#define log_debug(module, ...) logger_log(LOG_LEVEL_DEBUG, module, __VA_ARGS__)
#define log_info(module, ...)  logger_log(LOG_LEVEL_INFO,  module, __VA_ARGS__)
#define log_warn(module, ...)  logger_log(LOG_LEVEL_WARN,  module, __VA_ARGS__)
#define log_error(module, ...) logger_log(LOG_LEVEL_ERROR, module, __VA_ARGS__)

#endif /* INC_LOGGER_H_ */
