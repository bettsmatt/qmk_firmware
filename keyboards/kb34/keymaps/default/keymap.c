// Quick reference build commands.
// qmk compile -kb kb34 -km default
// cp .build/kb34_default.hex /mnt/c/Users/iplk/Documents/
#include QMK_KEYBOARD_H

enum {
    _COLMAC,
    _SHORT,
    _NAV,
    _SYM,
    _NUM,
    _FN,
};

#define MO_NAV MO(_NAV)
#define MO_NUM LT(_NUM, KC_Z)
#define MO_FN LT(_FN, KC_SLSH)
#define MO_CTL LM(_SHORT, MOD_LCTL)
#define MO_GUI LT(layer, kc)

#define GUI_DOT LGUI_T(KC_DOT)
#define ALT_X LALT_T(KC_X)

#define KC_OGUI OSM(MOD_LGUI)
#define KC_OALT OSM(MOD_LALT)
#define KC_OCTL OSM(MOD_LCTL)
#define KC_OSFT OSM(MOD_LSFT)

// screenshot
// navigations
// alt tab
// workspace switching
// ctrl delete / backspace

// Switching layer keys to z, x and ? would allow me to have
// z as number layer.
// x as alt tab.
// ? as fn.
// . as sym
// Or I might be able to move some of the brackets onto the alt tab or crtl tab layers.
// Also need to combine mod layer and tap layer functionality.
// enum {
//     SFT_F,
//     SFT_P,
//     SFT_V,
// };

// Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     [SFT_F]  = ACTION_TAP_DANCE_DOUBLE(KC_F, S(KC_F)),
//     [SFT_P]  = ACTION_TAP_DANCE_DOUBLE(KC_P, S(KC_P)),
//     [SFT_V]  = ACTION_TAP_DANCE_DOUBLE(KC_V, S(KC_V))
// };

// #define KC_SF TD(SFT_F)
// #define KC_SP TD(SFT_P)
// #define KC_SV TD(SFT_V)
#define KC_STAB S(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLMAC] = LAYOUT(
  //|--------------------------------------------------------------------------------------------------|
         KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
         KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
       MO_NUM,   ALT_X,    KC_C,    KC_V,    KC_B,             KC_K,    KC_M, KC_COMM, GUI_DOT,   MO_FN,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
                                  MO_CTL,  KC_SPC,          KC_RSFT,  MO_NAV
  //                           |--------+--------+--------+--------+--------|
  ),

  // CTL for Alphas.
  // Allows for one handed copy / paste.
  [_SHORT] = LAYOUT(
  //,--------------------------------------------------------------------------------------------------|
         KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
         KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           |--------+--------+--------+--------+--------|
  ),

  // Navigation with mods and symbols.
  [_NAV] = LAYOUT(
  //,--------------------------------------------------------------------------------------------------|
      KC_TILD, KC_QUOT,  KC_DQT,  KC_GRV, XXXXXXX,           KC_ESC, KC_BSPC,   KC_UP,  KC_DEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
      KC_OGUI, KC_OALT, KC_OCTL, KC_OSFT, KC_UNDS,           KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT, KC_STAB,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
      KC_PIPE, KC_PLUS, KC_MINS, KC_EQL,  KC_BSLS,          KC_HOME,  KC_ENT, KC_PGUP, KC_PGDN, KC_END,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           |--------+--------+--------+--------+--------|
  ),

  // Numbers and Tab
  // Would be good to have the nav mod like in alt tab held down for a limit or until you loose the layer.
  [_NUM] = LAYOUT(
  //,--------------------------------------------------------------------------------------------------|
       KC_ESC,  KC_TAB,  KC_TAB,  KC_TAB, XXXXXXX,          KC_LPRN,    KC_1,    KC_2,    KC_3, KC_RPRN,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
      KC_OGUI, KC_OALT, KC_OCTL, KC_OSFT, XXXXXXX,          XXXXXXX,    KC_4,    KC_5,    KC_6,    KC_0,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
      XXXXXXX, KC_STAB, KC_STAB, KC_STAB, XXXXXXX,          KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           |--------+--------+--------+--------+--------|
  ),

  // Function.
  [_FN] = LAYOUT(
  //,--------------------------------------------------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX         , XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F11,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,          XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F10,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
      XXXXXXX, KC_PSCR,  KC_INS, KC_CAPS, CG_TOGG,          XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
  //|--------+--------+--------+--------+--------+--------,--------,--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           |--------+--------+--------+--------+--------|
  ),

};
