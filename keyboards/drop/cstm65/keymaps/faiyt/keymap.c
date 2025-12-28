// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H


enum layers {
    _BASE,
    _DIRECTIONS,  // HJKL = arrows (was _RAISE)
    _UPPER,       // HJKL = Home/PgDn/PgUp/End
    _LOWER,       // Tab navigation + brackets
    _CONFIG,
    _TMUX,
    _GAMES
};


enum tap_dance_actions {
    TD_TAB_GRV = 0,
    TD_GRV_TAB,
    TD_CAPS_ESC,
    TD_PER_DOLLAR
};


tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_TAB_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_GRV),
    [TD_GRV_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TAB),
    [TD_CAPS_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_PER_DOLLAR] = ACTION_TAP_DANCE_DOUBLE(KC_PERCENT, KC_DOLLAR)
    // [TD_LOWER_ESC_TOGGLE] = ACTION_TAP_DANCE_FN(d  ance_lower_esc_toggle)
};

// Bit flags for storing active modifiers
#define TMUX_MOD_LCTL (1 << 0)
#define TMUX_MOD_LALT (1 << 1)
#define TMUX_MOD_LGUI (1 << 2)
#define TMUX_MOD_LSFT (1 << 3)
#define TMUX_MOD_RCTL (1 << 4)
#define TMUX_MOD_RALT (1 << 5)
#define TMUX_MOD_RGUI (1 << 6)
#define TMUX_MOD_RSFT (1 << 7)

#define IS_MOD(keycode) ((keycode) == KC_LCTL || (keycode) == KC_LALT || \
                                  (keycode) == KC_LGUI || (keycode) == KC_LSFT || \
                                  (keycode) == KC_RCTL || (keycode) == KC_RALT || \
                                  (keycode) == KC_RGUI || (keycode) == KC_RSFT)

static uint8_t tmux_mods = 0;

// Convert keycode to corresponding mod flag
static uint8_t get_mod_flag(uint16_t keycode) {
    switch (keycode) {
        case KC_LCTL: return TMUX_MOD_LCTL;
        case KC_LALT: return TMUX_MOD_LALT;
        case KC_LGUI: return TMUX_MOD_LGUI;
        case KC_LSFT: return TMUX_MOD_LSFT;
        case KC_RCTL: return TMUX_MOD_RCTL;
        case KC_RALT: return TMUX_MOD_RALT;
        case KC_RGUI: return TMUX_MOD_RGUI;
        case KC_RSFT: return TMUX_MOD_RSFT;
        default: return 0;
    }
}

// Apply stored mods to a keycode
static uint16_t apply_tmux_mods(uint16_t keycode) {
    uint16_t mods = 0;
    if (tmux_mods & TMUX_MOD_LCTL) mods |= MOD_LCTL;
    if (tmux_mods & TMUX_MOD_LALT) mods |= MOD_LALT;
    if (tmux_mods & TMUX_MOD_LGUI) mods |= MOD_LGUI;
    if (tmux_mods & TMUX_MOD_LSFT) mods |= MOD_LSFT;
    if (tmux_mods & TMUX_MOD_RCTL) mods |= MOD_RCTL;
    if (tmux_mods & TMUX_MOD_RALT) mods |= MOD_RALT;
    if (tmux_mods & TMUX_MOD_RGUI) mods |= MOD_RGUI;
    if (tmux_mods & TMUX_MOD_RSFT) mods |= MOD_RSFT;
    return (mods ? QK_MODS_MAX | (mods << 8) | (keycode & 0xFF) : keycode);
}

// prefixes the key with the tmux prefix and handles modifiers
void tmux_key(uint16_t keycode) {
    if (IS_MOD(keycode)) {
        uint8_t mod_flag = get_mod_flag(keycode);
        tmux_mods |= mod_flag;  // Store the modifier
    } else {
        tap_code16(LCTL(KC_A));
        uint16_t modified_keycode = apply_tmux_mods(keycode);
        tap_code16(modified_keycode);
        tmux_mods = 0;  // Clear modifiers after key press
    }
}


enum custom_keycodes {
    CUSTOM_GUI_A = SAFE_RANGE,  // Our custom GUI+A key
    CUSTOM_GUI_SCLN,
    CUSTOM_GUI,
    FORCE_GUI,
    OS_INFO
    //
    // Add more custom keycodes here if needed
};



#define TMUX(kc) tmux_key(kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Default
    [_BASE] = LAYOUT_65_ansi_blocker(
        LT(_UPPER, KC_ESC), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        TD(TD_GRV_TAB),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        MT(MOD_LCTL, KC_ESC),  LT(0, KC_A),    LALT_T(KC_S),    MT(MOD_LCTL, KC_D),    LSFT_T(KC_F),    KC_G,    KC_H,    RSFT_T(KC_J),   MT(MOD_LCTL, KC_K),    LALT_T(KC_L),    LT(0,KC_SCLN), KC_QUOT,          LT(_LOWER, KC_ENT),  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, LT(_TMUX, KC_LGUI), LT(_DIRECTIONS, KC_LALT),                            LT(_DIRECTIONS, KC_SPC),                             LT(_TMUX, KC_RALT), MO(_CONFIG),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Directions - HJKL = Arrow Keys (was _RAISE)
    [_DIRECTIONS] = LAYOUT_65_ansi_blocker(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_GRV,  LGUI_T(KC_A),    LALT_T(KC_S),    MT(MOD_LCTL, KC_D),    LSFT_T(KC_F),    KC_G,    KC_LEFT,    KC_DOWN,   KC_UP, KC_RIGHT, KC_SCLN, KC_GRV, KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Upper - HJKL = Home/PgDn/PgUp/End
    [_UPPER] = LAYOUT_65_ansi_blocker(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        _______,  LGUI_T(KC_A),    LALT_T(KC_S),    MT(MOD_LCTL, KC_D),    LSFT_T(KC_F),    KC_G,    KC_HOME,    KC_PGDN,   KC_PGUP, KC_END, KC_SCLN, KC_GRV, KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Lower - Tab navigation + brackets
    [_LOWER] = LAYOUT_65_ansi_blocker(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        _______,  LGUI_T(KC_A),    LALT_T(KC_S),    C(KC_TAB),    C(S(KC_TAB)),    KC_G,    KC_LBRC,    S(KC_9),   S(KC_0), KC_RBRC, KC_SCLN, KC_GRV, _______,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // TMUX - Auto prefix with Ctrl+A
    [_TMUX] = LAYOUT_65_ansi_blocker(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        _______, KC_A,    KC_S,    KC_D,    KC_LSFT,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        _______, _______, _______,                            _______,                             _______, _______,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Config Keyboard
    [_CONFIG] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_GAMES), KC_MUTE,
        OS_INFO, RM_TOGG, RM_VALU, RM_SPDU, RM_HUEU, RM_SATU, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_END,
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
        KC_LCTL, FORCE_GUI, KC_LALT,                            KC_SPC,                             KC_RALT, DF(_BASE),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

};



bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            rgb_matrix_set_color_all(RGB_WHITE);
            break;
        case OS_WINDOWS:
            rgb_matrix_set_color_all(RGB_BLUE);
            break;
        case OS_LINUX:
            rgb_matrix_set_color_all(RGB_ORANGE);
            break;
        case OS_UNSURE:
            rgb_matrix_set_color_all(RGB_RED);
            break;
    }

    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t custom_gui_a_timer = 0;
    // static uint16_t custom_gui_scln_timer = 0;
    static bool gui_a_held = false;
    static bool gui_scln_held = false;
    // static bool win_key_active = false;
    static bool other_key_pressed = false;

    // Handle other key presses
        if (record->event.pressed) {
            if (keycode != LT(0, KC_A) || keycode != LT(0, KC_SCLN))
                other_key_pressed = true;
        } else {
            other_key_pressed = false;
        }
    //

    //
    switch (keycode) {
        case LT(0,KC_A):
            if (record->tap.count && record->event.pressed) {
                // tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
                tap_code16(KC_A);
            } else if (record->event.pressed) {
                // tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
                if (other_key_pressed) {
                    // tap_code16(KC_LGUI);
                    gui_a_held = true;
                    register_code(KC_LGUI);
                }
            } else {

                gui_a_held = false;
                if (!gui_scln_held) {
                    unregister_code(KC_LGUI);
                }
            }
            return false;
        case LT(0, KC_SCLN):
            if (record->tap.count && record->event.pressed) {
                // tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
                tap_code16(KC_SCLN);
            } else if (record->event.pressed) {
                // tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
                if (other_key_pressed) {
                    // tap_code16(KC_LGUI);
                    gui_scln_held = true;
                    register_code(KC_LGUI);
                }
            } else {
                gui_scln_held = false;
                if (!gui_a_held) {
                    unregister_code(KC_LGUI);
                }
            }
            return false;
    }

    // TMUX layer handling
    if (layer_state_is(_TMUX)) {
        if (record->event.pressed) {
            tmux_key(keycode);
            return false;
        } else {
            if (IS_MOD(keycode)) {
                uint8_t mod_flag = get_mod_flag(keycode);
                tmux_mods &= ~mod_flag;  // Clear the modifier flag on release
            }
        }
    }

    // Handle standalone Windows key
    // if (keycode == KC_LGUI) {
    //     if (record->event.pressed) {
    //         // win_key_active = true;
    //         other_key_pressed = false;
    //         return false;
    //     } else {
    //         if (!other_key_pressed) {
    //             // win_key_active = false;
    //             return false;
    //         }
    //         // win_key_active = false;
    //         unregister_code(KC_LGUI);
    //         return false;
    //     }
    // }

    // Force GUI key - bypasses all custom handling
    if (keycode == FORCE_GUI) {
        if (record->event.pressed) {
            register_code(KC_LGUI);
        } else {
            unregister_code(KC_LGUI);
        }
        return false;
    }

    // Handle custom GUI+A with tap-hold behavior
    // Todo: Make this so the a key takes less time to show up when pressed
    // if (keycode == CUSTOM_GUI_A) {
    //     if (record->event.pressed) {
    //         custom_gui_a_timer = timer_read();
    //         gui_a_held = true;
    //     } else {
    //         gui_a_held = false;
    //         // On release
    //         if (timer_elapsed(custom_gui_a_timer) < TAPPING_TERM) {
    //             // This was a tap, send 'a'
    //             tap_code(KC_A);
    //         }
    //
    //         if (!gui_scln_held) {
    //            unregister_code(KC_LGUI);
    //         }
    //     }
    //     return false;
    // }

    // if (keycode == CUSTOM_GUI_SCLN) {
    //     if (record->event.pressed) {
    //         custom_gui_scln_timer = timer_read();
    //         gui_scln_held = true;
    //     } else {
    //         gui_scln_held = false;
    //         // On release
    //         if (timer_elapsed(custom_gui_scln_timer) < TAPPING_TERM) {
    //             // This was a tap, send ';'
    //             tap_code(KC_SCLN);
    //         }
    //
    //         if (!gui_a_held) {
    //             unregister_code(KC_LGUI);
    //         }
    //
    //     }
    //     return false;
    // }

    if (keycode == OS_INFO) {

           if (record->event.pressed) {
                switch (detected_host_os()) {
                    case OS_MACOS:
                        SEND_STRING("Running on macOS");
                        break;
                    case OS_WINDOWS:
                        SEND_STRING("Running on Windows");
                        break;
                    case OS_LINUX:
                        SEND_STRING("Running on Linux");
                        break;
                    case OS_IOS:
                        SEND_STRING("Running on iOS");
                        break;
                    case OS_UNSURE:
                        SEND_STRING("Unable to detect OS");
                        break;
                }
            return false;
        }
    }

    return true;
}


