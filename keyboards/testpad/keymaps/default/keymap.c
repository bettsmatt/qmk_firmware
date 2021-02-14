/* Copyright 2019 imchipwood
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

#define _BASE 0
#define _SUB  1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    RGB_TOG, KC_2, KC_3, RGB_TOG,
    KC_5, KC_6, KC_7, KC_8,
    KC_A, KC_B, KC_C, KC_D,
    KC_E, KC_F, KC_G, KC_H
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
  #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable = true;
  debug_matrix = true;
  debug_keyboard = true;
  // debug_mouse = true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Default behavior:
   *    main layer:
   *       CW: move mouse right
   *      CCW: move mouse left
   *    other layers:
   *       CW: = (equals/plus - increase slider in Adobe products)
   *      CCW: - (minus/underscore - decrease slider in adobe products)
  */

    #ifdef CONSOLE_ENABLE
      uprintf("clockwise: %u, index: %u\n", clockwise, index);
    #endif

    switch (biton32(layer_state)) {
      case _BASE:
        // main layer - move mouse right (CW) and left (CCW)
        if (clockwise && index == 0) {
          // tap_code(RGB_MODE_FORWARD);
          // register_code(RGB_MOD);
          rgblight_step();

        } else if (!clockwise && index == 0){
          // register_code(RGB_RMOD);
          rgblight_step_reverse();

          // tap_code(RGB_MODE_REVERSE);
        } else if (clockwise && index == 1){
          // register_code(RGB_VAI);
          // unregister_code(RGB_VAI);
          rgblight_increase_hue();
        } else if (!clockwise && index == 1){
          // register_code(RGB_VAD);
          rgblight_decrease_hue();
          // unregister_code(RGB_VAD);
        }
        break;
  }
}