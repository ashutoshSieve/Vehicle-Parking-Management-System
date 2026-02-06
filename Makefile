##############################################################################
# Vehicle Parking System - Makefile for mingw32-make (cmd)
##############################################################################

# Use Windows cmd.exe as shell
SHELL := cmd
.SHELLFLAGS := /C

# Compiler & flags
CXX      := g++
CXXFLAGS := -std=gnu++17 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -MMD -MP
INCLUDES := -I"include"

# Build type toggles
DEBUG_FLAGS   := -g -O0 -DDEBUG
RELEASE_FLAGS := -O3 -DNDEBUG

# Directories
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
BIN_DIR   := bin

# Target
TARGET := "$(BIN_DIR)\\parking_app.exe"

# ----------------------------------------------------------------------------
# Source collection
# Add/remove subdirectories here if your structure changes
# ----------------------------------------------------------------------------
SRCS := \
  $(wildcard $(SRC_DIR)/*.cpp) \
  $(wildcard $(SRC_DIR)/domain/*.cpp) \
  $(wildcard $(SRC_DIR)/pricing/*.cpp) \
  $(wildcard $(SRC_DIR)/parking/*.cpp)

# Object files under build/ mirroring src/ structure
# Convert forward slashes to backslashes for Windows paths where needed
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Dependency files
DEPS := $(OBJS:.o=.d)

# Default goal
.PHONY: all
all: dirs $(TARGET)

# Debug / Release
.PHONY: debug release
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

release: CXXFLAGS += $(RELEASE_FLAGS)
release: clean all

# Link
$(TARGET): $(OBJS)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET)

# Compile each .cpp into build/%.o
# Ensure the object folder exists before compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

# Create top-level build/bin directories if missing
.PHONY: dirs
dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BIN_DIR)"   mkdir "$(BIN_DIR)"

# Run (optional)
.PHONY: run
run: all
	$(TARGET)

# Clean
.PHONY: clean
clean:
	@echo Cleaning...
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(BIN_DIR)"   rmdir /S /Q "$(BIN_DIR)"

# Include auto-generated dependencies (ignore if missing)
-include $(DEPS)

######## MAKE, RUN & CLEAN ########
##MAKE -> mingw32-make
##RUN -> .\bin\parking_app.exe
##CLEAN -> mingw32-make clean