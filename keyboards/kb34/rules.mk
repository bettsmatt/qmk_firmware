# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = qmk-dfu

# Build Options
BOOTMAGIC_ENABLE    = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE     = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE     = no        # Audio control and System control(+450)
CONSOLE_ENABLE      = no         # Console for debug(+400)
COMMAND_ENABLE      = no         # Commands for debug and configuration
SLEEP_LED_ENABLE    = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE         = no            # USB Nkey Rollover
BACKLIGHT_ENABLE    = no       # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE         = no            # MIDI controls
UNICODE_ENABLE      = no         # Unicode
BLUETOOTH_ENABLE    = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE        = no           # Audio output on port C6
TAP_DANCE_ENABLE    = yes
