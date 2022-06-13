# Define the link target.
linkTarget = a.out

#pwd 명령으로 확인 가능
HOME = $(PWD)

SRC_DIR := $(HOME)/src
INC_DIR := $(HOME)/include
OBJ_DIR := $(HOME)/build
BIN_DIR := $(HOME)/bin
SDL_INC := $(HOME)/3rdParty/SDL/include
SDL_LIB := $(HOME)/3rdParty/SDL/lib/x86_64-linux-gnu

CC := c++
EXE := $(BIN_DIR)/a.out
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP -I$(INC_DIR) -I$(SDL_INC)
CFLAGS   := -Wall 
LDFLAGS  := -Llib
LDLIBS   := -lm

#SDL_LIBS := -L$(SDL_LIB)/libSDL2_2.0.so -lSDL2 -L$(SDL_LIB)/libSDL2_image-2.0.so $(SDL_LIB)/libSDL2_image.a -L $(SDL_LIB)/libSDL2_gfx.so $(SDL_LIB)/libSDL2_gfx.a -L $(SDL_LIB)/libSDL2_ttf-2.0.so $(SDL_LIB)/libSDL2_ttf.a  -L $(SDL_LIB)/libSDL2_mixer-2.0.so $(SDL_LIB)/libSDL2_mixer.a -lfreetype -lpng -ljpeg -ltiff -lwebp

#mixer install 후 실행 가능 버전 
SDL_LIBS := -L$(SDL_LIB)/libSDL2_2.0.so -lSDL2 -L$(SDL_LIB)/libSDL2_image-2.0.so $(SDL_LIB)/libSDL2_image.a -L $(SDL_LIB)/libSDL2_gfx.so $(SDL_LIB)/libSDL2_gfx.a -L $(SDL_LIB)/libSDL2_ttf-2.0.so $(SDL_LIB)/libSDL2_ttf.a -lSDL2_mixer -lfreetype -lpng -ljpeg -ltiff -lwebp


# -L $(SDL_LIB)/libFLAC.so   -L $(SDL_LIB)/libogg.so.2.6.0  $(SDL_LIB)/libogg.a -L $(SDL_LIB)/libfluidsynth.so -L $(SDL_LIB)/libSDL2_mixer-2.0.so  $(SDL_LIB)/libSDL2_mixer.a  $(SDL_LIB)/libFLAC.a

MIXER = libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 libflac-dev

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(SDL_LIBS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

install:
	install-pkg $(MIXER)

setup:
	export LIBRARY_PATH=$(SDL_LIB)
	export LD_LIBRARY_PATH=$(SDL_LIB)

-include $(OBJ:.o=.d)

run: $(EXE)
	$(EXE)

#export LIBRARY_PATH=/home/runner/.apt/usr/lib/x86_64-linux-gnu:/home/runner/.apt/usr/lib/i386-linux-gnu:/usr/local/lib:/home/runner/.apt/usr/lib:/home/runner/HoseoSDL/3rdParty/SDL/lib/x86_64-linux-gnu
#export LD_LIBRARY_PATH=/home/runner/.apt/usr/lib/x86_64-linux-gnu:/home/runner/.apt/usr/lib/i386-linux-gnu:/usr/local/lib:/home/runner/.apt/usr/lib:/home/runner/HoseoSDL/3rdParty/SDL/lib/x86_64-linux-gnu