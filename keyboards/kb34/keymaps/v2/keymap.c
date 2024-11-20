// Quick reference build commands.
// qmk compile -kb kb34 -km v2 && cp ../.build/kb34_v2.hex /mnt/c/Users/iplk/Documents/
// cp .build/kb34_v2.hex /mnt/c/Users/iplk/Documents/
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
  //|--------------------------------------------+--------+--------------------------------------------|
         KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       MO_NUM,    KC_X,    KC_C,    KC_V,    KC_B,             KC_K,    KC_M, KC_COMM, GUI_DOT,   MO_FN,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
                                  MO_NAV,  KC_SPC,          KC_LSFT,  MO_SYM
  //                           +--------+--------+--------+--------+--------+
  ),

  // CTL for Alphas.
  // Allows for one handed copy / paste.
  [_SHORT] = LAYOUT(
  //,--------------------------------------------+--------+--------------------------------------------|
         KC_Q,    KC_W,   KC_SF,   KC_SP,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,   KC_SV,    KC_B,             KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           +--------+--------+--------+--------+--------+
  ),

  // Navigation with mods and symbols.
  [_NAV] = LAYOUT(
  //|--------------------------------------------+--------+--------------------------------------------|
      C(KC_Q), C(KC_W), C(KC_F), C(KC_P), C(KC_G),          XXXXXXX, KC_BSPC,   KC_UP,  KC_DEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, C(KC_D),           KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B),          KC_STAB,  KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           +--------+--------+--------+--------+--------+
  ),

  // Navigation with mods and symbols.
  [_SYM] = LAYOUT(
  //|--------------------------------------------+--------+--------------------------------------------|
      KC_SLSH, KC_BSLS, KC_QUOT,  KC_GRV, KC_SCLN,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------------------------------------------+--------+--------------------------------------------|
      KC_LBRC, KC_LPRN, KC_UNDS, KC_RPRN, KC_RBRC,          XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  //|--------------------------------------------+--------+--------------------------------------------|
        KC_LT, KC_PLUS, KC_MINS,  KC_EQL,   KC_GT,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------------------------------------------+--------+--------------------------------------------|
                                 _______, _______,          _______, _______
  //                           +--------+--------+--------+--------+--------+
  ),

  // Numbers and Tab
  // Would be good to have the nav mod like in alt tab held down for a limit or until you loose the layer.
  [_NUM] = LAYOUT(
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC, KC_HOME,  KC_TAB,  KC_END, KC_PGUP,          KC_LPRN,    KC_1,    KC_2,    KC_3, KC_RPRN,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_PGDN,          XXXXXXX,    KC_4,    KC_5,    KC_6,    KC_0,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_CL,   KC_CU,   KC_CR,  KC_PIC,          KC_LBRC,    KC_7,    KC_8,    KC_9, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           +--------+--------+--------+--------+--------+
  ),

  // Function.
  [_FN] = LAYOUT(
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          CG_TOGG,  KC_INS, KC_CAPS, KC_PSCR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,          XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_OGUI,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
                                 _______, _______,          _______, _______
  //                           +--------+--------+--------+--------+--------+--------+
  ),

};
