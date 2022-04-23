// Quick reference build commands.
// qmk compile -kb handwired/ortho5x12 -km default && cp .build/handwired_ortho5x12_default.hex /mnt/c/Users/Matt-PC/Documents/

#include QMK_KEYBOARD_H

#define _QWERT 0
#define _COLMK 1
#define _AOE 2
#define _LAYR 3
#define _AOELY 4
#define _FN 5

#define KC_SYMBL MO(_SYMBL)
#define KC_AOELY MO(_AOELY)

enum {
    KC_TF1 = SAFE_RANGE,
    KC_TF2,
    KC_TF3,
    KC_LAYR
};

// Variable for keeping track of how many layer active keys are held down.
// QMK does not like it when you have two keys that activate the same layer.
// Releaseing the key you entered the layer with while holding down the other
// key will not keep you in the layer.
static uint16_t layer_keys_active = 0;

// One Shot Modifiers.
#define KC_OSMC OSM(MOD_LCTL)
#define KC_OSMS OSM(MOD_LSFT)

// Age of Empires FX, then Tab keys.

static bool is_f1_active = false;
static uint16_t f1_timer = 0;

static bool is_f2_active = false;
static uint16_t f2_timer = 0;

static bool is_f3_active = false;
static uint16_t f3_timer = 0;

enum {
    TD_TCSV,
    TD_TCSF,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TCSV] = ACTION_TAP_DANCE_DOUBLE(C(KC_V), RCS(KC_V)),
    [TD_TCSF] = ACTION_TAP_DANCE_DOUBLE(C(KC_F), RCS(KC_F))
};

// Default Layer switch keys.
#define DF_QWERT DF(_QWERT)
#define DF_COLMK DF(_COLMK)
#define DF_AOE DF(_AOE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // QWERTY Default layer
  [_QWERT] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_OSMS ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_OSMC ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_LCTL ,
  //|--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
     XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LALT ,KC_LAYR ,KC_SPC  ,KC_LSFT ,KC_LAYR ,KC_LGUI ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //`--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
  ),

  // COLMK Default layer
  [_COLMK] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G    ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_OSMS ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D    ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOTE,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_OSMC ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_LCTL ,
  //|--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
     XXXXXXX ,XXXXXXX ,KC_LGUI ,KC_LALT ,KC_LAYR ,KC_SPC  ,KC_LSFT ,KC_LAYR ,KC_UP   ,KC_DOWN ,KC_LEFT ,KC_RGHT
  //`--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
  ),

  // AOE4 / Gaming layer.
  // Removes some modifiers and has some special macros on the left hand layer key.
  [_AOE] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_LSFT ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_LCTL ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_LCTL  ,
  //|--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
     XXXXXXX ,XXXXXXX ,KC_LGUI ,KC_LALT ,KC_AOELY,KC_SPC  ,KC_LSFT ,KC_LAYR ,KC_UP   ,KC_DOWN ,KC_LEFT ,KC_RGHT
  //`--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
  ),
  // Single layer, toggled on when either of the layer keys are held down.
  // Allows you to switch the key you are holding to activate the layer while in the layer / the fn layer.
  // And use either thumb to keys on the layer.
  [_LAYR] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,KC_LCBR ,KC_LPRN , KC_GRV ,KC_RPRN ,KC_RCBR ,KC_ESC  ,KC_BSPC ,KC_UP   ,KC_ENT  ,KC_PGUP  ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,KC_LABK ,KC_LBRC ,KC_UNDS ,KC_RBRC ,KC_RABK ,KC_TAB  ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_DEL  ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,KC_BSLS ,KC_PLUS ,KC_MINS  ,KC_EQL ,KC_PIPE ,KC_CAPS ,KC_HOME ,KC_TILD ,KC_END  ,KC_PGDN ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
  ),
  // Special Gaming layer with AOE4 and gaming keys.
  [_AOELY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_ESC  ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,_______ ,_______ ,_______ ,_______ ,DF_QWERT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_TAB  ,KC_Y    ,KC_TF1  ,KC_TF2  ,KC_TF3  ,KC_P    ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_LSFT ,KC_H    ,KC_J    ,KC_Q    ,KC_L    ,KC_SCLN ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     KC_LCTL ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //|--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
     _______ ,_______ ,_______ ,_______ ,KC_AOELY,KC_SPC  ,_______ ,_______ ,_______ ,_______ ,_______ , _______
  //`--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+
  ),
  // Function layer, both layer keys held to activate.
[_FN] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,RESET   ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,DF_QWERT,DF_AOE  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_F11  ,KC_F12  ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,DF_COLMK,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ , _______,_______
  //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
  ),

};

// Always use QWERTY as the default layer, don't start in a gaming layer.
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
         case KC_LAYR:
            if (record->event.pressed) {
                layer_keys_active += 1;

                if (layer_keys_active == 1) {
                    layer_on(_LAYR);
                }

                if (layer_keys_active == 2) {
                    layer_on(_FN);
                }

                return false;
            }

            else {
                layer_keys_active -= 1;
                if (layer_keys_active == 0) {
                    layer_off(_LAYR);
                }
                if (layer_keys_active == 1) {
                    layer_off(_FN);
                }

                return false;
            }
        case KC_TF1:
            if (record->event.pressed) {
                if (!is_f1_active) {
                    register_code(KC_F1);
                    unregister_code(KC_F1);
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                    is_f1_active = true;
                    f1_timer = timer_read();
                } else {
                    f1_timer = timer_read();
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                }
            }
            return false;

        case KC_TF2:
            if (record->event.pressed) {
                if (!is_f2_active) {
                    register_code(KC_F2);
                    unregister_code(KC_F2);
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                    is_f2_active = true;
                    f2_timer = timer_read();
                } else {
                    f2_timer = timer_read();
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                }
            }
            return false;

        case KC_TF3:
            if (record->event.pressed) {
                if (!is_f3_active) {
                    register_code(KC_F3);
                    unregister_code(KC_F3);
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                    is_f3_active = true;
                    f3_timer = timer_read();
                } else {
                    f3_timer = timer_read();
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                }
            }
            return false;
    }

    return true;
}

void matrix_scan_user(void) {
    if (is_f1_active) {
        if (timer_elapsed(f1_timer) > 1000) {
            is_f1_active = false;
        }
    }

    if (is_f2_active) {
        if (timer_elapsed(f2_timer) > 1000) {
            is_f2_active = false;
        }
    }

    if (is_f3_active) {
        if (timer_elapsed(f3_timer) > 1000) {
            is_f3_active = false;
        }
    }

}
