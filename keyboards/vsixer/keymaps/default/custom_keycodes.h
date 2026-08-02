#pragma once
#include QMK_KEYBOARD_H

enum custom_keycodes {
    UNI_DOT_COM = SAFE_RANGE,
    UNI_QSTN,
    UNI_AMP,
    UNI_AT,
    UNI_HASH,
    UNI_DLR,
    UNI_PIPE,
    UNI_CARET,
//    UNI_TILDE,

    ADJUST_LNG,
    WS_FWD,
    WS_BWD,
    CPS_BLK,

    NEW_SAFE_RANGE  // Всегда оставляйте это в конце enum
};

// Слои
#define _BASE 0 // Слой основной
#define _GAME 1 // Слой игровой
#define _GAME_ADDITIONAL 2 // Слой игровой дополнительный
#define _TYPE 3 // Слой печати
#define _SYM  4 // Слой символов
#define _NAV  5 // Слой навигации
#define _SYS  6 // Слой системный
#define _RU 7   // Слой русского языка
#define _MOUSE 8 // Слой мыши
#define _NAV_ALT 9 // Слой навигации альтернативный


//Слой 0 (Базовый):
//
//20 самых частых букв русского языка (о, е, а, и, н, т, с, р, в, л, к, м, п, у, я, ы, д, з, б, г).
//
//Примерно покрывает ~85% текста.
//
//Слой 1 (Дополнительные буквы):
//
//Оставшиеся 13 букв (ч, й, ф, х, ц, ж, ш, щ, э, ю, ъ, ь, ё) + символы (., , / ? !).
//
//Активация через удержание пробела, кнопки-модификатора или LT(layer, key).


// е, н, т, к, у, г