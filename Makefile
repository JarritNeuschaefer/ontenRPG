# Compiler-Optionen
CXX = g++
CXXFLAGS = -Isrc/include -DSFML_STATIC -Iheader

# Dateien und Verzeichnisse
SRC_DIR = scripts
OBJ_DIR = src/compile
LIB_DIR = src/lib

# Zielfile
TARGET = game

# Dateilisten
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Standardziel: Kompilieren, Linken und Ausführen
all: compile link run

# Kompilieren der Quelldateien in Objektdateien
compile: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linken der Objektdateien zu einer ausführbaren Datei
link: $(OBJ_FILES)
	$(CXX) $^ -o $(TARGET) -L$(LIB_DIR) -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

# Aufräumen: Löschen der Objektdateien
clean:
	rm -f $(OBJ_DIR)/*.o

# Ausführen des Programms
run:
	./$(TARGET)
