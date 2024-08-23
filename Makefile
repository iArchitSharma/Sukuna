# Variables
TARGET_EXEC = sukuna.exe
SRC_DIR = src
ZIP_FILE = sukuna-release.zip
WIN_UTIL_DIR = util/win

# MinGW compiler
CXX = x86_64-w64-mingw32-g++
CXXFLAGS = -static

# Default target
all: build zip

# Build the executable
build:
	$(CXX) $(CXXFLAGS) -o $(TARGET_EXEC) $(SRC_DIR)/*.cpp

# Create a zip file directly from the source and build directories
zip: build
	zip -r $(ZIP_FILE) $(TARGET_EXEC) $(WIN_UTIL_DIR)/*

# Clean up
clean:
	rm -rf $(TARGET_EXEC) $(ZIP_FILE)