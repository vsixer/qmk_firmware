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

//region Слои
#define ENT_NAV LT(_NAV, KC_ENT) // Enter при нажатии, слой навигации при удержании
#define ESC_SYM LT(_SYM, KC_ESC) // Escape при нажатии, слой символов при удержании
#define ESC_GAME_ADD LT(_GAME_ADDITIONAL, KC_ESC) // Escape при нажатии, слой доп игровой
// #define SPC_TYPE LT(_TYPE, KC_SPC) // Space при нажатии, слой типографики при удержании

#define TAB_SFT LSFT_T(KC_TAB) // Tab при нажатии, Shift при удержании
#define DEL_CTR LCTL_T(KC_DEL) // Delete при нажатии, Ctrl при удержании
#define SEL_RGHT LCTL(LSFT(KC_RGHT)) // Выделить слово правее
#define SEL_LEFT LCTL(LSFT(KC_LEFT)) // Выделить слово левее
#define CHG_PREV LCTL(LSFT(LALT(KC_UP))) // Предыдущее изменение
#define CHG_NEXT LCTL(LSFT(LALT(KC_DOWN))) // Следующее изменение
#define SWTCH_AUD LCTL(LALT(KC_F11)) // Переключить вывод звука
#define SELCT_MODE LSFT(LALT(KC_INSERT)) // Режим выделения
#define SCRNSHT LGUI(LSFT(KC_S)) // Скриншот
#define GC_COMPL C(A(KC_COMMA)) // Force GigaCode Completion
#define CTRL_ALT_DEL LCTL(LALT(KC_DEL)) // Ctrl + Alt + Delete

#define SW_TERM LGUI(KC_F12) // Переключить терминал
#define SW_STRM LGUI(KC_1) // Переключить на phpstorm
#define SW_BWSR LGUI(KC_2) // Переключить на браузер
#define SW_APP4 LGUI(KC_4) // Переключить приложение 4
#define SW_APP5 LGUI(KC_5) // Переключить приложение 5
#define SW_APP6 LGUI(KC_6) // Переключить приложение 6

#define USG_HLGH LCTL(LSFT(KC_F7)) // Подсветка выделения в PhpStorm
#define CPS_ALL C(S(KC_MINS)) //d Свернуть всё
#define EXP_BLK C(A(KC_PPLS)) // Развернуть блок

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_4x6_5(
        KC_F12,     KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,      KC_F7,    KC_F8,      KC_F9,     KC_F10,      KC_F11,
        KC_GRAVE,   KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,       KC_U,     KC_I,       KC_O,      KC_P,        KC_LBRC,
        TAB_SFT,    KC_A,      KC_S,    KC_D,    KC_F,    KC_G,          KC_H,       KC_J,     KC_K,       KC_L,      KC_SCLN,     KC_QUOT,
        KC_LALT,    KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,          KC_N,       KC_M,     KC_COMM,    KC_DOT,    UNI_DOT_COM, KC_RBRC,
                                        DEL_CTR, KC_LSFT, ESC_SYM,       ENT_NAV,    KC_SPC,   KC_BSPC,
                                                 KC_LGUI, ENT_NAV,       MO(_NAV_ALT), XXXXXXX
    ),

    [_NAV] = LAYOUT_split_4x6_5(
        XXXXXXX, XXXXXXX,    XXXXXXX,  KC_PGUP, XXXXXXX,  XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,
        KC_LCTL, XXXXXXX,    KC_HOME,  KC_UP,   KC_END,   XXXXXXX,           KC_PAST, KC_7,    KC_8,    KC_9,    KC_PSLS,     XXXXXXX,
        KC_LSFT, SEL_LEFT,   KC_LEFT,  KC_DOWN, KC_RGHT,  SEL_RGHT,          KC_PPLS, KC_4,    KC_5,    KC_6,    KC_0,        KC_EQL,
        KC_LALT, SELCT_MODE, CHG_PREV, KC_PGDN, CHG_NEXT, XXXXXXX,           KC_MINS, KC_1,    KC_2,    KC_3,    UNI_DOT_COM, KC_NUM_LOCK,
                                       _______, _______,  MO(_NAV_ALT),      _______, _______, _______,
                                                _______,  _______,           _______, _______
    ),

    [_NAV_ALT] = LAYOUT_split_4x6_5(
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,           _______, KC_F7,   KC_F8,   KC_F9,   _______, _______,
        _______, _______, _______, _______, _______, _______,           KC_F12,  KC_F4,   KC_F5,   KC_F6,   KC_F10,  _______,
        _______, _______, _______, _______, _______, _______,           _______, KC_F1,   KC_F2,   KC_F3,   KC_F11,  _______,
                                   _______, _______, _______,           _______, _______, _______,
                                            _______, _______,           _______, _______
    ),

    [_SYM] = LAYOUT_split_4x6_5(
        KC_VOLD,   KC_VOLU, XXXXXXX,  CPS_ALL, CPS_BLK, USG_HLGH,          XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,  KC_PAUSE,
        SCRNSHT,   KC_CALC, GC_COMPL, WS_BWD,  WS_FWD,  XXXXXXX,           KC_BSLS,    UNI_AMP,  S(KC_8), UNI_QSTN,  UNI_PIPE, XXXXXXX,
        XXXXXXX,   XXXXXXX, SW_STRM,  SW_BWSR, SW_TERM, XXXXXXX,           KC_PSLS,    UNI_DLR,  S(KC_5), UNI_CARET, XXXXXXX,  XXXXXXX,
        TG(_GAME), XXXXXXX, SW_APP4,  SW_APP5, SW_APP6, SWTCH_AUD,         S(KC_MINS), S(KC_1),  UNI_AT,  UNI_HASH,  XXXXXXX,  XXXXXXX,
                                      _______, _______, _______,           _______,    _______,  _______,
                                               _______, _______,           MO(_SYS),   TG(_GAME)
    ),

    [_GAME] = LAYOUT_split_4x6_5(
        KC_ESC,  XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,              KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
        KC_CAPS, KC_GRAVE, KC_Q,    KC_W,    KC_E,    KC_R,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,
        KC_TAB,  KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_LALT, KC_LALT,  KC_Z,    KC_X,    KC_C,    KC_V,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_RSFT,
                                    KC_LCTL, KC_SPC,  ESC_GAME_ADD,      _______, _______, _______,
                                             KC_M,    ENT_NAV,           _______, _______
    ),

    [_GAME_ADDITIONAL] = LAYOUT_split_4x6_5(
        KC_VOLD,   KC_VOLU, KC_F1,   KC_F2,   KC_F3,   KC_F4,             KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PAUSE,
        KC_F12,    KC_J,    KC_7,    KC_8,    KC_9,    KC_T,              XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F5,     KC_0,    KC_1,    KC_2,    KC_3,    KC_G,              XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        TG(_GAME), KC_I,    KC_4,    KC_5,    KC_6,    KC_B,              XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,           _______,  _______, _______,
                                            _______, _______,           MO(_SYS), TG(_GAME)
    ),

    [_SYS] = LAYOUT_split_4x6_5(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_RU),           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADJUST_LNG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CTRL_ALT_DEL,
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
    ),

    [_RU] = LAYOUT_split_4x6_5(
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
        _______, KC_B,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_P,    _______,
        _______, KC_Z,    _______, KC_C,    KC_V,    _______,           _______, _______, KC_COMM, _______, _______, _______,
                                   _______, _______, _______,           _______, _______, _______,
                                            _______, _______,           _______, _______
    ),

    [_MOUSE] = LAYOUT_split_4x6_5(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, MS_WHLL, MS_UP,   MS_WHLR, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX,           XXXXXXX, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, MS_WHLU, KC_LCTL, MS_WHLD, XXXXXXX,           XXXXXXX, MS_ACL1, MS_ACL0, MS_ACL2, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX
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
    COMMENT,
};

const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END}; // Скобка "("
const uint16_t PROGMEM sf_combo[] = {KC_S, KC_F, COMBO_END}; // Скобка ")"
const uint16_t PROGMEM sq_brc_left_combo[] = {KC_U, KC_O, COMBO_END}; // Скобка "["
const uint16_t PROGMEM sq_brc_right_combo[] = {KC_W, KC_R, COMBO_END}; // Скобка "]"
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END}; // Двоеточие
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END}; // Кавычка
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END}; // `
const uint16_t PROGMEM arrow_combo[] = {KC_M, KC_COMM, COMBO_END}; // Стрелка
const uint16_t PROGMEM lng_ru_combo[] = {KC_D, KC_F, COMBO_END}; // Переключение языка на русский
const uint16_t PROGMEM lng_en_combo[] = {KC_J, KC_K, COMBO_END}; // Переключение языка на английский
const uint16_t PROGMEM comment_combo[] = {KC_H, KC_K, COMBO_END}; // Комментарий

combo_t key_combos[] = {
    [RND_BRC_LEFT] = COMBO_ACTION(jl_combo),
    [RND_BRC_RIGHT] = COMBO_ACTION(sf_combo),
    [SQ_BRC_LEFT] = COMBO_ACTION(sq_brc_left_combo),
    [SQ_BRC_RIGHT] = COMBO_ACTION(sq_brc_right_combo),
    [COLON] = COMBO_ACTION(kl_combo),
    [QUOTE] = COMBO_ACTION(sd_combo),
    [BACKTICK] = COMBO_ACTION(cv_combo),
    [ARROW_RIGHT] = COMBO_ACTION(arrow_combo),
    [SWTCH_LNG_RU] = COMBO_ACTION(lng_ru_combo),
    [SWTCH_LNG_EN] = COMBO_ACTION(lng_en_combo),
    [COMMENT] = COMBO_ACTION(comment_combo),
};

#define BACKTICK_KEY_INTERVAL 10
#define BACKTICK_LANG_SETTLE_DELAY 50

static void switch_backtick_language(uint8_t lang) {
    tap_code16_delay(C(G(KC_SPC)), BACKTICK_KEY_INTERVAL);
    langCtrl->setLang(lang);
    wait_ms(BACKTICK_LANG_SETTLE_DELAY);
}

static void send_backtick_fence(void) {
    const uint8_t previous_lang = langCtrl->getCurrentLang();
    const uint8_t mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
    send_keyboard_report();

    if (previous_lang == LANG_RU) {
        switch_backtick_language(LANG_EN);
    }

    // send_string_with_delay добавляет паузу как при нажатии, так и после
    // отпускания. Это не даёт USB/ОС потерять повторяющиеся клавиши.
    send_string_with_delay("```\n\n```", BACKTICK_KEY_INTERVAL);
    tap_code16_delay(KC_UP, BACKTICK_KEY_INTERVAL);
    wait_ms(BACKTICK_KEY_INTERVAL);

    if (previous_lang == LANG_RU) {
        switch_backtick_language(LANG_RU);
    }

    set_mods(mods);
    set_weak_mods(weak_mods);
    set_oneshot_mods(oneshot_mods);
    send_keyboard_report();
}

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
                if (get_mods() & MOD_MASK_SHIFT) {
                    langCtrl->switchLangEn();
                } else {
                    langCtrl->switchLangRu();
                }
            }
            break;
        case SWTCH_LNG_EN:
            if (pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    langCtrl->switchLangRu();
                } else {
                    langCtrl->switchLangEn();
                }
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
                // DEL_CTR находится в позиции [4,2]. Матрица уже полностью
                // обновлена, даже если событие mod-tap ещё не обработано.
                const bool ctrl_held = matrix_is_on(4, 2);

                if (ctrl_held) {
                    send_backtick_fence();
                } else {
                    WITH_LANG_SWITCH({
                        tap_code16(KC_GRAVE);
                    });
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

//region Retro tapping
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_TYPE, KC_SPC):
            return true;
        default:
            return false;
    }
}
//endregion
