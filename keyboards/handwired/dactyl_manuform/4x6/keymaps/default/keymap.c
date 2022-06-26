// qmk compile -kb handwired/dactyl_manuform/4x6 -km default
#include QMK_KEYBOARD_H

#define _BASE 0
#define _LYR 1
#define _MODS 3
#define _FN 4

enum {
    KC_LAYR = SAFE_RANGE,
    KC_HRB,
    KC_HSB,
    KC_HCB,
};

// Variable for keeping track of how many layer active keys are held down.
// QMK does not like it when you have two keys that activate the same layer.
// Releaseing the key you entered the layer with while holding down the other
// key will not keep you in the layer.
static uint16_t layer_keys_active = 0;

// One Shot Modifiers.
#define KC_OSMC OSM(MOD_LCTL)
#define KC_OSMS OSM(MOD_LSFT)
#define KC_OSMA OSM(MOD_LALT)
#define KC_OSMG OSM(MOD_LGUI)


// Timers for the hold to close braces.
static bool is_hrb_active = false;
static uint16_t hrb_timer = 0;

static bool is_hsb_active = false;
static uint16_t hsb_timer = 0;

static bool is_hcb_active = false;
static uint16_t hcb_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT( \
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
         KC_TAB,      KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                 KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,    KC_ESC,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        KC_LSFT,      KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                 KC_H,      KC_J,      KC_K,      KC_L,   KC_SCLN,   KC_QUOT,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        KC_LCTL,      KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,                 KC_N,      KC_M,   KC_COMM,    KC_DOT,   KC_SLSH,    KC_ENT,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
                              XXXXXXX,   XXXXXXX,                                                          XXXXXXX,   XXXXXXX,
//                        +----------+----------+                                                      +----------+----------+
                                         KC_LALT,  KC_SPACE,   KC_LGUI,              MO(_NUM),  KC_LSFT,  MO(_LYR),
//                                   +----------+----------+----------+          +----------+----------+----------+
                                                    XXXXXXX,   XXXXXXX,              XXXXXXX,   XXXXXXX
//                                              +----------+----------+          +----------+----------+
),


[_LYR] = LAYOUT(
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        _______,   XXXXXXX,   KC_LPRN,    KC_GRV,   KC_RPRN,   XXXXXXX,              KC_PGUP,   KC_BSPC,     KC_UP,    KC_DEL    KC_PGDN,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        _______,   XXXXXXX,   KC_LBRC,   KC_UNDS,   KC_RBRC,   KC_BSLS,              KC_HOME,   KC_LEFT,   KC_DOWN,   KC_RGHT,    KC_END,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        _______,   XXXXXXX,   KC_PLUS,   KC_MINS,    KC_EQL,   XXXXXXX,              KC_CAPS,   KC_LSFT,   KC_LCTL,   XXXXXXX,   XXXXXXX,   MO(_FN),
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
                              XXXXXXX,   XXXXXXX,                                                          XXXXXXX,   XXXXXXX,
//                        +----------+----------+                                                      +----------+----------+
                                         _______,   _______,   _______,              _______,   _______,   _______,
//                                   +----------+----------+----------+          +----------+----------+----------+
                                                    XXXXXXX,   XXXXXXX,              XXXXXXX,   XXXXXXX
//                                              +----------+----------+          +----------+----------+
),


[_NUM] = LAYOUT(
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        _______,   XXXXXXX,      KC_1,      KC_2,      KC_3,   KC_COMM,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        _______,   XXXXXXX,      KC_4,      KC_5,      KC_6,      KC_0,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
        _______,   XXXXXXX,      KC_7,      KC_8,      KC_9,    KC_DOT,              XXXXXXX,   KC_LSFT,   KC_LCTL,   XXXXXXX,   XXXXXXX,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
                              XXXXXXX,   XXXXXXX,                                                          XXXXXXX,   XXXXXXX,
//                        +----------+----------+                                                      +----------+----------+
                                         _______,   _______,   _______,              _______,   _______,   _______,
//                                   +----------+----------+----------+          +----------+----------+----------+
                                                    XXXXXXX,   XXXXXXX,              XXXXXXX,   XXXXXXX
//                                              +----------+----------+          +----------+----------+
),


[_FN] = LAYOUT(
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
       XXXXXXX,   XXXXXXX,      KC_F1,     KC_F2,     KC_F3,    KC_F10,                RESET,   LCG_SWP,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
       XXXXXXX,   XXXXXXX,      KC_F4,     KC_F5,     KC_F6,    KC_F11,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
       XXXXXXX,   XXXXXXX,      KC_F7,     KC_F8,     KC_F9,    KC_F12,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
//  |----------+----------+----------+----------+----------+----------+          +----------+----------+----------+----------+----------+----------|
                              XXXXXXX,   XXXXXXX,                                                          XXXXXXX,   XXXXXXX,
//                        +----------+----------+                                                      +----------+----------+
                                        _______,   _______,   _______,              _______,   _______,   _______,
//                                   +----------+----------+----------+          +----------+----------+----------+
                                                   XXXXXXX,   XXXXXXX,              XXXXXXX,   XXXXXXX
//                                              +----------+----------+          +----------+----------+
)
};


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
                    layer_on(_LYR);
                }
                return false;
            }

            else {
                layer_keys_active -= 1;
                if (layer_keys_active == 0) {
                    layer_off(_LYR);
                }
                return false;
            }

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

