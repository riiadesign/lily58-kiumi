# ObliviousGmn // Dokuu // October 2020 // Rules

# No ..
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
MOUSEKEY_ENABLE = no
BLUETOOTH_ENABLE  = no  # Enable Bluetooth with the Adafruit EZ-Key HID
NKRO_ENABLE = no
RGBLIGHT_ENABLE = no

# Yes ..
OLED_DRIVER_ENABLE = yes
EXTRAKEY_ENABLE= yes # For Media Keys
WPM_ENABLE = yes
LTO_ENABLE = yes     # Makes hex file smaller

# Elite C ..
BOOTLOADER = qmk-dfu

SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \