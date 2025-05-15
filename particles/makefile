SRC_DIRS := engine particle matrices
SRC_FILES := $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS))) main.cpp

OBJ_DIR := build
OBJ_FILES := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

LDFLAGS := -Lcode/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS := -g -Wall -fpermissive -std=c++17 -Icode/SFML/include

TARGET := particle.out

# Final binary
$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile .cpp to build/ with subdirectory structure
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run rule (loads DLLs from ./dll directory)
run: $(TARGET)
	PATH=./dll:$$PATH ./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
