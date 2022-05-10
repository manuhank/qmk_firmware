/*
Copyright 2019 Stephen Peery

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BASE,
    _FN,
};

enum custom_keycodes {
    KC_MISSION_CONTROL = SAFE_RANGE,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER
};

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Row:        0           1           2           3        4           5        6        7           8           9           10          11          12          13          14          15          16          */
    [_BASE] = { {   KC_ESC,     KC_SLCK,    KC_PAUSE,   KC_MSEL, KC_MSTP,    KC_MAIL, KC_WHOM, KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_NO,      KC_CALC,    RGB_TOG,    KC_PSCR },
                {   KC_GRV,     KC_1,       KC_2,       KC_3,    KC_4,       KC_5,    KC_6,    KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_INS,     KC_HOME,    KC_PGUP  },
                {   KC_TAB,     KC_Q,       KC_W,       KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_NO,      KC_DEL,     KC_END,     KC_PGDN  },
                {   KC_CAPS,    KC_A,       KC_S,       KC_D,    KC_F,       KC_G,    KC_H,    KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_NUHS,    KC_ENT,     KC_NO,      KC_NO,      KC_NO    },
                {   KC_LSFT,    KC_NUBS,    KC_Z,       KC_X,    KC_C,       KC_V,    KC_B,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_NO,      KC_RSFT,    KC_NO,      KC_UP,      KC_NO    },
                {   KC_LCTL,    KC_LALT,    KC_LGUI,    KC_SPC,  KC_RCTL,    KC_RALT, MO(_FN), KC_LAUNCHPAD,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_LEFT,    KC_DOWN,    KC_RIGHT }
              },
    [_FN]   = { {   RESET,      KC_F1,      KC_F2,      KC_F3,   KC_F4,      KC_F5,   KC_F6,   KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,    _______,    _______,    KC_SLEP  },
                {   _______,    _______,    _______,    _______, _______,    _______, _______, _______,    _______,    _______,    _______,    RGB_SPD,    RGB_SPI,    _______,    RGB_M_P,    RGB_M_B,    RGB_M_R  },
                {   _______,    _______,    _______,    _______, _______,    _______, _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,   RGB_M_SW,    RGB_MOD,   RGB_RMOD  },
                {   _______,    _______,    _______,    _______, _______,    _______, _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______  },
                {   _______,    _______,    _______,    _______, _______,    _______, _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RGB_VAI,    _______  },
                {   _______,    _______,    _______,    _______, _______,    _______, _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    RGB_HUD,    RGB_VAD,    RGB_HUI  }
             }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
        default:
            return true;   // Process all other keycodes normally
    }
}