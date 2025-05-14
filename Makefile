CC = g++
CFLAGS = -std=c++17 -Iinclude -MMD -MP
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
EXECUTABLE = main
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ -o $@
	@echo "Linking complete: $@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $< => $@"


clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned object files and executable"

run: $(BUILD_DIR)/$(EXECUTABLE)
	./$(BUILD_DIR)/$(EXECUTABLE)

.PHONY: all clean run