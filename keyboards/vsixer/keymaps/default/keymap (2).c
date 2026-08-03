// Copyright 2024 Vsixer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "service/language_controller.h"
#include "process_record.c"

//region Инициализация
LanguageController* langCtrl;

void keyboard_post_init_user(void) {
    langCtrl = createLanguageController();
}
// endregion

// Enum для tap dance
enum {
    TD_RU_Z = 0, // ж => з
    TD_RU_H = 1 // д -> х
};

//region Слои
#define ENT_NAV LT(_NAV, KC_ENT) // Enter при нажатии, слой навигации при удержании
#define ESC_SYM LT(_SYM, KC_ESC) // Escape при нажатии, слой символов при удержании
#define ESC_GAME_ADD LT(_GAME_ADDITIONAL, KC_ESC) // Escape при нажатии, слой доп игровой

#define TAB_SFT LSFT_T(KC_TAB) // Tab при нажатии, Shift при удержании
#define DEL_CTR LCTL_T(KC_DEL) // Delete при нажатии, Ctrl при удержании
#define SEL_RGHT LCTL(LSFT(KC_RGHT)) // Выделить слово правее
#define SEL_LEFT LCTL(LSFT(KC_LEFT)) // Выделить слово левее
#define CHG_PREV LCTL(LSFT(LALT(KC_UP))) // Предыдущее изменение
#define CHG_NEXT LCTL(LSFT(LALT(KC_DOWN))) // Следующее изменение
#define SWTCH_AUD LCTL(LALT(KC_F11)) // Переключить вывод звука
#define SELCT_MODE LSFT(LALT(KC_INSERT)) // Режим выделения
#define SCRNSHT LGUI(LSFT(KC_S)) // Скриншот
#define USG_HLGH LCTL(LSFT(KC_F7)) // Подсветка выделения в PhpStorm
#define GC_COMPL C(A(KC_COMMA)) // Force GigaCode Completion

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_4x6_5(
        KC_F12,     KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,    KC_F8,      KC_F9,       KC_F10,       KC_F11,
        KC_GRAVE,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,     KC_I,       KC_O,        KC_P,         KC_LBRC,
        TAB_SFT,    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,     KC_K,       KC_L,        KC_SCLN,      KC_QUOT,
        KC_LALT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,     KC_COMM,    KC_DOT,      UNI_DOT_COM,  KC_RBRC,
                                     DEL_CTR, KC_LSFT, ESC_SYM,       ENT_NAV, KC_SPC,   KC_BSPC,
                                              KC_LGUI, ENT_NAV,       XXXXXXX, XXXXXXX
    ),

    [_RU] = LAYOUT_split_4x6_5(
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
        _______, KC_B,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_P,    _______,
        _______, KC_Z,    _______, KC_C,    KC_V,    _______,           _______, _______, KC_COMM, _______, _______, _______,
                                   _______, _______, _______,           _______, _______, _______,
                                            _______, _______,           _______, _______
    ),

    [_NAV] = LAYOUT_split_4x6_5(
        XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,    KC_HOME,  KC_UP,   KC_END,   XXXXXXX,           KC_PAST, KC_7,    KC_8,    KC_9,    KC_PSLS, XXXXXXX,
        XXXXXXX, SEL_LEFT,   KC_LEFT,  KC_DOWN, KC_RGHT,  SEL_RGHT,          KC_PPLS, KC_4,    KC_5,    KC_6,    KC_0,    KC_EQL,
        KC_LALT, SELCT_MODE, CHG_PREV, XXXXXXX, CHG_NEXT, XXXXXXX,           KC_MINS, KC_1,    KC_2,    KC_3,    KC_PDOT, KC_NUM_LOCK,
                                       _______, _______,  _______,           _______, _______, _______,
                                                _______,  _______,           _______, _______
    ),

    [_SYM] = LAYOUT_split_4x6_5(
        KC_VOLD, KC_VOLU, XXXXXXX,  XXXXXXX, XXXXXXX, USG_HLGH,          XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,  KC_PAUSE,
        SCRNSHT, KC_CALC, GC_COMPL, WS_BWD,  WS_FWD,  XXXXXXX,           KC_BSLS,    UNI_AMP,  S(KC_8), UNI_QSTN,  UNI_PIPE, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,           KC_PSLS,    UNI_DLR,  S(KC_5), UNI_CARET, XXXXXXX,  XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, SWTCH_AUD,         S(KC_MINS), S(KC_1),  UNI_AT,  UNI_HASH,  XXXXXXX,  XXXXXXX,
                                    _______, _______, _______,           _______,    _______,  _______,
                                             _______, _______,           MO(_SYS),   TG(_GAME)
    ),

    [_GAME] = LAYOUT_split_4x6_5(
        KC_ESC,  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,              KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
        XXXXXXX, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,
        XXXXXXX, KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_LALT, KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_RSFT,
                                   KC_G,    KC_SPC,  ESC_GAME_ADD,      _______, _______, _______,
                                            KC_T,    KC_ENT,            _______, _______
    ),

    [_GAME_ADDITIONAL] = LAYOUT_split_4x6_5(
        KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUSE,
        XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_T,              XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_G,              XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_0,    KC_7,    KC_8,    KC_9,    KC_B,              XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,           _______,  _______, _______,
                                            _______, _______,           MO(_SYS), TG(_GAME)
    ),

    [_SYS] = LAYOUT_split_4x6_5(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADJUST_LNG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,           _______, _______, _______,
                                            _______, _______,           _______, _______
    ),

    [_TYPE] = LAYOUT_split_4x6_5(
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_GRAVE,          _______, _______, _______, _______, _______, _______,
        _______, KC_Q,    _______, _______, KC_B,    KC_T,              KC_Y,    KC_N,    _______, KC_LBRC, KC_P,    _______,
        _______, _______, _______, _______, _______, _______,           _______, KC_RBRC, _______, _______, KC_QUOT, _______,
                                   _______, _______, _______,           _______, _______, _______,
                                            _______, _______,           _______, _______
    )

//    [_NAME] = LAYOUT_split_4x6_5(
//        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
//                                   _______, _______, _______,           _______, _______, _______,
//                                            _______, _______,           _______, _______
//    )

//    [_NAME] = LAYOUT_split_4x6_5(
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//                                   _______, _______, _______,           _______, _______, _______,
//                                            _______, _______,           _______, _______
//    )

};
//endregion

//region Combos
enum combos {
    RND_BRC_LEFT,
    RND_BRC_RIGHT,
    SQ_BRC_LEFT,
    SQ_BRC_RIGHT,
    COLON,
    QUOTE,
    BACKTICK,
    ARROW_RIGHT,
    SWTCH_LNG_RU,
    SWTCH_LNG_EN,
    COPY_PASTE,
    COMMENT,
};

const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END}; // Скобка "("
const uint16_t PROGMEM sf_combo[] = {KC_S, KC_F, COMBO_END}; // Скобка ")"
const uint16_t PROGMEM sq_brc_left_combo[] = {KC_U, KC_O, COMBO_END}; // Скобка "["
const uint16_t PROGMEM sq_brc_right_combo[] = {KC_W, KC_R, COMBO_END}; // Скобка "]"
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END}; // Двоеточие
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END}; // Кавычка
const uint16_t PROGMEM sdf_combo[] = {KC_S, KC_D, KC_F, COMBO_END}; // `
const uint16_t PROGMEM arrow_combo[] = {KC_M, KC_COMM, COMBO_END}; // Стрелка
const uint16_t PROGMEM lng_ru_combo[] = {KC_D, KC_F, COMBO_END}; // Переключение языка на русский
const uint16_t PROGMEM lng_en_combo[] = {KC_J, KC_K, COMBO_END}; // Переключение языка на английский
const uint16_t PROGMEM copy_paste_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM comment_combo[] = {KC_H, KC_K, COMBO_END};

combo_t key_combos[] = {
    [RND_BRC_LEFT] = COMBO_ACTION(jl_combo),
    [RND_BRC_RIGHT] = COMBO_ACTION(sf_combo),
    [SQ_BRC_LEFT] = COMBO_ACTION(sq_brc_left_combo),
    [SQ_BRC_RIGHT] = COMBO_ACTION(sq_brc_right_combo),
    [COLON] = COMBO_ACTION(kl_combo),
    [QUOTE] = COMBO_ACTION(sd_combo),
    [BACKTICK] = COMBO_ACTION(sdf_combo),
    [ARROW_RIGHT] = COMBO_ACTION(arrow_combo),
    [SWTCH_LNG_RU] = COMBO_ACTION(lng_ru_combo),
    [SWTCH_LNG_EN] = COMBO_ACTION(lng_en_combo),
    [COPY_PASTE] = COMBO_ACTION(copy_paste_combo),
    [COMMENT] = COMBO_ACTION(comment_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case SQ_BRC_LEFT:
            if (pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(KC_LBRC);
                });
            }
            break;
        case SQ_BRC_RIGHT:
            if (pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(KC_RBRC);
                });
            }
            break;
        case RND_BRC_LEFT:
            if (pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    WITH_LANG_SWITCH({
                        tap_code16(KC_LBRC);
                    });
                } else {
                    tap_code16(S(KC_9));
                }
            }
            break;
        case RND_BRC_RIGHT:
            if (pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    WITH_LANG_SWITCH({
                        tap_code16(KC_RBRC);
                    });
                } else {
                    tap_code16(S(KC_0));
                }
            }
            break;
        case ARROW_RIGHT:
            if (pressed) {
                const char* stringToSend = (get_mods() & MOD_MASK_SHIFT) ? "=>" : "->";
                WITH_LANG_SWITCH({
                    unregister_code(KC_LSFT);  // Отключаем Shift
                    send_string(stringToSend);
                });
            }
            break;
        case SWTCH_LNG_RU:
            if (pressed) {
                langCtrl->switchLangRu();
            }
            break;
        case SWTCH_LNG_EN:
            if (pressed) {
                langCtrl->switchLangEn();
            }
            break;
        case COLON:
            if (pressed) {
                WITH_LANG_SWITCH({
                   tap_code16(KC_SCLN);
                });
            }
            break;
        case QUOTE:
            if (pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(KC_QUOT);
                });
            }
            break;
        case BACKTICK:
            if (pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(KC_GRAVE);
                });
            }
            break;
        case COPY_PASTE:
            if (pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSFT);
                    tap_code16(C(KC_V));
                    register_code(KC_LSFT);
                } else {
                    tap_code16(C(KC_C));
                }
            }
            break;
        case COMMENT:
            if (pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(C(KC_SLASH));
                });
            }
            break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case RND_BRC_LEFT:
            return 40;
        case RND_BRC_RIGHT:
            return 40;
        default:
            return COMBO_TERM;
    }
}
//endregion

//region Tap dance
tap_dance_action_t tap_dance_actions[] = {
    [TD_RU_Z] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_P),
    [TD_RU_H] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_LBRC)
};
//endregion

//region Retro tapping
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_TYPE, KC_SPC):
            return true;
        default:
            return false;
    }
}
//endregionаа