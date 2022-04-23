/* Copyright 2021 bettsmatt
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

#define _EDITOR 0
#define _TERMINAL 1
#define _NUMPAD 2

#define _ENCODER_LEFT 0
#define _ENCODER_RIGHT 1

#define KC_CS_F RCS(KC_F)

bool is_tab_active = false;
uint16_t tab_timer = 0;

bool is_gui_active = false;
uint16_t gui_timer = false;

bool is_alt_tab_mode = false;

enum {
    KC_G1 = SAFE_RANGE,
    KC_G2,
    KC_G3,
    KC_G4,
    KC_TABMD,
};

enum {
    TD_V,
    TD_F,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_V] = ACTION_TAP_DANCE_DOUBLE(C(KC_V), RCS(KC_V)),
    [TD_F] = ACTION_TAP_DANCE_DOUBLE(C(KC_F), RCS(KC_F)),
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_EDITOR] = LAYOUT(
    RGB_TOG, RGB_TOG, TO(_TERMINAL), KC_TABMD,
    KC_G1, KC_G2, KC_G3, KC_G4,
    C(KC_A), C(KC_S), XXXXXXX, TD(TD_F),
    C(KC_Z), C(KC_X), C(KC_C), TD(TD_V)
  ),

  [_TERMINAL] = LAYOUT(
    RGB_TOG, RGB_TOG, TO(_NUMPAD), KC_TABMD,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_NUMPAD] = LAYOUT(
    RGB_TOG, RGB_TOG, TO(_EDITOR), KC_TABMD,
    XXXXXXX, KC_7, KC_8, KC_9,
    XXXXXXX, KC_4, KC_5, KC_6,
    KC_0, KC_1, KC_2, KC_3
  ),
};

uint32_t layer_state_set_user(uint32_t state) {

  uint8_t layer = biton32(state);

  switch (layer) {
    case _EDITOR:
      rgblight_sethsv(201, 255, 50);
		  break;
    case _TERMINAL:
      rgblight_sethsv(169, 255, 50);
      break;
    case _NUMPAD:
      rgblight_sethsv(127, 255, 50);
      break;
  }

 return state;

}


void led_set_user(uint8_t usb_led) {

}

void keyboard_post_init_user(void) {
  rgblight_enable();
  rgblight_mode(0);
  rgblight_sethsv(201, 255, 100);
}


void encoder_update_user(uint8_t index, bool clockwise) {

  if (index == _ENCODER_LEFT) {
    if (clockwise) {
      tap_code16(KC_WH_U);
    } else {
      tap_code16(KC_WH_D);
    }
  }

  if (index == _ENCODER_RIGHT) {
    if (!is_tab_active) {
      is_tab_active = true;
      if (is_alt_tab_mode) {
        register_code(KC_LALT);
      } else {
        register_code(KC_LCTL);
      }
    }
    if (is_tab_active) {
      tab_timer = timer_read();
      if (clockwise) {
        tap_code16(KC_TAB);
      } else {
        tap_code16(S(KC_TAB));
      }
    }
  }
}

void matrix_scan_user(void) {
  if (is_tab_active) {
    if (timer_elapsed(tab_timer) > 1250) {
      if (is_alt_tab_mode) {
        unregister_code(KC_LALT);
      }
      else {
        unregister_code(KC_LCTL);
      }
      is_alt_tab_mode = false;
      is_tab_active = false;
    }
  }

  if (is_gui_active) {
    if (timer_elapsed(gui_timer) > 1250) {
      unregister_code(KC_LGUI);
      is_gui_active = false;
    }
  }


}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_TABMD:
          if (!record->event.pressed) {
            if (!is_tab_active) {
              is_alt_tab_mode = true;
            } else {
              if (is_alt_tab_mode) {
                unregister_code(KC_LALT);
              }
              else {
                unregister_code(KC_LCTL);
              }
              is_alt_tab_mode = false;
              is_tab_active = false;
            }
          }
          break;

        // Keep GUI active for 10002 ms when cycling between pinned programs.
        // This allows us to tab between two instances of a program.
        case KC_G1:
        case KC_G2:
        case KC_G3:
        case KC_G4:

            if (record->event.pressed) {

                if (!is_gui_active) {
                    is_gui_active = true;
                    register_code(KC_LGUI);
                }

                switch (keycode) {
                    case KC_G1: register_code(KC_1); break;
                    case KC_G2: register_code(KC_2); break;
                    case KC_G3: register_code(KC_3); break;
                    case KC_G4: register_code(KC_4); break;
                }
            } else {

                switch (keycode) {
                  case KC_G1:
                  case KC_G2:
                  case KC_G3:
                  case KC_G4:
                    gui_timer = timer_read();
                }

                switch (keycode) {
                    case KC_G1: unregister_code(KC_1); break;
                    case KC_G2: unregister_code(KC_2); break;
                    case KC_G3: unregister_code(KC_3); break;
                    case KC_G4: unregister_code(KC_4); break;
                }
            }
    }
    return true;
}