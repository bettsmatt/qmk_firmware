/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define USE_SERIAL_PD2

#define TAPPING_TERM 150
#define LEADER_TIMEOUT 300

#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_ALPHA

#ifdef MOUSEKEY_ENABLE
    #define MOUSEKEY_DELAY 0
    #define MOUSEKEY_INTERVAL 16
    #define MOUSEKEY_TIME_TO_MAX 120
    #define MOUSEKEY_MAX_SPEED 8
    #define MOUSEKEY_WHEEL_DELAY 0
    #define MOUSEKEY_WHEEL_INTERVAL 16
    #define MK_COMBINED
#endif

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif