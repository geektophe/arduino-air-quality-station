# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

## Pathes
ARDUINO_SKETCHBOOK   = $(HOME)/git/arduino
ARDMK_DIR            = /usr/local/share/arduino-makefile
ARDUINO_DIR          = /usr/local/share/arduino
AVRDUDE_CONF         = /etc/avrdude.conf
AVR_TOOLS_DIR        = /usr/local
## Compilation options
LDFLAGS              = -Wl,-u,vfprintf -lprintf_flt
ARDUINO_LIBS         = Wire SPI LiquidCrystal_I2C dsm501-interrupt DHT #station-sensors
## Board info
BOARD_TAG            = nano
BOARD_SUB            = atmega328
#BOARD_TAG            = uno
## Uppload and console
MONITOR_PORT         = /dev/cuaU0
#ISP_PROG             = avrisp
#ISP_PORT             = /dev/cuaU1
#AVRDUDE_ARD_BAUDRATE = 19200

include ${ARDMK_DIR}/Arduino.mk

console:
	cu -l $(MONITOR_PORT) -s 9600

# --- leonardo (or pro micro w/leo bootloader)
#BOARD_TAG    = leonardo
#MONITOR_PORT = /dev/ttyACM0
#include /usr/share/arduino/Arduino.mk

# --- mega2560 ide 1.0
#BOARD_TAG    = mega2560
#ARDUINO_PORT = /dev/ttyACM0
#include /usr/share/arduino/Arduino.mk

# --- mega2560 ide 1.6
#BOARD_TAG    = mega
#BOARD_SUB    = atmega2560
#MONITOR_PORT = /dev/ttyACM0
#ARDUINO_DIR  = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- nano ide 1.0
#BOARD_TAG    = nano328
#MONITOR_PORT = /dev/ttyUSB0
#include /usr/share/arduino/Arduino.mk

# --- nano ide 1.6
#BOARD_TAG   = nano
#BOARD_SUB   = atmega328
#ARDUINO_DIR = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- pro mini
#BOARD_TAG    = pro5v328
#MONITOR_PORT = /dev/ttyUSB0
#include /usr/share/arduino/Arduino.mk

# --- sparkfun pro micro
#BOARD_TAG         = promicro16
#ALTERNATE_CORE    = promicro
#BOARDS_TXT        = $(HOME)/arduino/hardware/promicro/boards.txt
#BOOTLOADER_PARENT = $(HOME)/arduino/hardware/promicro/bootloaders
#BOOTLOADER_PATH   = caterina
#BOOTLOADER_FILE   = Caterina-promicro16.hex
#ISP_PROG     	   = usbasp
#AVRDUDE_OPTS 	   = -v
#include /usr/share/arduino/Arduino.mk

# --- chipkit
#BOARD_TAG = mega_pic32
#MPIDE_DIR = /where/you/installed/mpide-0023-linux64-20130817-test
#include /usr/share/arduino/chipKIT.mk

# --- pinoccio
#BOARD_TAG         = pinoccio256
#ALTERNATE_CORE    = pinoccio
#BOOTLOADER_PARENT = $(HOME)/arduino/hardware/pinoccio/bootloaders
#BOOTLOADER_PATH   = STK500RFR2/release_0.51
#BOOTLOADER_FILE   = boot_pinoccio.hex
#CFLAGS_STD        = -std=gnu99
#CXXFLAGS_STD      = -std=gnu++11
#include /usr/share/arduino/Arduino.mk

# --- fio
#BOARD_TAG = fio
#include /usr/share/arduino/Arduino.mk

# --- atmega-ng ide 1.6
#BOARD_TAG    = atmegang
#BOARD_SUB    = atmega168
#MONITOR_PORT = /dev/ttyACM0
#ARDUINO_DIR  = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- arduino-tiny ide 1.0
#ISP_PROG     	    = usbasp
#BOARD_TAG          = attiny85at8
#ALTERNATE_CORE     = tiny
#ARDUINO_VAR_PATH   = $(HOME)/arduino/hardware/tiny/cores/tiny
#ARDUINO_CORE_PATH  = $(HOME)/arduino/hardware/tiny/cores/tiny
#AVRDUDE_OPTS 	    = -v
#include /usr/share/arduino/Arduino.mk

# --- arduino-tiny ide 1.6
#ISP_PROG       = usbasp
#BOARD_TAG      = attiny85at8
#ALTERNATE_CORE = tiny
#ARDUINO_DIR    = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- damellis attiny ide 1.0
#ISP_PROG       = usbasp
#BOARD_TAG      = attiny85
#ALTERNATE_CORE = attiny-master
#AVRDUDE_OPTS   = -v
#include /usr/share/arduino/Arduino.mk

# --- damellis attiny ide 1.6
#ISP_PROG       = usbasp
#BOARD_TAG      = attiny
#BOARD_SUB      = attiny85
#ALTERNATE_CORE = attiny
#F_CPU          = 16000000L
#ARDUINO_DIR    = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- teensy3
#BOARD_TAG 	 = teensy31
#ARDUINO_DIR = /where/you/installed/the/patched/teensy/arduino-1.0.6
#include /usr/share/arduino/Teensy.mk

# --- mighty 1284p
#BOARD_TAG         = mighty_opt
#BOARDS_TXT        = $(HOME)/arduino/hardware/mighty-1284p/boards.txt
#BOOTLOADER_PARENT = $(HOME)/arduino/hardware/mighty-1284p/bootloaders
#BOOTLOADER_PATH   = optiboot
#BOOTLOADER_FILE   = optiboot_atmega1284p.hex
#ISP_PROG     	   = usbasp
#AVRDUDE_OPTS 	   = -v
#include /usr/share/arduino/Arduino.mk

# --- atmega328p on breadboard
#BOARD_TAG    = atmega328bb
#ISP_PROG     = usbasp
#AVRDUDE_OPTS = -v
#BOARDS_TXT   = $(HOME)/arduino/hardware/breadboard/boards.txt
#include /usr/share/arduino/Arduino.mk
