#include "logger.h"
#include "main.h" // Potrzebne dla HAL_GetTick()

// Tablica stringów dla poziomów logowania
static const char* level_strings[] = {
    "DEBUG", "INFO", "WARN", "ERROR"
};

void logger_init(void) {
    // W przyszłości można tu dodać inicjalizację np. timestampa
}

void logger_log(log_level_t level, const char* module, const char* format, ...) {
    // Sprawdź, czy poziom logowania jest wystarczająco wysoki
    if (level < LOGGER_LEVEL) {
        return;
    }

    // Bufor na sformatowaną wiadomość
    char buffer[256];
    va_list args;

    // Rozpocznij przetwarzanie zmiennych argumentów
    va_start(args, format);
    // Sformatuj wiadomość użytkownika do bufora
    vsnprintf(buffer, sizeof(buffer), format, args);
    // Zakończ przetwarzanie
    va_end(args);

    // Wydrukuj sformatowany log przez printf (który idzie na UART)
    // Format: [timestamp_ms][LEVEL][MODUŁ] wiadomość
    printf("[%lu][%s][%s] %s\r\n",
           HAL_GetTick(),
           level_strings[level],
           module,
           buffer);
}
