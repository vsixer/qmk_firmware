~~~~# GEMINI.md

## Project Overview

This project is a custom keymap for the "vsixer" keyboard, built on the QMK firmware. It is designed for a bilingual user who frequently switches between English and Russian. The keymap is highly customized with multiple layers, custom keycodes, and combos to streamline the user's workflow.

**Main Technologies:**

*   QMK Firmware
*   C programming language

**Architecture:**

The keymap is structured into several files:

*   `keymap.c`: The core of the keymap, defining layers, combos, and key mappings.
*   `custom_keycodes.h`: Defines custom keycodes for special actions and characters.
*   `process_record.c`: Handles the logic for custom keycodes and other key events.
*   `rules.mk`: Configures the QMK build, enabling features like combos and extra keys.
*   `service/language_controller.c` & `service/language_controller.h`: A custom service for managing and switching between keyboard layouts (English and Russian).

## Building and Running

To build and flash this keymap, you will need to have a QMK build environment set up.

**Build Command:**

```bash
qmk compile -kb vsixer -km default
```

**Flash Command:**

```bash
qmk flash -kb vsixer -km default
```

*Note: You may need to replace `vsixer` with the actual keyboard name if it differs.*

## Development Conventions

*   **Layers:** The keymap uses multiple layers to organize keys by function (e.g., base, gaming, navigation, symbols, Russian).
*   **Combos:** Combos are used extensively to send special characters (e.g., `()`, `[]`, `->`) and perform actions (e.g., switch language, copy/paste).
*   **Custom Keycodes:** Custom keycodes are defined for actions that are not available in the standard QMK keycode set (e.g., universal symbols, window switching).
*   **Language Switching:** A custom language controller service allows for seamless switching between English and Russian layouts. The `WITH_LANG_SWITCH` macro is used to temporarily switch to the English layout for sending specific keycodes.
*   **Code Style:** The code follows the standard QMK coding style.
