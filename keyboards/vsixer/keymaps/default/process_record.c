// process_record.c
#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "service/language_controller.h"
#include "wait.h"

extern LanguageController* langCtrl;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ADJUST_LNG:
            if (record->event.pressed) {
                uint8_t langToSet = langCtrl->getCurrentLang() == LANG_RU ? LANG_EN : LANG_RU;
                langCtrl->setLang(langToSet);
            }
            break;

        //region Унивсальные символы
        case UNI_DOT_COM:
            if (record->event.pressed) {
                if (langCtrl->getCurrentLang() == LANG_EN) { // Английская раскладка
                    if (get_mods() & MOD_MASK_SHIFT) {
                        unregister_code(KC_LSFT);  // Отключаем Shift
                        tap_code(KC_COMM);         // Отправляем запятую
                        register_code(KC_LSFT);    // Возвращаем Shift
                    } else {
                        tap_code16(KC_DOT);
                    }
                } else { // Русская раскладка
                    if (get_mods() & MOD_MASK_SHIFT) {
                        tap_code16(S(KC_SLSH)); // запятая
                    } else {
                        tap_code16(KC_SLSH); // точка
                    }
                }
            }
            break;
        case UNI_QSTN:
            if (record->event.pressed) {
                if (langCtrl->getCurrentLang() == LANG_EN) {
                    tap_code16(S(KC_SLSH));
                } else {
                    tap_code16(S(KC_7));
                }
            }
            break;
        case UNI_AMP:
            if (record->event.pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(S(KC_7));
                });
            }
            break;
        case UNI_AT:
            if (record->event.pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(S(KC_2));
                });
            }
            break;
        case UNI_HASH:
            if (record->event.pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(S(KC_3));
                });
            }
            break;
        case UNI_DLR:
            if (record->event.pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(S(KC_4));
                });
            }
            break;
        case UNI_PIPE:
            if (record->event.pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(S(KC_BSLS));
                });
            }
            break;
        case UNI_CARET:
            if (record->event.pressed) {
                WITH_LANG_SWITCH({
                    tap_code16(S(KC_6));
                });
            }
            break;
//        case UNI_TILDE:
//            if (record->event.pressed) {
//                WITH_LANG_SWITCH({
//                    tap_code16(KC_GRAVE);
//                });
//            }
//            break;
        //endregion

        //region Переключение окон
        case WS_FWD:
            if (!record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                unregister_mods(MOD_BIT(KC_LSFT));
                tap_code(KC_TAB);
            }
            break;
        case WS_BWD:
            if (!record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                register_mods(MOD_BIT(KC_LSFT));
                tap_code(KC_TAB);
            }
            break;
        case LT(_SYM, KC_ESC):
            if (!record->event.pressed) {
                unregister_mods(MOD_BIT(KC_LALT));
                unregister_mods(MOD_BIT(KC_LSFT));
            }
            break;
        //endregion

        case CPS_BLK:
            if (!record->event.pressed) {
                tap_code16(C(S(KC_MINUS)));
                wait_ms(50);
                tap_code16(C(S(KC_PLUS)));
            }
            break;
    }

    return true;
}