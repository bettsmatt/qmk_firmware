#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,                    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                    R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                    R20, R21, R22, R23, R24, R25, \
<<<<<<< HEAD
              L32, L33,                                        R32, R33, \
                        L34, L35,                    R30, R31, \
                        L44, L45,                    R40, R41, \
              L42, L43,                                        R42, R43 \
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { XXX, XXX, L32, L33, L34, L35 }, \
    { XXX, XXX, L42, L43, L44, L45 }, \
\
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { R30, R31, R32, R33, XXX, XXX }, \
    { R40, R41, R42, R43, XXX, XXX } \
}
=======
              L32, L33,                                        R32, R33,           \
                   L43, L44, L45,                    R40, R41, R42,                \
                        L54, L55,                    R50, R51                      \
    ) \
    { \
        { L00,   L01,   L02, L03, L04, L05   }, \
        { L10,   L11,   L12, L13, L14, L15   }, \
        { L20,   L21,   L22, L23, L24, L25   }, \
        { KC_NO, KC_NO, L32, L33, L43, KC_NO }, \
        { KC_NO, KC_NO, L45, L55, L54, L44   }, \
\
        { R05,   R04,   R03, R02, R01,   R00   }, \
        { R15,   R14,   R13, R12, R11,   R10   }, \
        { R25,   R24,   R23, R22, R21,   R20   }, \
        { KC_NO, KC_NO, R33, R32, R42,   KC_NO }, \
        { KC_NO, KC_NO, R40, R50, R51,   R41 } \
\
   }
>>>>>>> Many changes from tweaking many boards
