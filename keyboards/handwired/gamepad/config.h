#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2020
#define DEVICE_VER      0x0001
#define MANUFACTURER    Matthew Betts
#define PRODUCT         6x5Gamepad
#define DESCRIPTION     6x5Gamepad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { F7, B1, B3, B2, B6}
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5