/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS  8
#define MATRIX_COLS  5

// Left
#define MATRIX_ROW_PINS { D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F7, B1, B3, B2, B6 }

// Right
#define MATRIX_ROW_PINS_RIGHT { B1, B3, B2, B6 }
#define MATRIX_COL_PINS_RIGHT { C6, D7, E6, B4, B5 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define USE_SERIAL
#define SOFT_SERIAL_PIN D0 // or D1, D2, D3, E6
#define SPLIT_USB_DETECT

#define TAPPING_TERM 200
#define MOUSEKEY_MAX_SPEED 8
#define MOUSEKEY_TIME_TO_MAX 50
#define MOUSEKEY_MOVE_DELTA 6
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40
