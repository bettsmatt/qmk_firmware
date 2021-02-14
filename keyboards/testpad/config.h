/*
Copyright 2019 imchipwood

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your opion) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAF
#define PRODUCT_ID      0x0913
#define DEVICE_VER      0x0001
#define MANUFACTURER    imchipwood
#define PRODUCT         dumbpad
#define DESCRIPTION     4x4 macro/numpad with rotary encoder


/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

// Black, D7, R1
// Purple, B5, R2
// Blue, B6, R3
// Green, B2, R4

// White, E6, C1
// Grey, B4, C2
// Yello, B3, C3
// Orange, B1, C4,

// Brown, C6, E1
// Red, D4, E1
// Red, F7, E2
// Brown, F6, E2

#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { D7, B5, B6, B2}
#define MATRIX_COL_PINS { E6, B4, B3, B1}
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Rotary encoder */
#define ENCODERS_PAD_A { C6, F7 }
#define ENCODERS_PAD_B { D4, F6 }
#define ENCODER_RESOLUTION 4


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define RGB_DI_PIN F4
#define RGBLED_NUM 24

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8