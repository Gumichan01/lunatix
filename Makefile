
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

# Makefile - Lunatix Engine v0.2


# You can modify the value of DEBUG
# If you want to use debug or release mode
DEBUG=no


CC=g++
MAIN_OBJ=main.o
OBJS=LX_Chunk.o LX_Config.o LX_Graphics.o LX_Library.o LX_WindowManager.o \
LX_Mixer.o LX_Music.o LX_Physics.o LX_TrueTypeFont.o LX_Window.o LX_Device.o

LUAC=luac5.1
SCRIPT_FILE=script/LX_config.lua
COMPILED_SCRIPT=$(SCRIPT_FILE)c

# Path to main file directory
MAIN_PATH=./src/


# Test file
LUNATIX_EXE=test_lunatix-engine

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
	@echo "Compile the Lua script : "$<" -> "$@
	@$(LUAC) -o $@ $<


# Demo
$(LUNATIX_EXE) : $(MAIN_OBJ) $(OBJS)
ifeq ($(DEBUG),yes)
	@echo "Debug mode"
else
	@echo "Release mode"
endif
	@echo $@"- Linking "
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


LX_Polygon.o : $(LUNATIX_PATH)LX_Polygon.cpp $(LUNATIX_PATH)LX_Polygon.hpp
        @echo $@" - Compiling "$<
        @$(CC) -c -o $@ $< -I $(LUNATIX_INCLUDE_LIB) $(CFLAGS)

	

clean : 
	@echo "Delete object file "
	@rm -f *.o

clean-target : clean
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE) $(COMPILED_SCRIPT)

