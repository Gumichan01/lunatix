
#
#   Copyright (C) 2016 Luxon Jean-Pierre
#   gumichan01.cpplympe.in
#
#   LunatiX is a free, SDL2-based library.
#   It can be used for open-source or commercial games thanks to the zlib/libpng license.
#
#   Luxon Jean-Pierre (Gumichan01)
#   luxon.jean.pierre@gmail.com
#

# Makefile - LunatiX

# You can modify the value of DEBUG
# If you want to use the debug or release mode
DEBUG=yes


#
# Variables
#

CC=clang++

# Path to the test files
TEST_PATH=./test/

# Executable file
LUNATIX_EXE=lunatix-demo

# Path to directories
SRC_PATH=./src/
LUNATIX_PATH=./src/LunatiX/
LIBRARIES_I_DIR=./include/
LUNATIX_I_PATH=$(LIBRARIES_I_DIR)LunatiX/
UTILS_I_PATH=$(LUNATIX_I_PATH)utils/
TINYTHREAD_I_PATH=$(UTILS_I_PATH)tinythread/
LIBTAGSPP_I_PATH=$(UTILS_I_PATH)libtagspp/
SDL2_I_PATH=`pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf`

# Path to the different modules
SRC_MAIN_PATH=./src/
SRC_DEVICE_PATH=$(LUNATIX_PATH)Device/
SRC_FILEIO_PATH=$(LUNATIX_PATH)FileIO/
SRC_GRAPHICS_PATH=$(LUNATIX_PATH)Graphics/
SRC_INPUT_PATH=$(LUNATIX_PATH)Input/
SRC_LIBRARY_PATH=$(LUNATIX_PATH)Library/
SRC_MIXER_PATH=$(LUNATIX_PATH)Mixer/
SRC_MSG_PATH=$(LUNATIX_PATH)MSGBox/
SRC_MULTITHREAD_PATH=$(LUNATIX_PATH)Multithreading/
SRC_PARTICLE_PATH=$(LUNATIX_PATH)ParticleEngine/
SRC_PHYSICS_PATH=$(LUNATIX_PATH)Physics/
SRC_RANDOM_PATH=$(LUNATIX_PATH)Random/
SRC_SYSTEM_PATH=$(LUNATIX_PATH)System/
SRC_TEXT_PATH=$(LUNATIX_PATH)Text/
SRC_TTF_PATH=$(LUNATIX_PATH)TrueTypeFont/
SRC_VERSION_PATH=$(LUNATIX_PATH)Version/
SRC_UTILS_PATH=$(LUNATIX_PATH)Utilities/
SRC_TINYTHREAD_PATH=$(SRC_UTILS_PATH)tinythread/
SRC_LIBTAGSPP_PATH=$(SRC_UTILS_PATH)libtagspp/

# Path to the different sources files
MAIN_FILE=$(SRC_MAIN_PATH)main.cpp
SRC_FILES=$(SRC_DEVICE_PATH)LX_Device.cpp $(SRC_DEVICE_PATH)LX_Gamepad.cpp \
$(SRC_DEVICE_PATH)LX_Haptic.cpp $(SRC_DEVICE_PATH)LX_Mouse.cpp \
$(SRC_FILEIO_PATH)LX_FileIO.cpp $(SRC_FILEIO_PATH)LX_FileBuffer.cpp \
$(SRC_GRAPHICS_PATH)LX_OpenGL.cpp $(SRC_GRAPHICS_PATH)LX_Window.cpp \
$(SRC_GRAPHICS_PATH)LX_WindowManager.cpp $(SRC_GRAPHICS_PATH)LX_Image.cpp \
$(SRC_INPUT_PATH)LX_Event.cpp \
$(SRC_LIBRARY_PATH)LX_Config.cpp $(SRC_LIBRARY_PATH)LX_Library.cpp \
$(SRC_MIXER_PATH)LX_Sound.cpp $(SRC_MIXER_PATH)LX_Chunk.cpp \
$(SRC_MIXER_PATH)LX_Music.cpp $(SRC_MIXER_PATH)LX_Mixer.cpp \
$(SRC_MSG_PATH)LX_MessageBox.cpp \
$(SRC_MULTITHREAD_PATH)LX_Thread.cpp $(SRC_MULTITHREAD_PATH)LX_Sync.cpp \
$(SRC_PARTICLE_PATH)LX_Particle.cpp $(SRC_PARTICLE_PATH)LX_ParticleSystem.cpp \
$(SRC_PHYSICS_PATH)LX_Hitbox.cpp $(SRC_PHYSICS_PATH)LX_Physics.cpp \
$(SRC_PHYSICS_PATH)LX_Polygon.cpp $(SRC_PHYSICS_PATH)LX_Vector2D.cpp \
$(SRC_RANDOM_PATH)LX_Random.cpp $(SRC_SYSTEM_PATH)LX_SystemInfo.cpp \
$(SRC_SYSTEM_PATH)LX_Log.cpp $(SRC_SYSTEM_PATH)LX_FileSystem.cpp \
$(SRC_TEXT_PATH)LX_Text.cpp $(SRC_TTF_PATH)LX_TrueTypeFont.cpp \
$(SRC_VERSION_PATH)LX_Version.cpp \
$(SRC_UTILS_PATH)utf8_string.cpp $(SRC_UTILS_PATH)utf8_iterator.cpp \
$(SRC_TINYTHREAD_PATH)tinythread.cpp $(SRC_LIBTAGSPP_PATH)8859.cpp \
$(SRC_LIBTAGSPP_PATH)flac.cpp $(SRC_LIBTAGSPP_PATH)id3genres.cpp \
$(SRC_LIBTAGSPP_PATH)id3v1.cpp $(SRC_LIBTAGSPP_PATH)id3v2.cpp \
$(SRC_LIBTAGSPP_PATH)m4a.cpp $(SRC_LIBTAGSPP_PATH)tags.cpp \
$(SRC_LIBTAGSPP_PATH)utf16.cpp $(SRC_LIBTAGSPP_PATH)vorbis.cpp \
$(SRC_LIBTAGSPP_PATH)libtagspp.cpp

# Test files
SRC_TEST_FILES=$(TEST_PATH)test-init.cpp $(TEST_PATH)test-config.cpp \
$(TEST_PATH)test-device.cpp $(TEST_PATH)test-physics.cpp $(TEST_PATH)test-window.cpp \
$(TEST_PATH)test-system.cpp $(TEST_PATH)test-ttf.cpp $(TEST_PATH)test-particle.cpp \
$(TEST_PATH)test-file.cpp $(TEST_PATH)test-ime.cpp $(TEST_PATH)test-audio.cpp \
$(TEST_PATH)test-thread.cpp $(TEST_PATH)test-ime.cpp $(TEST_PATH)test-input.cpp

OBJ_FILES=$(SRC_FILES:.cpp=.o)
MAIN_OBJ=$(MAIN_FILE:.cpp=.o)

# Dependency
DEPENDENCY=Makefile.depend

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
	OPTIMIZE=-O0
	OPT_SIZE=

else

	# Release mode
	CFLAGS=-fPIC -w -std=c++11 -g
	OPTIMIZE=-O3
	OPT_SIZE=-s

endif


# Linking flags
LFLAGS=`pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf gl`

DOXY_FILE=dox

########################
#                      #
# Generate the library #
#                      #
########################

.PHONY: depend test clean cleandoc documentation $(DEPENDENCY)

library: depend $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)

$(LUNATIX_STATIC_LIB): $(OBJ_FILES)
	@echo -n "Generating the static library → "$@"... "
	@ar rcs $@ $(OBJ_FILES)
	@echo "DONE"

$(LUNATIX_SHARED_LIB): $(OBJ_FILES)
	@echo -n "Generating the shared library → "$@"... "
	@$(CC) -shared -o $@ $(OBJ_FILES) $(LFLAGS)
	@echo "DONE"


##########
#        #
#  Demo  #
#        #
##########

$(LUNATIX_EXE): depend $(MAIN_OBJ) $(OBJ_FILES)
ifeq ($(DEBUG),yes)
	@echo "Debug mode"
else
	@echo "Release mode"
endif
	@echo "| Linking → " $@"... "
	@$(CC) -o $@ $(MAIN_OBJ) $(OBJ_FILES) $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS) \
	&& echo "| SUCCESS" || echo "| FAILURE"


# Object files (library)
main.o: $(SRC_MAIN_PATH)main.o
LX_Device.o: $(SRC_DEVICE_PATH)LX_Device.o
LX_Gamepad.o: $(SRC_DEVICE_PATH)LX_Gamepad.o
LX_Haptic.o: $(SRC_DEVICE_PATH)LX_Haptic.o
LX_Mouse.o: $(SRC_DEVICE_PATH)LX_Mouse.o
LX_FileIO.o: $(SRC_FILEIO_PATH)LX_FileIO.o
LX_FileBuffer.o: $(SRC_FILEIO_PATH)LX_FileBuffer.o
LX_OpenGL.o: $(SRC_GRAPHICS_PATH)LX_OpenGL.o
LX_Window.o: $(SRC_GRAPHICS_PATH)LX_Window.o
LX_WindowManager.o: $(SRC_GRAPHICS_PATH)LX_WindowManager.o
LX_Image.o: $(SRC_GRAPHICS_PATH)LX_Image.o
LX_Event.o: $(SRC_LIBRARY_PATH)LX_Event.o
LX_Config.o: $(SRC_LIBRARY_PATH)LX_Config.o
LX_Library.o: $(SRC_LIBRARY_PATH)LX_Library.o
LX_Sound.o: $(SRC_MIXER_PATH)LX_Sound.o
LX_Chunk.o: $(SRC_MIXER_PATH)LX_Chunk.o
LX_Music.o: $(SRC_MIXER_PATH)LX_Music.o
LX_Mixer.o: $(SRC_MIXER_PATH)LX_Mixer.o
LX_MessageBox.o: $(SRC_MSG_PATH)LX_MessageBox.o
LX_Thread.o: $(SRC_MULTITHREAD_PATH)LX_Thread.o
LX_Sync.o: $(SRC_MULTITHREAD_PATH)LX_Sync.o
LX_Particle.o: $(SRC_PARTICLE_PATH)LX_Particle.o
LX_ParticleSystem.o: $(SRC_PARTICLE_PATH)LX_ParticleSystem.o
LX_Physics.o: $(SRC_PHYSICS_PATH)LX_Physics.o
LX_Polygon.o: $(SRC_PHYSICS_PATH)LX_Polygon.o
LX_Hitbox.o: $(SRC_PHYSICS_PATH)LX_Hitbox.o
LX_Random.o: $(SRC_RANDOM_PATH)LX_Random.o
LX_SystemInfo.o: $(SRC_SYSTEM_PATH)LX_SystemInfo.o
LX_FileSystem.o: $(SRC_SYSTEM_PATH)LX_FileSystem.o
LX_Log.o: $(SRC_SYSTEM_PATH)LX_Log.o
LX_Text.o: $(SRC_TEXT_PATH)LX_Text.o
LX_TrueTypeFont.o: $(SRC_TTF_PATH)LX_TrueTypeFont.o
LX_Version.o: $(SRC_VERSION_PATH)LX_Version.o


##########
#        #
#  Test  #
#        #
##########

test: depend test-init test-config test-system test-device test-file test-physics \
test-audio test-window test-ttf test-particle test-ime test-thread


# Test (object files + executable)
test-init: $(TEST_PATH)test-init.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-config: $(TEST_PATH)test-config.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-device: $(TEST_PATH)test-device.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-physics: $(TEST_PATH)test-physics.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-window: $(TEST_PATH)test-window.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-system: $(TEST_PATH)test-system.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-ttf: $(TEST_PATH)test-ttf.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-particle: $(TEST_PATH)test-particle.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-file: $(TEST_PATH)test-file.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-ime: $(TEST_PATH)test-ime.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-audio: $(TEST_PATH)test-audio.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-thread: $(TEST_PATH)test-thread.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

test-input: $(TEST_PATH)test-input.o $(OBJ_FILES)
	@$(CC) -o $@ $^ $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE) $(LFLAGS)

# Object files (test)
test-init.o: $(TEST_PATH)test-init.o
test-config.o: $(TEST_PATH)test-config.o
test-device.o: $(TEST_PATH)test-device.o
test-physics.o: $(TEST_PATH)test-physics.o
test-window.o: $(TEST_PATH)test-window.o
test-system.o: $(TEST_PATH)test-system.o
test-ttf.o: $(TEST_PATH)test-ttf.o
test-particle.o: $(TEST_PATH)test-particle.o
test-file.o: $(TEST_PATH)test-file.o
test-ime.o: $(TEST_PATH)test-ime.o
test-audio.o: $(TEST_PATH)test-audio.o
test-thread.o: $(TEST_PATH)test-thread.o
test-input.o: $(TEST_PATH)test-input.o


################################
#                              #
# General rules + dependencies #
#                              #
################################

# General rule
%.o: %.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) $(CFLAGS) $(OPTIMIZE) $(OPT_SIZE)

# Dependencies
depend: $(SRC_FILES) $(SRC_TEST_FILES)
	@touch $(DEPENDENCY)
	@echo -n "Generate dependencies... " && \
	makedepend $^ -I $(LIBRARIES_I_DIR) -I $(SDL2_I_PATH) -f $(DEPENDENCY) 2>/dev/null \
	&& echo "DONE"; rm -f $(DEPENDENCY).bak


######################################
#                                    #
# Generate the doxygen documentation #
#                                    #
######################################

documentation: $(DOXY_FILE)
	@echo "Generating the doxygen file from "$<
	@doxygen $<


#########################
#                       #
# Clean generated files #
#                       #
#########################

clean:
	@echo "Delete object files"
	@find $(LUNATIX_PATH) $(SRC_MAIN_PATH) $(TEST_PATH) -name '*.o' -exec rm {} \;
	@echo "Delete library files"
	@rm -f $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)
	@echo "Delete the dependency graph"
	@rm -rf $(DEPENDENCY)

cleandoc:
	@echo "Delete the doxygen documentation"
	@rm -rf html/

clear: cleandoc clean
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE)

# Dependency file (automatically generated by depend)
include $(wildcard $(DEPENDENCY))
