
#
#	Copyright (C) 2016 Luxon Jean-Pierre
#	gumichan01.olympe.in
#
#	The LunatiX Engine is a SDL2-based game engine.
#	It can be used for open-source or commercial games thanks to the zlib/libpng license.
#
#	Luxon Jean-Pierre (Gumichan01)
#	luxon.jean.pierre@gmail.com
#

# Makefile - LunatiX Engine

.PHONY: clean doxy test


#
# Debug symbol
#

# You can modify the value of DEBUG
# If you want to use the debug or release mode
DEBUG=yes


#
# Variables
#

CC=clang++
LUAC=luac5.1
SCRIPT_FILE=script/LX_config.lua
COMPILED_SCRIPT=$(SCRIPT_FILE)c

# Path to the main file directory
MAIN_PATH=./src/

# Path to the test files
TEST_PATH=./test/

# Executable file
LUNATIX_EXE=lunatix-demo

# Path to the Lunatix engine directories
LUNATIX_PATH=./src/LunatiX/
LUNATIX_BUILD_ROOT=./_build/
LUNATIX_BUILD_DIR=$(LUNATIX_BUILD_ROOT)LunatiX/
LIBRARIES_I_DIR=./include/
LUNATIX_I_PATH=$(LIBRARIES_I_DIR)LunatiX/
UTILS_I_PATH=$(LUNATIX_I_PATH)utils/
SDL2_I_PATH=`pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf`

# Path to the different modules
DEVICE_PATH=$(LUNATIX_PATH)Device/
FILEIO_PATH=$(LUNATIX_PATH)FileIO/
GRAPHICS_PATH=$(LUNATIX_PATH)Graphics/
LIBRARY_PATH=$(LUNATIX_PATH)Library/
MIXER_PATH=$(LUNATIX_PATH)Mixer/
MSG_PATH=$(LUNATIX_PATH)MSGBox/
PARTICLE_PATH=$(LUNATIX_PATH)ParticleEngine/
PHYSICS_PATH=$(LUNATIX_PATH)Physics/
RANDOM_PATH=$(LUNATIX_PATH)Random/
SYSTEM_PATH=$(LUNATIX_PATH)System/
TEXT_PATH=$(LUNATIX_PATH)Text/
TTF_PATH=$(LUNATIX_PATH)TrueTypeFont/
VERSION_PATH=$(LUNATIX_PATH)Version/
UTILS_PATH=$(LUNATIX_PATH)Utilities/

# Path to the different object directories
OBJ_MAIN_PATH=$(LUNATIX_BUILD_DIR)../
OBJ_DEVICE_PATH=$(LUNATIX_BUILD_DIR)Device/
OBJ_FILEIO_PATH=$(LUNATIX_BUILD_DIR)FileIO/
OBJ_GRAPHICS_PATH=$(LUNATIX_BUILD_DIR)Graphics/
OBJ_LIBRARY_PATH=$(LUNATIX_BUILD_DIR)Library/
OBJ_MIXER_PATH=$(LUNATIX_BUILD_DIR)Mixer/
OBJ_MSG_PATH=$(LUNATIX_BUILD_DIR)MSGBox/
OBJ_PARTICLE_PATH=$(LUNATIX_BUILD_DIR)ParticleEngine/
OBJ_PHYSICS_PATH=$(LUNATIX_BUILD_DIR)Physics/
OBJ_RANDOM_PATH=$(LUNATIX_BUILD_DIR)Random/
OBJ_SYSTEM_PATH=$(LUNATIX_BUILD_DIR)System/
OBJ_TEXT_PATH=$(LUNATIX_BUILD_DIR)Text/
OBJ_TTF_PATH=$(LUNATIX_BUILD_DIR)TrueTypeFont/
OBJ_VERSION_PATH=$(LUNATIX_BUILD_DIR)Version/
OBJ_UTILS_PATH=$(LUNATIX_BUILD_DIR)Utilities/

# Path to the different object files
MAIN_OBJ_FILE=$(OBJ_MAIN_PATH)main.o
OBJ_FILES=$(OBJ_DEVICE_PATH)LX_Device.o \
$(OBJ_DEVICE_PATH)LX_Gamepad.o $(OBJ_DEVICE_PATH)LX_Haptic.o \
$(OBJ_FILEIO_PATH)LX_FileIO.o $(OBJ_FILEIO_PATH)LX_FileBuffer.o \
$(OBJ_GRAPHICS_PATH)LX_Graphics.o $(OBJ_GRAPHICS_PATH)LX_Window.o \
$(OBJ_GRAPHICS_PATH)LX_WindowManager.o \
$(OBJ_LIBRARY_PATH)LX_Config.o $(OBJ_LIBRARY_PATH)LX_Library.o \
$(OBJ_MIXER_PATH)LX_Sound.o $(OBJ_MIXER_PATH)LX_Chunk.o \
$(OBJ_MIXER_PATH)LX_Music.o $(OBJ_MIXER_PATH)LX_Mixer.o \
$(OBJ_MSG_PATH)LX_MessageBox.o \
$(OBJ_PARTICLE_PATH)LX_Particle.o $(OBJ_PARTICLE_PATH)LX_ParticleSystem.o \
$(OBJ_PHYSICS_PATH)LX_Hitbox.o $(OBJ_PHYSICS_PATH)LX_Physics.o \
$(OBJ_PHYSICS_PATH)LX_Polygon.o $(OBJ_PHYSICS_PATH)LX_Vector2D.o \
$(OBJ_RANDOM_PATH)LX_Random.o $(OBJ_SYSTEM_PATH)LX_SystemInfo.o \
$(OBJ_SYSTEM_PATH)LX_Log.o $(OBJ_TEXT_PATH)LX_Text.o \
$(OBJ_TTF_PATH)LX_TrueTypeFont.o $(OBJ_VERSION_PATH)LX_Version.o \
$(OBJ_UTILS_PATH)utf8_string.o $(OBJ_UTILS_PATH)utf8_iterator.o

# Libraries
LUNATIX_LIB_DIR=./lib/linux/
LUNATIX_STATIC_LIB=$(LUNATIX_LIB_DIR)libLunatix.a
LUNATIX_SHARED_LIB=$(LUNATIX_LIB_DIR)libLunatix.so

# Warning flags
WFLAGS=-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic \
-Wno-documentation -Wno-implicit-fallthrough -Wno-padded

# Select flags according to the compilation mode
ifeq ($(DEBUG),yes)

	# Debug mode
	CFLAGS=-fPIC $(WFLAGS) -std=c++11 -g
	OPTIMIZE=
	OPT_SIZE=

else

	# Release mode
	CFLAGS=-fPIC -w -std=c++11 -g
	OPTIMIZE=-O3
	OPT_SIZE=-s

endif


# Linking flags
LUA_FLAGS=$(LUNATIX_LIB_DIR)liblua5.1-c++.so.0
LFLAGS=`pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf`

DOXY_FILE=dox

########################
#                      #
# Generate the library #
#                      #
########################

library : $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB) lua-script

$(LUNATIX_STATIC_LIB) : $(OBJ_FILES)
	@echo "Generating the static library -> "$@
	@mkdir -p $(LUNATIX_BUILD_DIR)
	@ar rcs $@ $(OBJ_FILES)

$(LUNATIX_SHARED_LIB) : $(OBJ_FILES)
	@echo "Generating the shared library -> "$@
	@mkdir -p $(LUNATIX_BUILD_DIR)
	@$(CC) -shared -o $@ $(OBJ_FILES) $(LFLAGS)


lua-script : $(COMPILED_SCRIPT)

$(COMPILED_SCRIPT) : $(SCRIPT_FILE)
	@echo "Compilation of the Lua script : "$<" -> "$@
	@$(LUAC) -o $@ $<


##########
#        #
#  Demo  #
#        #
##########

$(LUNATIX_EXE) : $(MAIN_OBJ_FILE) $(OBJ_FILES) $(COMPILED_SCRIPT)
ifeq ($(DEBUG),yes)
	@echo "Debug mode"
else
	@echo "Release mode"
endif
	@echo $@" - Linking "
	@$(CC) -o $@ $(MAIN_OBJ_FILE) $(OBJ_FILES) $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) \
	$(LFLAGS) $(LUA_FLAGS) && echo $(LUNATIX_EXE)" - Success" \
	|| echo $(LUNATIX_EXE)" - Failure"


#
# Main file
#

main.o : $(OBJ_MAIN_PATH)main.o

$(OBJ_MAIN_PATH)main.o : $(MAIN_PATH)main.cpp \
$(LUNATIX_I_PATH)Lunatix_engine.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_MAIN_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Device
#

LX_Device.o : $(OBJ_DEVICE_PATH)LX_Device.o

$(OBJ_DEVICE_PATH)LX_Device.o : $(DEVICE_PATH)LX_Device.cpp \
$(LUNATIX_I_PATH)LX_Device.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_DEVICE_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Gamepad.o : $(OBJ_DEVICE_PATH)LX_Gamepad.o

$(OBJ_DEVICE_PATH)LX_Gamepad.o : $(DEVICE_PATH)LX_Gamepad.cpp \
$(LUNATIX_I_PATH)LX_Gamepad.hpp $(LUNATIX_I_PATH)LX_Haptic.hpp \
$(LUNATIX_I_PATH)LX_Device.hpp
	@mkdir -p $(OBJ_DEVICE_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Haptic.o : $(OBJ_DEVICE_PATH)LX_Haptic.o

$(OBJ_DEVICE_PATH)LX_Haptic.o : $(DEVICE_PATH)LX_Haptic.cpp \
$(LUNATIX_I_PATH)LX_Haptic.hpp $(LUNATIX_I_PATH)LX_Device.hpp
	@mkdir -p $(OBJ_DEVICE_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# FileIO
#

LX_FileIO.o : $(OBJ_FILEIO_PATH)LX_FileIO.o

$(OBJ_FILEIO_PATH)LX_FileIO.o : $(FILEIO_PATH)LX_FileIO.cpp \
$(LUNATIX_I_PATH)LX_FileIO.hpp
	@mkdir -p $(OBJ_FILEIO_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_FileBuffer.o : $(OBJ_FILEIO_PATH)LX_FileBuffer.o

$(OBJ_FILEIO_PATH)LX_FileBuffer.o : $(FILEIO_PATH)LX_FileBuffer.cpp \
$(LUNATIX_I_PATH)LX_FileBuffer.hpp
	@mkdir -p $(OBJ_FILEIO_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Graphics
#

LX_Graphics.o : $(OBJ_GRAPHICS_PATH)LX_Graphics.o

$(OBJ_GRAPHICS_PATH)LX_Graphics.o : $(GRAPHICS_PATH)LX_Graphics.cpp \
$(LUNATIX_I_PATH)LX_Graphics.hpp $(LUNATIX_I_PATH)LX_Window.hpp \
$(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_GRAPHICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Window.o : $(OBJ_GRAPHICS_PATH)LX_Window.o

$(OBJ_GRAPHICS_PATH)LX_Window.o : $(GRAPHICS_PATH)LX_Window.cpp \
$(LUNATIX_I_PATH)LX_Window.hpp $(LUNATIX_I_PATH)LX_Config.hpp \
$(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_GRAPHICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_WindowManager.o : $(OBJ_GRAPHICS_PATH)LX_WindowManager.o

$(OBJ_GRAPHICS_PATH)LX_WindowManager.o : $(GRAPHICS_PATH)LX_WindowManager.cpp \
$(LUNATIX_I_PATH)LX_WindowManager.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_GRAPHICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Library
#

LX_Config.o : $(OBJ_LIBRARY_PATH)LX_Config.o

$(OBJ_LIBRARY_PATH)LX_Config.o : $(LIBRARY_PATH)LX_Config.cpp \
$(LUNATIX_I_PATH)LX_Config.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_LIBRARY_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Library.o : $(OBJ_LIBRARY_PATH)LX_Library.o

$(OBJ_LIBRARY_PATH)LX_Library.o : $(LIBRARY_PATH)LX_Library.cpp \
$(LUNATIX_I_PATH)LX_Library.hpp $(LUNATIX_I_PATH)LX_Config.hpp \
$(LUNATIX_I_PATH)LX_Mixer.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_LIBRARY_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Mixer
#

LX_Sound.o : $(OBJ_MIXER_PATH)LX_Sound.o

$(OBJ_MIXER_PATH)LX_Sound.o : $(MIXER_PATH)LX_Sound.cpp \
$(LUNATIX_I_PATH)LX_Sound.hpp
	@mkdir -p $(OBJ_MIXER_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Chunk.o : $(OBJ_MIXER_PATH)LX_Chunk.o

$(OBJ_MIXER_PATH)LX_Chunk.o : $(MIXER_PATH)LX_Chunk.cpp \
$(LUNATIX_I_PATH)LX_Chunk.hpp $(LUNATIX_I_PATH)LX_Sound.hpp \
$(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_MIXER_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Music.o : $(OBJ_MIXER_PATH)LX_Music.o

$(OBJ_MIXER_PATH)LX_Music.o : $(MIXER_PATH)LX_Music.cpp \
$(LUNATIX_I_PATH)LX_Music.hpp $(LUNATIX_I_PATH)LX_Sound.hpp \
$(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_MIXER_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Mixer.o : $(OBJ_MIXER_PATH)LX_Mixer.o

$(OBJ_MIXER_PATH)LX_Mixer.o : $(MIXER_PATH)LX_Mixer.cpp \
$(LUNATIX_I_PATH)LX_Mixer.hpp $(LUNATIX_I_PATH)LX_Sound.hpp \
$(LUNATIX_I_PATH)LX_Music.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_MIXER_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# MSGBox
#

LX_MessageBox.o : $(OBJ_MSG_PATH)LX_MessageBox.o

$(OBJ_MSG_PATH)LX_MessageBox.o : $(MSG_PATH)LX_MessageBox.cpp \
$(LUNATIX_I_PATH)LX_MessageBox.hpp
	@mkdir -p $(OBJ_MSG_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# ParticleSystem
#

LX_Particle.o : $(OBJ_PARTICLE_PATH)LX_Particle.o

$(OBJ_PARTICLE_PATH)LX_Particle.o : $(PARTICLE_PATH)LX_Particle.cpp \
$(LUNATIX_I_PATH)LX_Particle.hpp
	@mkdir -p $(OBJ_PARTICLE_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_ParticleSystem.o : $(OBJ_PARTICLE_PATH)LX_ParticleSystem.o

$(OBJ_PARTICLE_PATH)LX_ParticleSystem.o : $(PARTICLE_PATH)LX_ParticleSystem.cpp \
$(LUNATIX_I_PATH)LX_ParticleSystem.hpp
	@mkdir -p $(OBJ_PARTICLE_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Physics
#

LX_Physics.o : $(OBJ_PHYSICS_PATH)LX_Physics.o

$(OBJ_PHYSICS_PATH)LX_Physics.o : $(PHYSICS_PATH)LX_Physics.cpp \
$(LUNATIX_I_PATH)LX_Physics.hpp $(LUNATIX_I_PATH)LX_Hitbox.hpp \
$(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_PHYSICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Polygon.o : $(OBJ_PHYSICS_PATH)LX_Polygon.o

$(OBJ_PHYSICS_PATH)LX_Polygon.o : $(PHYSICS_PATH)LX_Polygon.cpp \
$(LUNATIX_I_PATH)LX_Polygon.hpp $(LUNATIX_I_PATH)LX_Vector2D.hpp
	@mkdir -p $(OBJ_PHYSICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Vector2D.o : $(OBJ_PHYSICS_PATH)LX_Vector2D.o

$(OBJ_PHYSICS_PATH)LX_Vector2D.o : $(PHYSICS_PATH)LX_Vector2D.cpp \
$(LUNATIX_I_PATH)LX_Vector2D.hpp
	@mkdir -p $(OBJ_PHYSICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Hitbox.o : $(OBJ_PHYSICS_PATH)LX_Hitbox.o

$(OBJ_PHYSICS_PATH)LX_Hitbox.o : $(PHYSICS_PATH)LX_Hitbox.cpp \
$(LUNATIX_I_PATH)LX_Hitbox.hpp
	@mkdir -p $(OBJ_PHYSICS_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Random
#

LX_Random.o : $(OBJ_RANDOM_PATH)LX_Random.o

$(OBJ_RANDOM_PATH)LX_Random.o : $(RANDOM_PATH)LX_Random.cpp \
$(LUNATIX_I_PATH)LX_Random.hpp
	@mkdir -p $(OBJ_RANDOM_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# System
#

LX_SystemInfo.o : $(OBJ_SYSTEM_PATH)LX_SystemInfo.o

$(OBJ_SYSTEM_PATH)LX_SystemInfo.o : $(SYSTEM_PATH)LX_SystemInfo.cpp \
$(LUNATIX_I_PATH)LX_SystemInfo.hpp
	@mkdir -p $(OBJ_SYSTEM_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


LX_Log.o : $(OBJ_SYSTEM_PATH)LX_Log.o

$(OBJ_SYSTEM_PATH)LX_Log.o : $(SYSTEM_PATH)LX_Log.cpp \
$(LUNATIX_I_PATH)LX_Log.hpp
	@mkdir -p $(OBJ_SYSTEM_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Text
#

LX_Text.o : $(OBJ_TEXT_PATH)LX_Text.o

$(OBJ_TEXT_PATH)LX_Text.o : $(TEXT_PATH)LX_Text.cpp \
$(LUNATIX_I_PATH)LX_Text.hpp $(LUNATIX_I_PATH)LX_Log.hpp \
$(UTILS_I_PATH)utf8_string.hpp
	@mkdir -p $(OBJ_TEXT_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# True Type Font
#

LX_TrueTypeFont.o : $(OBJ_TTF_PATH)LX_TrueTypeFont.o

$(OBJ_TTF_PATH)LX_TrueTypeFont.o : $(TTF_PATH)LX_TrueTypeFont.cpp \
$(LUNATIX_I_PATH)LX_TrueTypeFont.hpp $(LUNATIX_I_PATH)LX_Graphics.hpp \
$(LUNATIX_I_PATH)LX_Config.hpp $(LUNATIX_I_PATH)LX_Error.hpp
	@mkdir -p $(OBJ_TTF_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Version
#

LX_Version.o : $(OBJ_VERSION_PATH)LX_Version.o

$(OBJ_VERSION_PATH)LX_Version.o : $(VERSION_PATH)LX_Version.cpp \
$(LUNATIX_I_PATH)LX_Version.hpp
	@mkdir -p $(OBJ_VERSION_PATH)
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


#
# Utilities
#

utf8_string.o : $(OBJ_UTILS_PATH)utf8_string.o

$(OBJ_UTILS_PATH)utf8_string.o : $(UTILS_PATH)utf8_string.cpp \
$(UTILS_I_PATH)utf8_string.hpp $(UTILS_I_PATH)utf8_iterator.hpp
	@mkdir -p $(OBJ_UTILS_PATH)
	@$(CC) -c $(CFLAGS) -o $@ $< -I $(LIBRARIES_I_DIR)
	@echo $@" - Compiling "$<


utf8_iterator.o : $(OBJ_UTILS_PATH)utf8_iterator.o

$(OBJ_UTILS_PATH)utf8_iterator.o : $(UTILS_PATH)utf8_iterator.cpp \
$(UTILS_I_PATH)utf8_iterator.hpp $(UTILS_I_PATH)utf8_string.hpp
	@echo $<" -> "$@
	@$(CC) -c $(CFLAGS) -o $@ $< -I $(LIBRARIES_I_DIR)
	@echo $<" -> "$@" done."


##########
#        #
#  Test  #
#        #
##########

test : lua-script test-init test-config test-device test-physics \
test-window test-system test-ttf test-particle test-file
	@echo "INFO - Test launch"
ifeq ($(DEBUG),yes)
	@./test/test.sh
endif
	@make clean -j 1
	@echo "INFO - Test finished"

test-init : $(OBJ_FILES) test-init.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-init.o : $(TEST_PATH)test-init.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-config : $(OBJ_FILES) test-config.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-config.o : $(TEST_PATH)test-config.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-device : $(OBJ_FILES) test-device.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-device.o : $(TEST_PATH)test-device.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-physics : $(OBJ_FILES) test-physics.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-physics.o : $(TEST_PATH)test-physics.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-window : $(OBJ_FILES) test-window.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-window.o : $(TEST_PATH)test-window.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-system : $(OBJ_FILES) test-system.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-system.o : $(TEST_PATH)test-system.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-ttf : $(OBJ_FILES) test-ttf.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-ttf.o : $(TEST_PATH)test-ttf.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-particle : $(OBJ_FILES) test-particle.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-particle.o : $(TEST_PATH)test-particle.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-file : $(OBJ_FILES) test-file.o
	@make lua-script
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-file.o : $(TEST_PATH)test-file.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


test-ime : $(OBJ_FILES) test-ime.o
	@make lua-script
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-ime.o : $(TEST_PATH)test-ime.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS)


######################################
#                                    #
# Generate the doxygen documentation #
#                                    #
######################################

doxy : $(DOXY_FILE)
	@echo "Generating the doxygen file from "$<
	@doxygen $<


#########################
#                       #
# Clean generated files #
#                       #
#########################

clean :
	@echo "Delete object files"
	@rm -rf $(LUNATIX_BUILD_ROOT) test-*

cleandoc:
	@echo "Delete the doxygen documentation"
	@rm -rf html/

cleanlib:
	@echo "Delete libraries"
	@rm -f $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)

clear : cleandoc cleanlib clean
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE) $(COMPILED_SCRIPT)
