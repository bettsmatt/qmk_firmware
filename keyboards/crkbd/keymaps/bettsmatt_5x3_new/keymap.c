// Quick reference build commands.
// qmk compile -kb crkbd -km bettsmatt_5x3_new && cp .build/crkbd_rev1_bettsmatt_5x3_new.hex /mnt/c/Users/iplk/Documents/
#include QMK_KEYBOARD_H

enum {
    _COLMAC,
    _SHORT,
    _NAV,
    _SYM,
    _NUM,
    _FN,
};

#define KC_CU C(KC_UP)
#define KC_CL C(KC_LEFT)
#define KC_CR C(KC_RIGHT)
#define KC_PIC G(S(KC_5))

#define MO_NAV MO(_NAV)
#define MO_SYM MO(_SYM)
#define MO_NUM LT(_NUM, KC_Z)
#define MO_FN  LT(_FN, KC_SLSH)
#define MO_CTL LM(_SHORT, MOD_LCTL)
#define MO_GUI LT(layer, kc)

#define GUI_DOT LGUI_T(KC_DOT)

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
enum {
    SFT_F,
    SFT_P,
    SFT_V,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [SFT_F]  = ACTION_TAP_DANCE_DOUBLE(KC_F, S(KC_F)),
    [SFT_P]  = ACTION_TAP_DANCE_DOUBLE(KC_P, S(KC_P)),
    [SFT_V]  = ACTION_TAP_DANCE_DOUBLE(KC_V, S(KC_V))
};

#define KC_SF TD(SFT_F)
#define KC_SP TD(SFT_P)
#define KC_SV TD(SFT_V)
#define KC_STAB S(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base - COLMAC
  [_COLMAC] = LAYOUT(
  //|-----------------------------------------------------+        +-----------------------------------------------------|
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y, KC_BSPC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      XXXXXXX,  MO_NUM,    KC_X,    KC_C,    KC_V,    KC_B,             KC_K,    KC_M, KC_COMM, GUI_DOT,   MO_FN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
                                 XXXXXXX,  MO_NAV,  KC_SPC,          KC_LSFT,  MO_SYM, XXXXXXX
  //                           +--------+--------+--------+        +--------+--------+--------+
  ),

  // CTL for Alphas.
  // Allows for one handed copy / paste.
  [_SHORT] = LAYOUT(
  //,-----------------------------------------------------.        ,-----------------------------------------------------.
      _______,    KC_Q,    KC_W,   KC_SF,   KC_SP,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y, KC_BSPC, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______,    KC_Z,    KC_X,    KC_C,   KC_SV,    KC_B,             KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,          _______, _______, _______
  //                           +--------+--------+--------+        +--------+--------+--------+
  ),

  // Navigation with mods and symbols.
  [_NAV] = LAYOUT(
  //,-----------------------------------------------------.        ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, C(KC_F), C(KC_P), XXXXXXX,          XXXXXXX, KC_BSPC,   KC_UP,  KC_DEL, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______, KC_OGUI, KC_OALT, KC_OCTL, KC_OSFT, XXXXXXX,           KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,          KC_STAB,  KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,          _______, _______, _______
  //                           +--------+--------+--------+        +--------+--------+--------+
  ),

  // Navigation with mods and symbols.
  [_SYM] = LAYOUT(
  //,-----------------------------------------------------.        ,-----------------------------------------------------.
      _______, KC_SCLN, KC_QUOT,  KC_DQT,  KC_GRV, KC_COLN,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_PIPE, KC_UNDS, KC_BSLS, XXXXXXX,          XXXXXXX, KC_OSFT, KC_OCTL, KC_OALT, KC_OGUI, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______,   KC_LT, KC_PLUS, KC_MINS,  KC_EQL,   KC_GT,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,          _______, _______, _______
  //                           +--------+--------+--------+        +--------+--------+--------+
  ),

  // Numbers and Tab
  // Would be good to have the nav mod like in alt tab held down for a limit or until you loose the layer.
  [_NUM] = LAYOUT(
  //,-----------------------------------------------------.        ,-----------------------------------------------------.
      _______,  KC_ESC, KC_HOME,  KC_TAB,  KC_END, KC_PGUP,          KC_LPRN,    KC_1,    KC_2,    KC_3, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______, KC_OGUI, KC_OALT, KC_OCTL, KC_OSFT, KC_PGDN,          KC_BSLS,    KC_4,    KC_5,    KC_6,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX,   KC_CL,   KC_CU,   KC_CR,  KC_PIC,          KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,          _______, _______, _______
  //                           +--------+--------+--------+        +--------+--------+--------+
  ),

  // Function.
  [_FN] = LAYOUT(
  //,-----------------------------------------------------.        ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          CG_TOGG,  KC_INS, KC_CAPS, KC_PSCR, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,          XXXXXXX, KC_OSFT, KC_OCTL, KC_OALT, KC_OGUI, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------,        ,--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,          _______, _______, _______
  //                           +--------+--------+--------+        +--------+--------+--------+
  ),

};
