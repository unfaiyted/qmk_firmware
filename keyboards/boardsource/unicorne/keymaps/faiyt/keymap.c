#include QMK_KEYBOARD_H
// #include "quantum.h"
// Layers enumeration
enum layers {
    _BASE,
    _RAISE,
    _LOWER,
    _FUNC,
    _ADJUST,
    _SETTINGS,
    _TMUX,
    _GAMES
};
//
enum tap_dance_actions {
    TD_TAB_TILDE = 0,
    TD_CAPS_ESC,
    TD_PER_DOLLAR
};


enum custom_keycodes {
    CUSTOM_SYMBOLS = SAFE_RANGE,
    DELAY_LGUI_Q,
    DELAY_POWER
    // other custom keycodes can follow
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_TAB_TILDE] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_TILDE),
    [TD_CAPS_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, CW_TOGG),
    [TD_PER_DOLLAR] = ACTION_TAP_DANCE_DOUBLE(KC_PERCENT, KC_DOLLAR)
    // [TD_LOWER_ESC_TOGGLE] = ACTION_TAP_DANCE_FN(d  ance_lower_esc_toggle)
};

// static uint16_t mod_tab_timer;
// static uint16_t layer1_key_timer = 0;
//

// prefixes the key with the tmux prefix
void tmux_key(uint16_t keycode) {
      tap_code16(LCTL(KC_A)); //
      tap_code(keycode); // Send the desired key
}


#define TMUX(kc) tmux_key(kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ,---------------------------------------.          ,------------------------------------.
// | TdTab~ |  Q  |  W  | Me+E |  R  |  T  |          |  Y  |  U  | Me+I |  O  |  P  | Bksp|
// |--------+-----+-----+------+-----+-----|          |-----+-----+------+-----+-----+-----|
// | Esc/ ` | A/LG| S/LA| D/LC | F/LS|  G  |          |  H  | J/LS| K/LC | L/LA|;L/LG| Quo |
// |--------+-----+-----+------+-----+-----|          |-----+-----+------+-----+-----+-----|
// | LShift |  Z  |  X  |  C   |  V  |  B  |          |  N  |  M  |  ,   |  .  |  /  | Esc/|
// `--------+-----+-----+------+-----+-----'--.    ,--`-----+-----+------+-----+-----+-----'
//                            |T/Bs|L/Esc|A/Sp|    |A/En|R/Bs|Func|
//                            `----+-----+----'    `----+----+----'

   [_BASE] = LAYOUT_split_3x6_3(
       TD(TD_TAB_TILDE) ,  KC_Q,    KC_W,    MEH_T(KC_E),    KC_R,    KC_T,                                              KC_Y,    KC_U,    MEH_T(KC_I),    KC_O,    KC_P,    KC_BSPC,
       QK_GRAVE_ESCAPE , LGUI_T(KC_A),    MT(MOD_LALT, KC_S),    LCTL_T(KC_D),    LSFT_T(KC_F),    KC_G,           KC_H,    RSFT_T(KC_J),    LCTL_T(KC_K),    MT(MOD_LALT, KC_L),    MT(MOD_LGUI, KC_SCLN), KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,

                                            LT(_SETTINGS, KC_TAB), LT(_LOWER, KC_ESC),  LT(_ADJUST, KC_SPC),            LT(_TMUX, KC_ENTER),  LT(_RAISE, KC_BSPC), LT(_FUNC, KC_DEL)
    ),

// _LOWER
// ,----------------------------------------.      ,------------------------------------.
// |LCtlShT|LGuQ |LCtlW |LCtlTb|LCtlTb|LCtlT|      | #   |  {  | }   | %    |=    |    |
// |--------+-----+-----+------+------+-----|      |-----+-----+------+-----+-----+-----|
// |        |LGui |LAlt |LCtrl |LShift|     |      |[    |(    |)    |]    |Grave|*     |
// |--------+-----+-----+------+------+-----|      |-----+-----+------+-----+-----+-----|
// |        |Undo |Cut  |Copy  |Paste |     |      |^    |<    |>    |$    |@    |      |
// `--------+-----+-----+------+------+-----'      `-----+-----+------+-----+-----+-----'
//          |WwSrch|    |     |                           |Undr |PMin |PPls |
//          `------+-----+----'                           `----+----+----'


    [_LOWER] = LAYOUT_split_3x6_3(
        LCTL(LSFT(KC_T)),  DELAY_LGUI_Q, LCTL(KC_W), LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), LCTL(KC_T),        KC_HASH,LSFT(KC_LBRC), LSFT(KC_RBRC), KC_PERCENT, KC_EQL,  _______,
        CW_TOGG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_WWW_SEARCH,                             KC_LBRC, KC_LPRN, KC_RPRN,  KC_RBRC, KC_GRAVE,  KC_PAST,
        _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, _______,                             KC_CIRC, KC_LT,  KC_GT, KC_DOLLAR, KC_AT,  _______,
                                    _______, _______, _______,                      KC_UNDERSCORE, KC_PMNS, KC_PPLS
    ),

// _RAISE Layer:
// ,------------------------------------.          ,-----------------------------------.
// |  `  |  !   |  7  |  8  |  9  | %/$ |          |  &  |  /  |  |  |  \  |     |     |
// |-----+------+-----+-----+-----+-----|          |-----+-----+-----+-----+-----+-----|
// |     |  @   |  4  |  5  |  6  |  0  |          |Left |Down | Up  |Right|RGui |     |
// |-----+------+-----+-----+-----+-----|          |-----+-----+-----+-----+-----+-----|
// |     | Pass |  1  |  2  |  3  |  *  |          |Home |PgDn |PgUp | End |     |     |
// `-----+------+-----+-----+-----+-----'--.   .--`-----+-----+-----+-----+-----+-----'
//                        |  0  | Dot |    |   |    |     |     |
//                        `-----+-----+----'   `----+-----+-----'

    [_RAISE] = LAYOUT_split_3x6_3(
        KC_GRAVE, KC_EXCLAIM, KC_7,    KC_8,    KC_9,     TD(TD_PER_DOLLAR),       KC_AMPR,    KC_SLASH,    KC_PIPE,    KC_BACKSLASH,    _______,    _______,
        _______, KC_AT, KC_4,    KC_5,    KC_6,    KC_0,                   KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_RGUI,    _______,
        _______,  CUSTOM_SYMBOLS, KC_1,    KC_2,    KC_3,    KC_PAST,               KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,    _______,    _______,
                            KC_0, KC_DOT, _______,        _______, _______,  DF(_BASE)
    ),

// _FUNC Layer:
// ,---------------------------------.      ,-----------------------------------.
// |    |F12  |F7   |F8   |F9  |PScr |      |     |     |     |     |     |     |
// |----+-----+-----+-----+----+-----|      |-----+-----+-----+-----+-----+-----|
// |    |F11  |F4   |F5   |F6  |     |      |     |LShft|LCtrl|LAlt |RGui |     |
// |----+-----+-----+-----+----+-----|      |-----+-----+-----+-----+-----+-----|
// |    |F10  |F1   |F2   |F3  |     |      |     |     |     |     |     |     |
// `----+-----+-----+-----+----+-----'      `-----+-----+-----+-----+-----+-----'
//           |    |     |     |                           |     |     |     |
//           `----+-----+-----'                           `-----+-----+-----'

    [_FUNC] = LAYOUT_split_3x6_3(
        DF(_GAMES), KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,         _______, _______, _______, _______, _______, DF(_BASE),
        _______, KC_F11, KC_F4, KC_F5, KC_F6, _______,         _______, KC_LSFT, KC_LCTL, KC_LALT, KC_RGUI, _______,
        _______, KC_F10, KC_F1, KC_F2, KC_F3, _______,         _______, _______, _______, _______, _______, _______,
                            _______, _______, _______,        _______, _______, _______
    ),

// _ADJUST Layer:
// ,----------------------------------.      ,---------------------------------.
// |    |     |     | mup |     |     |      | ⚡️  |🔽  |🔼  |     |     |     |
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// |    |     | mlef| mdwn|mrgt |     |      | 🔇  |🔉  |🔊  |     |     |     |
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// |🔄  |     |     |     |     |     |      |     |⏬  |⏫  |     |🔄   |     |}}}}}}}}}}}}
// `----+-----+-----+-----+-----+-----'      `-----+----+----+-----+-----+-----'
//           |    |     |     |                           | ▶️  | ⏮️  |⏭️  |
//           `----+-----+-----'                           `----+----+---'
    [_ADJUST] = LAYOUT_split_3x6_3(
        _______, _______, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_MS_WH_UP,                DELAY_POWER, KC_BRID, KC_BRIU, _______, _______, _______,
        _______, KC_MS_BTN3, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN,        KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
        QK_BOOT, _______, _______, _______, _______, _______,                           _______, KC_PGDN, KC_PGUP, _______, _______, _______,
                                _______, _______, _______,               KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK
    ),
// _SETTINGS Layer:
// ,----------------------------------.      ,---------------------------------.
// |    |     |     | mup |     |     |      |     |    |    |     |     |     |
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// |    |     | mlef| mdwn|mrgt |     |      |     |    |    |     |     |     |
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// |🔄  |     |     |     |     |     |      |     |    |    |     |     |     |
// `----+-----+-----+-----+-----+-----'      `-----+----+----+-----+-----+-----'
//           |    |     |     |                           |    |    |   |
//           `----+-----+-----'                           `----+----+---'
    [_SETTINGS] = LAYOUT_split_3x6_3(
        RGB_TOG, _______, RGB_HUD, RGB_VAI, RGB_HUI, RGB_SAD,                   MI_Cs, MI_Ds, QK_MIDI_TOGGLE , MI_Fs, MI_Gs, MI_As,
        _______, _______, RGB_MOD, RGB_VAD, RGB_RMOD, RGB_SAI,                  MI_C, MI_D, MI_E, MI_F, MI_G, MI_A,
        _______, _______, _______, _______, _______, _______,                  MI_C1, MI_D1, MI_E1, MI_F1, MI_G1, MI_A1,
                                   _______, _______, _______,               _______, _______, _______
    ),


// _TMUX Layer:
// ,----------------------------------.      ,---------------------------------.                                                          // _GAMES Layer:
// |    |     |     | mup |     |     |      |     |    |    |     |     |     |                                                          // ,----------------------------------.      ,---------------------------------.
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|                                                          // |    |     |     | mup |     |     |      |     |    |    |     |     |     |
// |    |     | mlef| mdwn|mrgt |     |      |     |    |    |     |     |     |                                                          // |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|                                                          // |    |     | mlef| mdwn|mrgt |     |      |     |    |    |     |     |     |
// |🔄  |     |     |     |     |     |      |     |    |    |     |     |     |                                                        // |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// `----+-----+-----+-----+-----+-----'      `-----+----+----+-----+-----+-----'                                                          // |🔄  |     |     |     |     |     |      |     |    |    |     |     |     |
//           |    |     |     |                           |    |    |   |                                                                 // `----+-----+-----+-----+-----+-----'      `-----+----+----+-----+-----+-----'
//           `----+-----+-----'                           `----+----+---'                                                                 //           |    |     |     |                           |    |    |   |
                                                                                                                                          //           `----+-----+-----'                           `----+----+---'
    [_TMUX] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, KC_S, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
                                _______, _______, _______,               _______, KC_PMNS, KC_PPLS

    ),

// _GAMES Layer:
// ,----------------------------------.      ,---------------------------------.                                                          // _GAMES Layer:
// |    |     |     | mup |     |     |      |     |    |    |     |     |     |                                                          // ,----------------------------------.      ,---------------------------------.
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|                                                          // |    |     |     | mup |     |     |      |     |    |    |     |     |     |
// |    |     | mlef| mdwn|mrgt |     |      |     |    |    |     |     |     |                                                          // |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|                                                          // |    |     | mlef| mdwn|mrgt |     |      |     |    |    |     |     |     |
// |🔄  |     |     |     |     |     |      |     |    |    |     |     |     |                                                        // |----+-----+-----+-----+-----+-----|      |-----+----+----+-----+-----+-----|
// `----+-----+-----+-----+-----+-----'      `-----+----+----+-----+-----+-----'                                                          // |🔄  |     |     |     |     |     |      |     |    |    |     |     |     |
//           |    |     |     |                           |    |    |   |                                                                 // `----+-----+-----+-----+-----+-----'      `-----+----+----+-----+-----+-----'
//           `----+-----+-----'                           `----+----+---'                                                                 //           |    |     |     |                           |    |    |   |
                                                                                                                                          //           `----+-----+-----'                           `----+----+---'

[_GAMES] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                      KC_LALT, KC_LCTL, KC_ENT,                LT(_TMUX, KC_ENTER),  LT(_RAISE, KC_BSPC), LT(_FUNC, KC_DEL)
)


};

static uint16_t close_key_timer;
static uint16_t power_key_timer;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {


    if (layer_state_is(_TMUX)) {
            if (record->event.pressed)  {
            tmux_key(keycode);
            return false;
        }

    }




    switch (keycode) {
        case CUSTOM_SYMBOLS:
            if (record->event.pressed) {
                // when keycode CUSTOM_HELLO is pressed
                SEND_STRING("$$##@@!!");
            } else {
                // when keycode CUSTOM_HELLO is released
            }
            break;
        case DELAY_LGUI_Q:
            if (record->event.pressed) {
                // Key pressed
                close_key_timer = timer_read();
            } else {
                // Key released
                if (timer_elapsed(close_key_timer) > CUSTOM_QUIT_KEY_DELAY) {
                    // Send your mod+key combination here
                    tap_code16(LGUI(KC_Q)); // Example: Alt + Q
                }
            }
            break;
         case DELAY_POWER:
            if (record->event.pressed) {
                // Key pressed
                power_key_timer = timer_read();
            } else {
                // Key released
                if (timer_elapsed(power_key_timer) > CUSTOM_POWER_KEY_DELAY) {
                    // Send your mod+key combination here
                    tap_code16(KC_PWR); // Example: Alt + Q
                }
            }
            break;}
    return true;
}

