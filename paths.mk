# Directory common source files exist
TOP_DIR = .
TMK_DIR = tmk_core
TMK_PATH = $(TMK_DIR)
LIB_PATH = lib

QUANTUM_DIR = quantum
QUANTUM_PATH = $(QUANTUM_DIR)

DRIVER_DIR = drivers
DRIVER_PATH = $(DRIVER_DIR)

PLATFORM_DIR = platforms
PLATFORM_PATH = $(PLATFORM_DIR)

PROTOCOL_DIR = protocol
PROTOCOL_PATH = $(TMK_DIR)/$(PROTOCOL_DIR)

BUILDDEFS_DIR = builddefs
BUILDDEFS_PATH = $(BUILDDEFS_DIR)

BUILD_DIR := build

COMMON_VPATH := $(TOP_DIR)
COMMON_VPATH += $(TMK_PATH)
COMMON_VPATH += $(QUANTUM_PATH)
COMMON_VPATH += $(QUANTUM_PATH)/keymap_extras
COMMON_VPATH += $(QUANTUM_PATH)/audio
COMMON_VPATH += $(QUANTUM_PATH)/process_keycode
COMMON_VPATH += $(QUANTUM_PATH)/sequencer
COMMON_VPATH += $(DRIVER_PATH)
