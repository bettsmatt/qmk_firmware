#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBB80
#define PRODUCT_ID      0x050D
#define DEVICE_VER      0x0001
#define MANUFACTURER    Hexwire
#define PRODUCT         KB34

#define MATRIX_ROWS 4
#define MATRIX_COLS 10

#define MATRIX_ROW_PINS { D0, F5, B5, B6 }
#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, D4, C6, D7, E6, B4 }

#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5
#define TAPPING_TERM 175

#endif

