# Compiler
CC = gcc

# Directories
ENGINE_DIR = engine
GAME_DIR = game
OBJ_DIR = obj

# Static library name
AR = ar
AR_FLAGS = rcs
LIBRARY = $(ENGINE_DIR)/libengine.a  # Static library with C convention

# Source and Object files
ENGINE_SOURCES = $(shell find $(ENGINE_DIR) -name '*.c')
ENGINE_OBJECTS = $(ENGINE_SOURCES:$(ENGINE_DIR)/%.c=$(OBJ_DIR)/%.o)

GAME_SOURCES = $(shell find $(GAME_DIR) -name '*.c')
GAME_OBJECTS = $(GAME_SOURCES:$(GAME_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(LIBRARY) $(GAME_DIR)/game

$(LIBRARY): $(ENGINE_OBJECTS)
	mkdir -p $(ENGINE_DIR) $(OBJ_DIR)
	$(AR) $(AR_FLAGS) $@ $^

$(OBJ_DIR)/%.o: $(ENGINE_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

$(OBJ_DIR)/%.o: $(GAME_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -Iengine/headers $< -o $@

# Build the game executable
$(GAME_DIR)/game: $(GAME_OBJECTS) $(LIBRARY)
	$(CC) -o $@ $(GAME_OBJECTS) $(LIBRARY)  # Link the game with the static library directly

run: $(GAME_DIR)/game
	./$(GAME_DIR)/game

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIBRARY) $(GAME_DIR)/game

.PHONY: all clean run
