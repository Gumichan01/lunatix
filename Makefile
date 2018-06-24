
#
#   Copyright © 2017 Luxon Jean-Pierre
#   https://gumichan01.github.io/
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

CC=g++

# Path to the test files
TEST_PATH=./test/

# Executable file
LUNATIX_EXE=lunatix-demo

# Path to directories
SRC_PATH=./src/
LUNATIX_PATH=./src/Lunatix/
OPENGL_DIR=/usr/include/
LIBRARIES_I_DIR=./include/
LUNATIX_I_PATH=$(LIBRARIES_I_DIR)Lunatix/
UTILS_I_PATH=$(LUNATIX_I_PATH)utils/
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
SRC_LIBTAGSPP_PATH=$(SRC_UTILS_PATH)libtagspp/

# Path to the different sources files
MAIN_FILE=$(SRC_MAIN_PATH)main.cpp
SRC_FILES=$(SRC_DEVICE_PATH)Device.cpp $(SRC_DEVICE_PATH)Gamepad.cpp \
$(SRC_DEVICE_PATH)Haptic.cpp $(SRC_DEVICE_PATH)Mouse.cpp \
$(SRC_FILEIO_PATH)FileIO.cpp $(SRC_FILEIO_PATH)FileBuffer.cpp \
$(SRC_GRAPHICS_PATH)OpenGL.cpp $(SRC_GRAPHICS_PATH)Window.cpp \
$(SRC_GRAPHICS_PATH)WindowManager.cpp $(SRC_GRAPHICS_PATH)Texture.cpp \
$(SRC_GRAPHICS_PATH)ImgRect.cpp $(SRC_INPUT_PATH)Event.cpp \
$(SRC_LIBRARY_PATH)Config.cpp $(SRC_LIBRARY_PATH)Library.cpp \
$(SRC_MIXER_PATH)Sound.cpp $(SRC_MIXER_PATH)Chunk.cpp \
$(SRC_MIXER_PATH)Music.cpp $(SRC_MIXER_PATH)Mixer.cpp \
$(SRC_MSG_PATH)MessageBox.cpp $(SRC_MULTITHREAD_PATH)Thread.cpp \
$(SRC_PARTICLE_PATH)Particle.cpp $(SRC_PARTICLE_PATH)ParticleSystem.cpp \
$(SRC_PHYSICS_PATH)Hitbox.cpp $(SRC_PHYSICS_PATH)Physics.cpp \
$(SRC_PHYSICS_PATH)Polygon.cpp $(SRC_PHYSICS_PATH)Vector2D.cpp \
$(SRC_RANDOM_PATH)Random.cpp $(SRC_SYSTEM_PATH)SystemInfo.cpp \
$(SRC_SYSTEM_PATH)Log.cpp $(SRC_SYSTEM_PATH)FileSystem.cpp \
$(SRC_TEXT_PATH)Text.cpp $(SRC_TTF_PATH)TrueTypeFont.cpp \
$(SRC_VERSION_PATH)Version.cpp \
$(SRC_UTILS_PATH)utf8_string.cpp $(SRC_UTILS_PATH)utf8_iterator.cpp \
$(SRC_LIBTAGSPP_PATH)8859.cpp $(SRC_LIBTAGSPP_PATH)flac.cpp \
$(SRC_LIBTAGSPP_PATH)id3genres.cpp $(SRC_LIBTAGSPP_PATH)id3v1.cpp \
$(SRC_LIBTAGSPP_PATH)id3v2.cpp $(SRC_LIBTAGSPP_PATH)m4a.cpp \
$(SRC_LIBTAGSPP_PATH)tags.cpp $(SRC_LIBTAGSPP_PATH)utf16.cpp \
$(SRC_LIBTAGSPP_PATH)vorbis.cpp $(SRC_LIBTAGSPP_PATH)libtagspp.cpp \
$(SRC_UTILS_PATH)float.cpp

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
WMISC_FLAGS=-Wlogical-op -Wformat=2 -Wmissing-declarations -Woverloaded-virtual -fno-common
WFLAGS=-Wall -Wextra -pedantic -Weffc++ $(WMISC_FLAGS)

# Select flags according to the compilation mode
ifeq ($(DEBUG),yes)

	# Debug mode
	CFLAGS=-fPIC $(WFLAGS) -std=c++11 -g -fsanitize=address
	OPTIMIZE=-O0
	OPT_SIZE=

else

	# Release mode
	CFLAGS=-fPIC -w -std=c++11 -g
	OPTIMIZE=-O3
	OPT_SIZE=-s

endif

ifeq ($(PREFIX),)
	PREFIX=/usr/local
endif

PKG_CONFIG_DIR=$(PREFIX)/lib/pkgconfig
LUNATIX_PKG=lunatix.pc

# Linking flags
LFLAGS=`pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf gl`

DOXY_FILE=dox

########################
#                      #
# Generate the library #
#                      #
########################

.PHONY: depend test clean cleandoc documentation $(DEPENDENCY)

all: library

library: depend $(LUNATIX_STATIC_LIB) $(LUNATIX_SHARED_LIB)

install: install-hdrs install-libs

install-hdrs:
	install -d $(DESTDIR)/$(PREFIX)/include/
	cp -R ./include/Lunatix/ $(DESTDIR)/$(PREFIX)/include/

install-libs:
	@rm -f $(DEPENDENCY)
	cp $(LUNATIX_PKG) $(PKG_CONFIG_DIR)/
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install -m 644 $(LUNATIX_STATIC_LIB) $(DESTDIR)/$(PREFIX)/lib/
	install -m 744 $(LUNATIX_SHARED_LIB) $(DESTDIR)/$(PREFIX)/lib/

uninstall:
	rm -vf $(PKG_CONFIG_DIR)/$(LUNATIX_PKG)
	rm -vf $(DESTDIR)/$(PREFIX)/lib/libLunatix.a
	rm -vf $(DESTDIR)/$(PREFIX)/lib/libLunatix.so
	rm -rvf $(DESTDIR)/$(PREFIX)/include/Lunatix/

$(LUNATIX_STATIC_LIB): $(OBJ_FILES)
	@echo -n "Generating the static library → "$@"... "
	@mkdir -p $(LUNATIX_LIB_DIR)
	@ar rcs $@ $(OBJ_FILES)
	@echo "DONE"

$(LUNATIX_SHARED_LIB): $(OBJ_FILES)
	@echo -n "Generating the shared library → "$@"... "
	@mkdir -p $(LUNATIX_LIB_DIR)
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
Device.o: $(SRC_DEVICE_PATH)Device.o
Gamepad.o: $(SRC_DEVICE_PATH)Gamepad.o
Haptic.o: $(SRC_DEVICE_PATH)Haptic.o
Mouse.o: $(SRC_DEVICE_PATH)Mouse.o
FileIO.o: $(SRC_FILEIO_PATH)FileIO.o
FileBuffer.o: $(SRC_FILEIO_PATH)FileBuffer.o
OpenGL.o: $(SRC_GRAPHICS_PATH)OpenGL.o
Window.o: $(SRC_GRAPHICS_PATH)Window.o
WindowManager.o: $(SRC_GRAPHICS_PATH)WindowManager.o
Texture.o: $(SRC_GRAPHICS_PATH)Texture.o
ImgRect.o: $(SRC_GRAPHICS_PATH)ImgRect.o
Event.o: $(SRC_INPUT_PATH)Event.o
Config.o: $(SRC_LIBRARY_PATH)Config.o
Library.o: $(SRC_LIBRARY_PATH)Library.o
Sound.o: $(SRC_MIXER_PATH)Sound.o
Chunk.o: $(SRC_MIXER_PATH)Chunk.o
Music.o: $(SRC_MIXER_PATH)Music.o
Mixer.o: $(SRC_MIXER_PATH)Mixer.o
MessageBox.o: $(SRC_MSG_PATH)MessageBox.o
Thread.o: $(SRC_MULTITHREAD_PATH)Thread.o
Particle.o: $(SRC_PARTICLE_PATH)Particle.o
ParticleSystem.o: $(SRC_PARTICLE_PATH)ParticleSystem.o
Physics.o: $(SRC_PHYSICS_PATH)Physics.o
Polygon.o: $(SRC_PHYSICS_PATH)Polygon.o
Hitbox.o: $(SRC_PHYSICS_PATH)Hitbox.o
Random.o: $(SRC_RANDOM_PATH)Random.o
SystemInfo.o: $(SRC_SYSTEM_PATH)SystemInfo.o
FileSystem.o: $(SRC_SYSTEM_PATH)FileSystem.o
Log.o: $(SRC_SYSTEM_PATH)Log.o
Text.o: $(SRC_TEXT_PATH)Text.o
TrueTypeFont.o: $(SRC_TTF_PATH)TrueTypeFont.o
Version.o: $(SRC_VERSION_PATH)Version.o
float.o: $(SRC_UTILS_PATH)float.o


##########
#        #
#  Test  #
#        #
##########

test: depend test-init test-config test-system test-device test-file test-physics \
test-audio test-window test-ttf test-particle test-ime test-thread test-random


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

test-random: $(TEST_PATH)test-random.o $(OBJ_FILES)
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
test-random.o: $(TEST_PATH)test-random.o


################################
#                              #
# General rules + dependencies #
#                              #
################################

# General rule
%.o: %.cpp
	@echo $@" - Compiling "$<
	@$(CC) -c -o $@ $< -I $(SDL2_I_PATH) -I $(LIBRARIES_I_DIR) -I $(OPENGL_DIR) \
	$(CFLAGS) $(OPTIMIZE) $(OPT_SIZE)

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

mrproper: cleandoc clean
	@echo "Delete targets"
	@rm -f $(LUNATIX_EXE) test-*

distclean: mrproper

# Dependency file (automatically generated by depend)
include $(wildcard $(DEPENDENCY))
