/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
  _ART_BASE,
  _ART_NUM,
  _ART_CUS,
  _ART_PUNC,
  _ART_MOU,
  _ART_NAV,
  _ART_SYM,
};

#include "aliases.c"
#include "combos.c"

// copied from https://beta.docs.qmk.fm/faqs/faq_debug#which-matrix-position-is-this-keypress
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_ART_BASE] = LAYOUT(
_______,
_______,BASE_2_1,BASE_1_1,
_______,BASE_2_2,BASE_1_2,
_______,BASE_2_3,BASE_1_3,
_______,BASE_2_4,BASE_1_4
),

[_ART_NUM] = LAYOUT(
_______,
_______,NUM_2_1,NUM_1_1,
_______,NUM_2_2,NUM_1_2,
_______,NUM_2_3,NUM_1_3,
_______,NUM_2_4,NUM_1_4
),


[_ART_PUNC] = LAYOUT(
_______,
_______,PUNC_2_1,PUNC_1_1,
_______,PUNC_2_2,PUNC_1_2,
_______,PUNC_2_3,PUNC_1_3,
_______,PUNC_2_4,PUNC_1_4
),

[_ART_CUS] = LAYOUT(
_______,
_______,CUS_2_1,CUS_1_1,
_______,CUS_2_2,CUS_1_2,
_______,CUS_2_3,CUS_1_3,
_______,CUS_2_4,CUS_1_4
),

[_ART_SYM] = LAYOUT(
_______,
_______,SYM_2_1,SYM_1_1,
_______,SYM_2_2,SYM_1_2,
_______,SYM_2_3,SYM_1_3,
_______,SYM_2_4,SYM_1_4
),

[_ART_MOU] = LAYOUT(
_______,
_______,MOU_2_1,MOU_1_1,
_______,MOU_2_2,MOU_1_2,
_______,MOU_2_3,MOU_1_3,
_______,MOU_2_4,MOU_1_4
),

[_ART_NAV] = LAYOUT(
_______,
_______,NAV_2_1,NAV_1_1,
_______,NAV_2_2,NAV_1_2,
_______,NAV_2_3,NAV_1_3,
_______,NAV_2_4,NAV_1_4
),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_ART_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [_ART_NUM] = { ENCODER_CCW_CW(_______, _______) },
  [_ART_CUS] = { ENCODER_CCW_CW(_______, _______) },
  [_ART_PUNC] = { ENCODER_CCW_CW(_______, _______) },
  [_ART_MOU] = { ENCODER_CCW_CW(_______, _______) },
  [_ART_NAV] = { ENCODER_CCW_CW(_______, _______) },
  [_ART_SYM] = { ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _ART_BASE:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _ART_NUM:
            oled_write_P(PSTR("NUM\n"), false);
            break;
        case _ART_CUS:
            oled_write_P(PSTR("CUS\n"), false);
            break;
        case _ART_PUNC:
            oled_write_P(PSTR("PUNC\n"), false);
            break;
        case _ART_MOU:
            oled_write_P(PSTR("MOU\n"), false);
            break;
        case _ART_NAV:
            oled_write_P(PSTR("NAV\n"), false);
            break;
        case _ART_SYM:
            oled_write_P(PSTR("SYM\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif
