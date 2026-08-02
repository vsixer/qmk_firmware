#include "language_controller.h"
#include "action_util.h"

static uint8_t current_lang = LANG_RU;

static uint8_t _get_current_language(void) {
    return current_lang;
}

static void _perform_switch(uint8_t lang) {
    tap_code16(C(G(KC_SPC)));
    current_lang = lang;
    wait_ms(50); // Краткая задержка для ОС
}

static void _switch_language(void) {
    int8_t lang = current_lang == LANG_RU ? LANG_EN : LANG_RU;
    _perform_switch(lang);
}

static void _switch_language_ru(void) {
    if (_get_current_language() == LANG_RU) {
        return;
    }

    _perform_switch(LANG_RU);
}

static void _switch_language_en(void) {
    if (_get_current_language() == LANG_EN) {
        return;
    }

    _perform_switch(LANG_EN);
}

static void _set_language(uint8_t lang) {
    if (lang != current_lang) {
        current_lang = lang;
    }
}

// "Конструктор"
LanguageController* createLanguageController(void) {
    // Статический экземпляр
    static LanguageController instance = {
        .switchLang = _switch_language,
        .switchLangRu = _switch_language_ru,
        .switchLangEn = _switch_language_en,
        .getCurrentLang = _get_current_language,
        .setLang = _set_language
    };
    return &instance;
}