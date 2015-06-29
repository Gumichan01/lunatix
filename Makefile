
#
#	Copyright (C) 2014-2015 Luxon Jean-Pierre
#	gumichan01.olympe.in
#
#	LunatiX-engine is a SDL-based game engine.
#	It can be used for open-source or commercial games thanks to the zlib/libpng license.
#
#	Luxon Jean-Pierre (Gumichan01)
#	luxon.jean.pierre@gmail.com
#

# Makefile - Lunatix Engine v0.3


# You can modify the value of DEBUG
# If you want to use debug or release mode
DEBUG=no


CC=g++
MAIN_OBJ=main.o
OBJS=LX_Chunk.o LX_Config.o LX_Graphics.o LX_Library.o LX_WindowManager.o \
LX_Mixer.o LX_Music.o LX_Physics.o LX_TrueTypeFont.o LX_Window.o LX_Device.o \
LX_Vector2D.o LX_Polygon.o LX_SystemInfo.o LX_Random.o LX_Particle.o \
LX_ParticleSystem.o LX_FileIO.o LX_FileBuffer.o LX_MessageBox.o LX_Version.o \
LX_Gamepad.o


LUAC=luac5.1
SCRIPT_FILE=script/LX_config.lua
COMPILED_SCRIPT=$(SCRIPT_FILE)c

# Path to main file directory
MAIN_PATH=./src/

# Path to the test files
TEST_PATH=./test/

# Executable file
LUNATIX_EXE=lunatix-engine

# Path to Lunatix engine directory and include directory
LUNATIX_PATH=./src/engine/
LUNATIX_INCLUDE_LIB=./include/

# Libraries
LUNATIX_STATIC_LIB=libLunatix.a
LUNATIX_SHARED_LIB=libLunatix.so

# Select flags according to the compilation mode
ifeq ($(DEBUG),yes)

	# Debug mode
	CFLAGS=-Wall -std=c++0x -g
	OPTIMIZE=
	OPT_SIZE=

else

	# Release mode
	CFLAGS=-fPIC -Wall -std=c++0x
	OPTIMIZE=-O3
	OPT_SIZE=-s

endif


# Linking flags
LUA_FLAGS=./lib/linux/liblua5.1-c++.so.0
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


# The default rule 
library : $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)

$(LUNATIX_STATIC_LIB) : $(OBJS)
	@echo "Generating the static library"
	@ar rcs $@ $(OBJS)

$(LUNATIX_SHARED_LIB) : $(OBJS)
	@echo "Generating the shared library"
	@gcc -shared -o $@ $(OBJS) $(LFLAGS)


$(COMPILED_SCRIPT) : $(SCRIPT_FILE)
	@echo "Compilation of the Lua script : "$<" -> "$@
	@$(LUAC) -o $@ $<


# Demo
$(LUNATIX_EXE) : $(MAIN_OBJ) $(OBJS) $(COMPILED_SCRIPT)
ifeq ($(DEBUG),yes)
	@echo "Debug mode"
else
	@echo "Release mode"
endif
	@echo $@" - Linking "
	@$(CC) -o $@ $(MAIN_OBJ) $(OBJS) $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


LX_Config.o : $(LUNATIX_PATH)LX_Config.cpp $(LUNATIX_PATH)LX_Config.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Window.o : $(LUNATIX_PATH)LX_Window.cpp $(LUNATIX_PATH)LX_Window.hpp $(LUNATIX_PATH)LX_Config.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_WindowManager.o : $(LUNATIX_PATH)LX_WindowManager.cpp $(LUNATIX_PATH)LX_WindowManager.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Library.o : $(LUNATIX_PATH)LX_Library.cpp $(LUNATIX_PATH)LX_Library.hpp $(LUNATIX_PATH)LX_Config.hpp $(LUNATIX_PATH)LX_Mixer.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Graphics.o : $(LUNATIX_PATH)LX_Graphics.cpp $(LUNATIX_PATH)LX_Graphics.hpp $(LUNATIX_PATH)LX_Window.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_TrueTypeFont.o : $(LUNATIX_PATH)LX_TrueTypeFont.cpp $(LUNATIX_PATH)LX_TrueTypeFont.hpp $(LUNATIX_PATH)LX_Graphics.hpp $(LUNATIX_PATH)LX_Config.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Physics.o : $(LUNATIX_PATH)LX_Physics.cpp $(LUNATIX_PATH)LX_Physics.hpp $(LUNATIX_PATH)LX_Hitbox.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Chunk.o : $(LUNATIX_PATH)LX_Chunk.cpp $(LUNATIX_PATH)LX_Chunk.hpp $(LUNATIX_PATH)LX_Sound.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Music.o : $(LUNATIX_PATH)LX_Music.cpp $(LUNATIX_PATH)LX_Sound.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Mixer.o : $(LUNATIX_PATH)LX_Mixer.cpp $(LUNATIX_PATH)LX_Mixer.hpp $(LUNATIX_PATH)LX_Sound.hpp $(LUNATIX_PATH)LX_Music.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


main.o : $(MAIN_PATH)main.cpp $(LUNATIX_PATH)Lunatix_engine.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Device.o : $(LUNATIX_PATH)LX_Device.cpp $(LUNATIX_PATH)LX_Device.hpp $(LUNATIX_PATH)LX_Error.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Polygon.o : $(LUNATIX_PATH)LX_Polygon.cpp $(LUNATIX_PATH)LX_Polygon.hpp $(LUNATIX_PATH)LX_Vector2D.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Vector2D.o : $(LUNATIX_PATH)LX_Vector2D.cpp $(LUNATIX_PATH)LX_Vector2D.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_SystemInfo.o : $(LUNATIX_PATH)LX_SystemInfo.cpp $(LUNATIX_PATH)LX_SystemInfo.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Random.o : $(LUNATIX_PATH)LX_Random.cpp $(LUNATIX_PATH)LX_Random.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Particle.o : $(LUNATIX_PATH)LX_Particle.cpp $(LUNATIX_PATH)LX_Particle.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_ParticleSystem.o : $(LUNATIX_PATH)LX_ParticleSystem.cpp $(LUNATIX_PATH)LX_ParticleSystem.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_FileIO.o : $(LUNATIX_PATH)LX_FileIO.cpp $(LUNATIX_PATH)LX_FileIO.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_FileBuffer.o : $(LUNATIX_PATH)LX_FileBuffer.cpp $(LUNATIX_PATH)LX_FileBuffer.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_MessageBox.o : $(LUNATIX_PATH)LX_MessageBox.cpp $(LUNATIX_PATH)LX_MessageBox.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Version.o : $(LUNATIX_PATH)LX_Version.cpp $(LUNATIX_PATH)LX_Version.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


LX_Gamepad.o : $(LUNATIX_PATH)LX_Gamepad.cpp $(LUNATIX_PATH)LX_Gamepad.hpp $(LUNATIX_PATH)LX_Device.hpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)



# Test of different modules
test : $(COMPILED_SCRIPT) test-init test-config test-device test-physics test-window test-system test-ttf test-particle test-file


test-init : $(OBJS) test-init.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-init.o : $(TEST_PATH)test-init.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-config : $(OBJS) test-config.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-config.o : $(TEST_PATH)test-config.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-device : $(OBJS) test-device.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-device.o : $(TEST_PATH)test-device.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-physics : $(OBJS) test-physics.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-physics.o : $(TEST_PATH)test-physics.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-window : $(OBJS) test-window.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-window.o : $(TEST_PATH)test-window.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-system : $(OBJS) test-system.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-system.o : $(TEST_PATH)test-system.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-ttf : $(OBJS) test-ttf.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-ttf.o : $(TEST_PATH)test-ttf.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -std=c++0x -g


test-particle : $(OBJS) test-particle.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-particle.o : $(TEST_PATH)test-particle.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)


test-file : $(OBJS) test-file.o LX_FileIO.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS) -lstdc++


test-file.o : $(TEST_PATH)test-file.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)



clean :
	@echo "Delete object files"
	@rm -f *.o

cleanlib:
	@echo "Delete libraries"
	@rm -f $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)

clean-test : clean
	@echo "Delete test object files"
	@rm -f test-* 

cleanall : clean-test cleanlib
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE) $(COMPILED_SCRIPT)

