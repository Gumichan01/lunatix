
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
DEBUG=yes


CC=g++
MAIN_OBJ=main.o
OBJS=LX_Chunk.o LX_Config.o LX_Graphics.o LX_Library.o LX_WindowManager.o \
LX_Mixer.o LX_Music.o LX_Physics.o LX_TrueTypeFont.o LX_Window.o LX_Device.o


LUAC=luac5.1
SCRIPT_FILE=script/LX_config.lua
COMPILED_SCRIPT=$(SCRIPT_FILE)c

# Path to main file directory
MAIN_PATH=./src/

# Path to the test files
TEST_PATH=./test/

# executable file
LUNATIX_EXE=lunatix-engine

# Path to Lunatix engine directory and include directory
LUNATIX_PATH=./src/engine/
LUNATIX_INCLUDE_LIB=./include/


# Select flags according to the compilation mode
ifeq ($(DEBUG),yes)

	# Debug mode
	CFLAGS=-std=c++0x -g
	OPTIMIZE=
	OPT_SIZE=

else

	# Release mode
	CFLAGS=-std=c++0x
	OPTIMIZE=-O3
	OPT_SIZE=-s

endif


# Linking flags
LUA_FLAGS=./lib/linux/liblua5.1-c++.so.0
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


all : $(LUNATIX_EXE) $(COMPILED_SCRIPT)

rebuild : clean-target all

$(COMPILED_SCRIPT) : $(SCRIPT_FILE)
	@echo "Compilation of the Lua script : "$<" -> "$@
	@$(LUAC) -o $@ $<



# Demo
$(LUNATIX_EXE) : $(MAIN_OBJ) $(OBJS)
ifeq ($(DEBUG),yes)
	@echo "Debug mode"
else
	@echo "Release mode"
endif
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


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



# Test of different modules
test : $(COMPILED_SCRIPT) test-init test-config test-device test-physics


test-init : $(OBJS) test-init.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-init.o : $(TEST_PATH)test-init.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -g


test-config : $(OBJS) test-config.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-config.o : $(TEST_PATH)test-config.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -g


test-device : $(OBJS) test-device.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-device.o : $(TEST_PATH)test-device.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -g


test-physics : $(OBJS) test-physics.o
	@echo $@" - Linking "
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) $(LUA_FLAGS)


test-physics.o : $(TEST_PATH)test-physics.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) -g


clean :
	@echo "Delete object files"
	@rm -f *.o

clean-test :
	@echo "Delete test object files"
	@rm -f test-* 

clean-target : clean
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE) test-* $(COMPILED_SCRIPT)

