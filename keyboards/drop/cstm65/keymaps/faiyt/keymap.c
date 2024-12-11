// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H


enum layers {
    _BASE,
    _RAISE,
    _LOWER,
    _CONFIG,
    _TMUX,
    _GAMES
};


enum tap_dance_actions {
    TD_TAB_TILDE = 0,
    TD_CAPS_ESC,
    TD_PER_DOLLAR
};



tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_TAB_TILDE] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_TILDE),
    [TD_CAPS_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_PER_DOLLAR] = ACTION_TAP_DANCE_DOUBLE(KC_PERCENT, KC_DOLLAR)
    // [TD_LOWER_ESC_TOGGLE] = ACTION_TAP_DANCE_FN(d  ance_lower_esc_toggle)
};


// prefixes the key with the tmux prefix
void tmux_key(uint16_t keycode) {
      tap_code16(LCTL(KC_A)); //
      tap_code(keycode); // Send the desired key
}


enum custom_keycodes {
    CUSTOM_GUI_A = SAFE_RANGE,  // Our custom GUI+A key
    // Add more custom keycodes here if needed
};




#define TMUX(kc) tmux_key(kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Default
    [_BASE] = LAYOUT_65_ansi_blocker(
        TD(TD_CAPS_ESC), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        QK_GRAVE_ESCAPE,  LGUI_T(KC_A),    LALT_T(KC_S),    MT(MOD_LCTL, KC_D),    LSFT_T(KC_F),    KC_G,    KC_H,    RSFT_T(KC_J),   MT(MOD_LCTL, KC_K),    LALT_T(KC_L),    LGUI_T(KC_SCLN), KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, LT(_RAISE, KC_LALT),                            KC_SPC,                             LT(_LOWER, KC_RALT), MO(_CONFIG),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Upper
    [_RAISE] = LAYOUT_65_ansi_blocker(
        TD(TD_CAPS_ESC), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        QK_GRAVE_ESCAPE,  LGUI_T(KC_A),    LALT_T(KC_S),    MT(MOD_LCTL, KC_D),    LSFT_T(KC_F),    KC_G,    KC_LEFT,    KC_DOWN,   KC_UP, KC_RIGHT, LGUI_T(KC_SCLN), KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Lower
    [_LOWER] = LAYOUT_65_ansi_blocker(
        TD(TD_CAPS_ESC), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        QK_GRAVE_ESCAPE,  LGUI_T(KC_A),    LALT_T(KC_S),    MT(MOD_LCTL, KC_D),    LSFT_T(KC_F),    KC_G,    KC_H,    RSFT_T(KC_J),   MT(MOD_LALT, KC_K),    LALT_T(KC_L),    LGUI_T(KC_SCLN), KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Config Keyboard
    [_CONFIG] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_GAMES), KC_MUTE,
        _______, RM_TOGG, RM_VALU, RM_SPDU, RM_HUEU, RM_SATU, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_END,
        _______, RM_NEXT, RM_VALD, RM_SPDD, RM_HUED, RM_SATD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,QK_BOOT, NK_TOGG, _______, _______, _______, _______, _______,          KC_PGUP, KC_VOLD,
        _______, _______, _______,                            EE_CLR,                             KC_APP,  _______, KC_HOME, KC_PGDN, KC_END
    ),

    // Default KB for Games Layout
    [_GAMES] = LAYOUT_65_ansi_blocker(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, DF(_BASE),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool win_key_active = false;
    static bool other_key_pressed = false;
    static bool custom_gui_a_active = false;
    static bool custom_other_pressed = false;

    // Handle standalone Windows key
    if (keycode == KC_LGUI) {
        if (record->event.pressed) {
            win_key_active = true;
            other_key_pressed = false;
            return false;
        } else {
            if (!other_key_pressed) {
                win_key_active = false;
                return false;
            }
            win_key_active = false;
            unregister_code(KC_LGUI);
            return false;
        }
    }

    // Handle our custom GUI+A key
    if (keycode == CUSTOM_GUI_A) {
        if (record->event.pressed) {
            custom_gui_a_active = true;
            custom_other_pressed = false;
            register_code(KC_A);  // Always send 'A' when pressed
            return false;
        } else {
            unregister_code(KC_A);
            if (!custom_other_pressed) {
                custom_gui_a_active = false;
                return false;  // Don't activate GUI if no other key was pressed
            }
            custom_gui_a_active = false;
            return false;
        }
    }

    // If another key is pressed while either modifier is active
    if (record->event.pressed) {
        if (win_key_active) {
            other_key_pressed = true;
            register_code(KC_LGUI);
        }
        if (custom_gui_a_active) {
            custom_other_pressed = true;
            register_code(KC_LGUI);
        }
    }

    return true;
}
