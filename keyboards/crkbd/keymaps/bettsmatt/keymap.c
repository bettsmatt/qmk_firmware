#include QMK_KEYBOARD_H

enum {
    KC_SPCU = SAFE_RANGE,
    KC_G1,
    KC_G2,
    KC_G3,
    KC_G4,
    KC_G5,
    KC_G6,
    KC_G7,
    KC_G8,
    KC_G9,
    KC_G0,
};


char wpm_str[21];
char kc_str[21];

// Globals Toggles

// Pinned application switching.
static bool is_gui_active = true;
static uint16_t gui_timer = 0;

static bool spcu_is_space = true;
static bool game_active = false;

uint16_t key_count = 0;

// Alt on hold, OS on tap.
#define KC_ALTOS LALT_T(KC_LGUI)

// VSCode search in all files.
#define KC_CSF RCS(KC_F)

// Paste with no formatting.
#define KC_CSV RCS(KC_V)

#define _BASE 0
#define _GAME 1
#define _GNUM 2
#define _NAVK 3
#define _NAVM 4
#define _NUM 5
#define _SYM 6
#define _FN 7
#define MO_NAVK MO(_NAVK)
#define MO_NAVM MO(_NAVM)
#define MO_NUM MO(_NUM)
#define MO_SYM MO(_SYM)
#define MO_FN MO(_FN)
#define MO_GNUM MO(_GNUM)

// Switch base layer to game.
#define DF_GAME DF(_GAME)

// Switch base layer to defaut.
#define DF_BASE DF(_BASE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base - Default
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ALTOS, MO_SYM, KC_SPCU,    KC_RSPC,  MO_NAVK,  MO_NUM
                                      //'--------------------------'  '--------------------------'
  ),

  // Base - Game
  // Similar to base, no windows key on alt, and numbers layer is activated by the left thumb and not the right thumb.
  [_GAME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LALT, MO_GNUM, KC_SPCU,    KC_RSPC,  MO_NAVK,  MO_SYM
                                      //'--------------------------'  '--------------------------'
  ),

  // Game - Number
  // Moved all numbers to the left had side.
  [_GNUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_PLUS, KC_MINS,  KC_EQL, KC_ASTR, KC_PSLS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX, DF_BASE,    XXXXXXX,  XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  ),

  // Navigation - Keys
  // LHS numbers need some custom code to continue holding GUI for a few ms after releaseing so you can switch tabs between multiple tabs.
  [_NAVK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_G1,   KC_G2,   KC_G3,   KC_G4,   KC_G5,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, C(KC_X), C(KC_C), C(KC_V), XXXXXXX,   MO_FN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LGUI, KC_SPCU,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  ),

  // Navigation - Mouse
  // Not used
  [_NAVM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  ),

  // Number
  // Numbers along the top.
  // Dedicated numpad on the right hand aligned with top row of numbers.
  // Maths operations on the left under the number row..
  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO, KC_PLUS, KC_MINS,  KC_EQL, KC_ASTR, KC_PSLS,                      XXXXXXX,    KC_4,    KC_5,    KC_6,  KC_DOT,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, C(KC_X), C(KC_C), C(KC_V), XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX,   MO_FN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ALTOS,  KC_DOT, KC_SPCU,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  ),

  // Symbol and Marco
  // Symbols on the top row mirroring number positions.
  // [] and {} split across the middle of the keyboard.
  // Macros keys on left hand.
  [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,  KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO, XXXXXXX, XXXXXXX, C(KC_T),  KC_CSF, KC_LBRC,                      KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX,  KC_CSV, KC_LCBR,                      KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, DF_GAME,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  ),

  // Function and Adjust
  // Functions keys along the top.
  // Various toggles on the left.
  [_FN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, CG_TOGG,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                      //'--------------------------'  '--------------------------'
  )

};


#ifdef OLED_DRIVER_ENABLE

// Rotate screen so it faces the user.
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}


#define L_DEFAULT 0
#define L_GNUM 4
#define L_NAVK 8
#define L_NAVM 16
#define L_NUM 32
#define L_SYMBOL 64
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
            if (game_active) {
                oled_write_ln("GAME ", false);
            } else {
                oled_write_ln("BASE ", false);
            }
            break;
        case L_NAVK:
            oled_write_ln("NAV-K", false);
            break;
        case L_NUM:
            oled_write_ln("NUM  ", false);
            break;
        case L_SYMBOL:
            oled_write_ln("SYM  ", false);
            break;

        // Activated with two layers.
        case L_FN:
        case L_FN | L_NAVK:
            oled_write_ln("FN   ", false);
            break;

        // Activated with two layers.
        case L_NAVM:
        case L_NAVM | L_NAVK:
            oled_write_ln("NAV-M", false);
            break;
        case L_GNUM:
            oled_write_ln("NUM-G", false);
            break;
    }

    sprintf(wpm_str, "%05d", get_current_wpm());
    sprintf(kc_str, "%05u", key_count);

    oled_write_ln("WPM: ", false);
    oled_write_ln(wpm_str, false);

    oled_write_ln("KEYS:", false);
    oled_write_ln(kc_str, false);
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
        // Keep track of what layer is the base layer as this swaps between
        // typing and gaming.
        case DF_GAME:
            game_active = true;
            return true;

        case DF_BASE:
            game_active = false;
            return true;

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
        // Keep GUI active for 10002 ms when cycling between pinned programs.
        // This allows us to tab between two instances of a program.
        case KC_G1:
        case KC_G2:
        case KC_G3:
        case KC_G4:
        case KC_G5:
        case KC_G6:
        case KC_G7:
        case KC_G8:
        case KC_G9:
        case KC_G0:
            if (record->event.pressed) {
                if (!is_gui_active) {
                    is_gui_active = true;
                    register_code(KC_LGUI);
                }
                gui_timer = timer_read();

                switch (keycode) {
                    case KC_G1: register_code(KC_1); break;
                    case KC_G2: register_code(KC_2); break;
                    case KC_G3: register_code(KC_3); break;
                    case KC_G4: register_code(KC_4); break;
                    case KC_G5: register_code(KC_5); break;
                    case KC_G6: register_code(KC_6); break;
                    case KC_G7: register_code(KC_7); break;
                    case KC_G8: register_code(KC_8); break;
                    case KC_G9: register_code(KC_9); break;
                    case KC_G0: register_code(KC_0); break;
                }
            } else {
                switch (keycode) {
                    case KC_G1: unregister_code(KC_1); break;
                    case KC_G2: unregister_code(KC_2); break;
                    case KC_G3: unregister_code(KC_3); break;
                    case KC_G4: unregister_code(KC_4); break;
                    case KC_G5: unregister_code(KC_5); break;
                    case KC_G6: unregister_code(KC_6); break;
                    case KC_G7: unregister_code(KC_7); break;
                    case KC_G8: unregister_code(KC_8); break;
                    case KC_G9: unregister_code(KC_9); break;
                    case KC_G0: unregister_code(KC_0); break;
                }
            }
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_gui_active) {
        if (timer_elapsed(gui_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_gui_active = false;
        }
    }
}