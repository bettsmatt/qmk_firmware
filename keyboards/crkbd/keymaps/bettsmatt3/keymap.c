#include QMK_KEYBOARD_H

enum {
    KC_SPCU = SAFE_RANGE,
    KC_HRB,
    KC_HSB,
    KC_HCB,
    KC_LAYR,
};

enum {
    TD_SB,
    TD_CB,
    TD_NB,
    TD_G1,
    TD_G2,
    TD_G3,
    TD_G4,
    TD_G5,
    TD_IDLE,
};

// Tap Dance.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SB] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_CB] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_NB] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_G1] = ACTION_TAP_DANCE_DOUBLE(KC_1, C(KC_1)),
    [TD_G2] = ACTION_TAP_DANCE_DOUBLE(KC_2, C(KC_2)),
    [TD_G3] = ACTION_TAP_DANCE_DOUBLE(KC_3, C(KC_3)),
    [TD_G4] = ACTION_TAP_DANCE_DOUBLE(KC_4, C(KC_4)),
    [TD_G5] = ACTION_TAP_DANCE_DOUBLE(KC_5, C(KC_5)),
    [TD_IDLE] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, S(KC_DOT)),
};

char wpm_str[21];
char kc_str[21];
char lyr_str[21];
uint16_t key_count = 0;

// Timers for the hold to close braces.
static bool is_hrb_active = false;
static uint16_t hrb_timer = 0;

static bool is_hsb_active = false;
static uint16_t hsb_timer = 0;

static bool is_hcb_active = false;
static uint16_t hcb_timer = 0;

// Variable for keeping track of how many layer active keys are held down.
// QMK does not like it when you have two keys that activate the same layer.
// Releaseing the key you entered the layer with while holding down the other
// key will not keep you in the layer.
static uint16_t layer_keys_active = 0;

// Globals Toggles
static bool spcu_is_space = true;

// Alt on hold, OS on tap._
#define KC_ALTOS LALT_T(KC_LGUI)
#define KC_BSCT LCTL_T(KC_BSPC)

#define _QWERTY 0
#define _COLEMAK 1
#define _FPS 2
#define _AOE 3
#define _LAYER 4
#define _FPSL 5
#define _AOEL 6
#define _FN 7

#define MO_NAV MO(_LAYER)
#define MO_FN MO(_FN)
#define MO_FPSL MO(_FPSL)
#define MO_AOEL MO(_AOEL)

#define DF_QWER DF(_QWERTY)
#define DF_COLM DF(_COLEMAK)
#define DF_FPS DF(_FPS)
#define DF_AOE DF(_AOE)

// Tap dance for brackets.
#define KC_TSB TD(TD_SB)
#define KC_TCB TD(TD_CB)
#define KC_TNB TD(TD_NB)

// One Shot Modifiers.
#define KC_OSMC OSM(MOD_LCTL)
#define KC_OSMS OSM(MOD_LSFT)

#define KC_SFTBS SFT_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base - Default.
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_OSMS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_OSMC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_RALT,  KC_LAYR, KC_SPCU,    KC_LSFT, KC_LAYR, KC_LGUI
                                      //'--------------------------'  '--------------------------'
  ),


  // Default navigation Numbers Symbols.
  [_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_PLUS,    KC_1,    KC_2,    KC_3,  KC_DOT,                      XXXXXXX, KC_HOME,   KC_UP,  KC_END, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  KC_MIN,    KC_4,    KC_5,    KC_6,    KC_0,                      XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_EQLS,    KC_7,    KC_8,    KC_9,  KC_COM,                      XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,   MO_FN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
                                      //'--------------------------'  '--------------------------'
  ),

  // Default navigation Numbers Symbols.
  [_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_LBR4, KC_LBRC, KC_LCBR, KC_LPRN, XXXXXXX,                      XXXXXXX, KC_RBRC, KC_RCBR, KC_RPRN, KC_RPR4,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, KC_BCKS, XXXXXXX,                      XXXXXXX, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX,   MO_FN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
                                      //'--------------------------'  '--------------------------'
  ),

KC_LCBR
KC_RCBR
KC_LPRN
KC_RPRN

  // Function and Adjust
  [_FN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,    KC_3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, DF_QWER, DF_COLM, DF_AOE,  DF_FPS,  CG_TOGG,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  ),

  // FPS Layer, number pad centered on index stagger.
  [_FPSL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_ESC,    KC_1,    KC_2,    KC_3, XXXXXXX,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,    KC_7,    KC_8,    KC_9,    KC_0,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_RALT, KC_LAYR,  KC_SPC,    KC_LSFT, KC_LAYR, KC_LCTL
                                      //'--------------------------'  '--------------------------'
  ),

  // AOE Layer, custom binds.
  [_AOEL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, TD(TD_G1),TD(TD_G2),TD(TD_G3),TD(TD_G4),TD(TD_G5),                    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,RCS(KC_B),   RCS(KC_A), TD(TD_IDLE), RCS(KC_H),  A(KC_COMM),           KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,RCS(KC_S),   RCS(KC_K), RCS(KC_V),  KC_Q, XXXXXXX,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_LAYR,  KC_SPC,    KC_LSFT, KC_LAYR, KC_LGUI
                                      //'--------------------------'  '--------------------------'
  ),
};


#ifdef OLED_DRIVER_ENABLE

// Rotate screen so it faces the user.
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}


#define L_DEFAULT 0
#define L_LAYER 16
#define L_FN 128


void oled_render_layer_state(void) {
    // Render Layer, WPM, key presses and toggles to the screen.
    // ._____.
    // |BASE |
    // |WPM: |
    // |00060|
    // |KEYS:|
    // |99999|
    // |     |
    // |     |
    // |_____|

    switch (layer_state) {
        case L_DEFAULT:
            switch (biton32(default_layer_state)) {
                case 0: oled_write_ln("QWERT ", false); break;
                case 1: oled_write_ln("COLMC ", false); break;
                case 2: oled_write_ln("FPS  ", false); break;
                case 3: oled_write_ln("AOE  ", false); break;
        } break;
        case L_LAYER: oled_write_ln("LYR  ", false ); break;
        case L_FN: oled_write_ln("FN   ", false); break;
        case L_FN | L_LAYER: oled_write_ln("FN   ", false); break;
    }

    sprintf(wpm_str, "%05d", get_current_wpm());
    sprintf(kc_str, "%05u", key_count);

    oled_write_ln("WPM: ", false);
    oled_write_ln(wpm_str, false);

    oled_write_ln("KEYS:", false);
    oled_write_ln(kc_str, false);

    char mods[] = "     ";

    if ((get_mods() & MOD_MASK_CTRL) | (get_oneshot_mods() & MOD_MASK_CTRL)) {
        mods[0] = 'C';
    }

    if ((get_mods() & MOD_MASK_SHIFT) | (get_oneshot_mods() & MOD_MASK_SHIFT)) {
        mods[1] = 'S';
    }

    if ((get_mods() & MOD_MASK_ALT) | (get_oneshot_mods() & MOD_MASK_ALT)) {
        mods[2] = 'A';
    }

    if ((get_mods() & MOD_MASK_GUI) | (get_oneshot_mods() & MOD_MASK_GUI)) {
        mods[3] = 'G';
    }

    oled_write_ln("MODS:", false);
    oled_write_ln(mods, false);

}

// Only use the master screen.
void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
    }
}

#endif // OLED_DRIVER_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Keypress counter
    if (record->event.pressed) {
        key_count += 1;
    }

    switch (keycode) {

        case KC_LAYR:

            if (record->event.pressed) {
                layer_keys_active += 1;
                if (layer_keys_active == 1) {
                    layer_on(_LAYER);
                }
                return false;
            }

            else {
                layer_keys_active -= 1;
                if (layer_keys_active == 0) {
                    layer_off(_LAYER);
                }
                return false;
            }
        // Handle special keycode for space / underscore on shift or toggle.
        case KC_SPCU:
            if (record->event.pressed) {
                // If shift if pressed send -/_ which is _ on shift.
                if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    // Save what shift key was pressed at the time.
                    // So we know we have to release the _ rather than a space.
                    spcu_is_space = false;
                    register_code(KC_MINS);
                }
                // No shift, send normal space.
                else {
                    spcu_is_space = true;
                    register_code(KC_SPC);
                }
            }
            else {
                // Space released and we were treating space as space.
                if (spcu_is_space) {
                    unregister_code(KC_SPC);
                // Space released and we were treating space as _.
                } else {
                    unregister_code(KC_MINS);
                }
            }
            return false;

        case KC_HRB:
            if (record->event.pressed) {
                if (!is_hrb_active) {
                    is_hrb_active = true;
                    hrb_timer = timer_read();
                }
            } else {
                if (is_hrb_active) {
                    is_hrb_active = false;
                    register_code(KC_LSFT);
                    register_code(KC_9);
                    unregister_code(KC_9);
                    unregister_code(KC_LSFT);
                }
            }
            return false;

        case KC_HSB:
            if (record->event.pressed) {
                if (!is_hsb_active) {
                    is_hsb_active = true;
                    hsb_timer = timer_read();
                }
            } else {
                if (is_hsb_active) {
                    is_hsb_active = false;
                    register_code(KC_LBRACKET);
                    unregister_code(KC_LBRACKET);
                }
            }
            return false;

        case KC_HCB:
            if (record->event.pressed) {
                if (!is_hcb_active) {
                    is_hcb_active = true;
                    hcb_timer = timer_read();
                }
            } else {
                if (is_hcb_active) {
                    is_hcb_active = false;
                    register_code(KC_LSFT);
                    register_code(KC_LBRACKET);
                    unregister_code(KC_LBRACKET);
                    unregister_code(KC_LSFT);
                }
            }
            return false;

    }
    return true;
}


void matrix_scan_user(void) {
    if (is_hrb_active) {
        if (timer_elapsed(hrb_timer) > 175) {
            is_hrb_active = false;
            register_code(KC_LSFT);
            register_code(KC_0);
            unregister_code(KC_0);
            unregister_code(KC_LSFT);
        }
    }

    if (is_hsb_active) {
        if (timer_elapsed(hsb_timer) > 175) {
            is_hsb_active = false;
            register_code(KC_RBRACKET);
            unregister_code(KC_RBRACKET);
        }
    }

    if (is_hcb_active) {
        if (timer_elapsed(hcb_timer) > 175) {
            is_hcb_active = false;
            register_code(KC_LSFT);
            register_code(KC_RBRACKET);
            unregister_code(KC_RBRACKET);
            unregister_code(KC_LSFT);
        }
    }
}