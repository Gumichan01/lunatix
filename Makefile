
#
#	Copyright (C) 2014-2015 Luxon Jean-Pierre
#	gumichan01.olympe.in
#
#	The LunatiX-engine is an SDL2-based game engine.
#	It can be used for open-source or commercial games thanks to the zlib/libpng license.
#
#	Luxon Jean-Pierre (Gumichan01)
#	luxon.jean.pierre@gmail.com
#

# Makefile - Lunatix Engine


.PHONY: doxy clean 


#
# Debug symbol
#

# You can modify the value of DEBUG
# If you want to use the debug or release mode
DEBUG=yes


#
# Variables
#

CC=g++
MAIN_OBJ=main.o
OBJS=LX_Device.o LX_Gamepad.o LX_Haptic.o \
LX_FileIO.o LX_FileBuffer.o \
LX_Graphics.o LX_Window.o LX_WindowManager.o \
LX_Config.o LX_Library.o \
LX_Chunk.o LX_Music.o LX_Mixer.o \
LX_MessageBox.o \
LX_Particle.o LX_ParticleSystem.o \
LX_Physics.o LX_Polygon.o LX_Vector2D.o \
LX_Random.o \
LX_SystemInfo.o \
LX_TrueTypeFont.o \
LX_Version.o

LUAC=luac5.1
SCRIPT_FILE=script/LX_config.lua
COMPILED_SCRIPT=$(SCRIPT_FILE)c

# Path to the main file directory
MAIN_PATH=./src/

# Path to the test files
TEST_PATH=./test/


# Executable file
LUNATIX_EXE=lunatix-engine

# Path to the Lunatix engine directory and include directory
LUNATIX_PATH=./src/LunatiX/
LIBRARIES_INCLUDE_DIR=./include/
LUNATIX_INCLUDE_PATH=$(LIBRARIES_INCLUDE_DIR)LunatiX/

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
TTF_PATH=$(LUNATIX_PATH)TrueTypeFont/
VERSION_PATH=$(LUNATIX_PATH)Version/


# Libraries
LUNATIX_BUILD_DIR=./build/
LUNATIX_STATIC_LIB=$(LUNATIX_BUILD_DIR)libLunatix.a
LUNATIX_SHARED_LIB=$(LUNATIX_BUILD_DIR)libLunatix.so

# Select flags according to the compilation mode
ifeq ($(DEBUG),yes)

	# Debug mode
	CFLAGS=-fPIC -Wall -std=c++0x -g
	OPTIMIZE=
	OPT_SIZE=

else

	# Release mode
	CFLAGS=-fPIC -w -std=c++0x
	OPTIMIZE=-O3
	OPT_SIZE=-s

endif


# Linking flags
LUA_FLAGS=./lib/linux/liblua5.1-c++.so.0
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


DOXY_FILE=dox

########################
#                      #
# Generate the library #
#                      #
########################

library : $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)

$(LUNATIX_STATIC_LIB) : $(OBJS)
	@echo "Generating the static library -> "$@
	@mkdir -p $(LUNATIX_BUILD_DIR)
	@ar rcs $@ $(OBJS)

$(LUNATIX_SHARED_LIB) : $(OBJS)
	@echo "Generating the shared library -> "$@
	@mkdir -p $(LUNATIX_BUILD_DIR)
	@gcc -shared -o $@ $(OBJS) $(LFLAGS)


$(COMPILED_SCRIPT) : $(SCRIPT_FILE)
	@echo "Compilation of the Lua script : "$<" -> "$@
	@$(LUAC) -o $@ $<



##########
#        #
#  Demo  #
#        #
##########

$(LUNATIX_EXE) : $(MAIN_OBJ) $(OBJS) $(COMPILED_SCRIPT)
ifeq ($(DEBUG),yes)
	@echo "Debug mode"
else
	@echo "Release mode"
endif
	@echo $@" - Linking "
	@$(CC) -o $@ $(MAIN_OBJ) $(OBJS) $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


#
# Main file
#

main.o : $(MAIN_PATH)main.cpp $(LUNATIX_INCLUDE_PATH)Lunatix_engine.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Device
#

LX_Device.o : $(DEVICE_PATH)LX_Device.cpp $(LUNATIX_INCLUDE_PATH)LX_Device.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Gamepad.o : $(DEVICE_PATH)LX_Gamepad.cpp $(LUNATIX_INCLUDE_PATH)LX_Gamepad.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Haptic.hpp $(LUNATIX_INCLUDE_PATH)LX_Device.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Haptic.o : $(DEVICE_PATH)LX_Haptic.cpp $(LUNATIX_INCLUDE_PATH)LX_Haptic.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Device.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# FileIO
#

LX_FileIO.o : $(FILEIO_PATH)LX_FileIO.cpp $(LUNATIX_INCLUDE_PATH)LX_FileIO.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_FileBuffer.o : $(FILEIO_PATH)LX_FileBuffer.cpp \
$(LUNATIX_INCLUDE_PATH)LX_FileBuffer.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Graphics
#


LX_Graphics.o : $(GRAPHICS_PATH)LX_Graphics.cpp $(LUNATIX_INCLUDE_PATH)LX_Graphics.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Window.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Window.o : $(GRAPHICS_PATH)LX_Window.cpp $(LUNATIX_INCLUDE_PATH)LX_Window.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Config.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_WindowManager.o : $(GRAPHICS_PATH)LX_WindowManager.cpp  \
$(LUNATIX_INCLUDE_PATH)LX_WindowManager.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Library
#

LX_Config.o : $(LIBRARY_PATH)LX_Config.cpp $(LUNATIX_INCLUDE_PATH)LX_Config.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Library.o : $(LIBRARY_PATH)LX_Library.cpp $(LUNATIX_INCLUDE_PATH)LX_Library.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Config.hpp $(LUNATIX_INCLUDE_PATH)LX_Mixer.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Mixer
#

LX_Chunk.o : $(MIXER_PATH)LX_Chunk.cpp $(LUNATIX_INCLUDE_PATH)LX_Chunk.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Sound.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Music.o : $(MIXER_PATH)LX_Music.cpp $(LUNATIX_INCLUDE_PATH)LX_Music.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Sound.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Mixer.o : $(MIXER_PATH)LX_Mixer.cpp $(LUNATIX_INCLUDE_PATH)LX_Mixer.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Sound.hpp $(LUNATIX_INCLUDE_PATH)LX_Music.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# MSGBox
#

LX_MessageBox.o : $(MSG_PATH)LX_MessageBox.cpp \
$(LUNATIX_INCLUDE_PATH)LX_MessageBox.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# ParticleSystem
#

LX_Particle.o : $(PARTICLE_PATH)LX_Particle.cpp $(LUNATIX_INCLUDE_PATH)LX_Particle.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_ParticleSystem.o : $(PARTICLE_PATH)LX_ParticleSystem.cpp \
$(LUNATIX_INCLUDE_PATH)LX_ParticleSystem.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Physics
#

LX_Physics.o : $(PHYSICS_PATH)LX_Physics.cpp $(LUNATIX_INCLUDE_PATH)LX_Physics.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Hitbox.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Polygon.o : $(PHYSICS_PATH)LX_Polygon.cpp $(LUNATIX_INCLUDE_PATH)LX_Polygon.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Vector2D.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


LX_Vector2D.o : $(PHYSICS_PATH)LX_Vector2D.cpp $(LUNATIX_INCLUDE_PATH)LX_Vector2D.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Random
#

LX_Random.o : $(RANDOM_PATH)LX_Random.cpp $(LUNATIX_INCLUDE_PATH)LX_Random.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# System
#

LX_SystemInfo.o : $(SYSTEM_PATH)LX_SystemInfo.cpp \
$(LUNATIX_INCLUDE_PATH)LX_SystemInfo.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# True Type Font
#

LX_TrueTypeFont.o : $(TTF_PATH)LX_TrueTypeFont.cpp \
$(LUNATIX_INCLUDE_PATH)LX_TrueTypeFont.hpp $(LUNATIX_INCLUDE_PATH)LX_Graphics.hpp \
$(LUNATIX_INCLUDE_PATH)LX_Config.hpp $(LUNATIX_INCLUDE_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)



#
# Version
#

LX_Version.o : $(VERSION_PATH)LX_Version.cpp $(LUNATIX_INCLUDE_PATH)LX_Version.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)





#############################
#                           #
# Test of different modules #
#                           #
#############################

test : $(COMPILED_SCRIPT) test-init test-config test-device test-physics \
test-window test-system test-ttf test-particle test-file


test-init : $(OBJS) test-init.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-init.o : $(TEST_PATH)test-init.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-config : $(OBJS) test-config.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-config.o : $(TEST_PATH)test-config.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-device : $(OBJS) test-device.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-device.o : $(TEST_PATH)test-device.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-physics : $(OBJS) test-physics.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-physics.o : $(TEST_PATH)test-physics.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-window : $(OBJS) test-window.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-window.o : $(TEST_PATH)test-window.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-system : $(OBJS) test-system.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-system.o : $(TEST_PATH)test-system.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-ttf : $(OBJS) test-ttf.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-ttf.o : $(TEST_PATH)test-ttf.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) -std=c++0x -g


test-particle : $(OBJS) test-particle.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-particle.o : $(TEST_PATH)test-particle.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)


test-file : $(OBJS) test-file.o LX_FileIO.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS) -lstdc++


test-file.o : $(TEST_PATH)test-file.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LIBRARIES_INCLUDE_DIR) $(CFLAGS)

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
	@rm -f *.o

cleandoc: 
	@echo "Delete the doxygen documentation"
	@rm -rf html/

cleanlib:
	@echo "Delete libraries"
	@rm -rf $(LUNATIX_BUILD_DIR)

clean-test : clean
	@echo "Delete test object files"
	@rm -f test-* 

cleanall : clean-test cleanlib cleandoc
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE) $(COMPILED_SCRIPT)


