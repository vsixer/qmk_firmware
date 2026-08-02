#pragma once
#include "quantum.h"

// Константы для языков
#define LANG_EN 0
#define LANG_RU 1
#define LANG_AUTO 0xFF

// "Класс" LanguageController
typedef struct {
    void (*switchLang)(void);
    void (*switchLangRu)(void);
    void (*switchLangEn)(void);
    uint8_t (*getCurrentLang)(void);
    void (*setLang)(uint8_t lang);
} LanguageController;

// Макрос для временного переключения раскладки
#define WITH_LANG_SWITCH(action) \
    do { \
        const uint8_t _prev_lang = langCtrl->getCurrentLang(); \
        if (_prev_lang != LANG_EN) { \
            langCtrl->switchLangEn(); \
        } \
        { action; } \
        if (_prev_lang == LANG_RU) { \
            langCtrl->switchLangRu(); \
        } \
    } while (0)

// "Конструктор" (инициализация)
LanguageController* createLanguageController(void);