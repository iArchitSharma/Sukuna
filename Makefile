# Variables
TARGET_EXEC_WIN = sukuna.exe
TARGET_EXEC_LINUX = sukuna
SRC_DIR = src
RELEASE_DIR = release
TEMP_DIR_WIN = $(RELEASE_DIR)/temp
TEMP_DIR_LINUX = $(RELEASE_DIR)/temp2
ZIP_FILE_WIN = $(RELEASE_DIR)/sukuna-win-v1.zip
ZIP_FILE_LINUX = $(RELEASE_DIR)/sukuna-linux-v1.zip
WIN_UTIL_DIR = util/win
LINUX_UTIL_DIR = util/linux

# MinGW compiler for Windows
CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS_WIN = -static

# GCC compiler for Linux
CXX_LINUX = g++
CXXFLAGS_LINUX = -static

# Default target
all: clean build-win zip-win build-linux zip-linux clean-temp

# Windows Build
build-win: prepare-temp-win
	$(CXX_WIN) $(CXXFLAGS_WIN) -o $(TEMP_DIR_WIN)/$(TARGET_EXEC_WIN) $(SRC_DIR)/*.cpp

# Create Windows zip file from the temp directory
zip-win: build-win
	cd $(TEMP_DIR_WIN) && zip -r ../sukuna-win-v1.zip .

# Linux Build
build-linux: prepare-temp-linux
	$(CXX_LINUX) $(CXXFLAGS_LINUX) -o $(TEMP_DIR_LINUX)/$(TARGET_EXEC_LINUX) $(SRC_DIR)/sukuna.cpp

# Create Linux zip file from the temp2 directory
zip-linux: build-linux
	cd $(TEMP_DIR_LINUX) && zip -r ../sukuna-linux-v1.zip .

# Create the temp directory and prepare files for Windows
prepare-temp-win:
	mkdir -p $(TEMP_DIR_WIN)
	cp -r $(WIN_UTIL_DIR)/* $(TEMP_DIR_WIN)/

# Create the temp directory and prepare files for Linux
prepare-temp-linux:
	mkdir -p $(TEMP_DIR_LINUX)
	cp -r $(LINUX_UTIL_DIR)/* $(TEMP_DIR_LINUX)/

# Clean up
clean:
	rm -f $(RELEASE_DIR)/$(TARGET_EXEC_WIN) $(ZIP_FILE_WIN) $(ZIP_FILE_LINUX)
	rm -f $(RELEASE_DIR)/$(TARGET_EXEC_LINUX)

# Remove the temp directories
clean-temp:
	rm -rf $(TEMP_DIR_WIN) $(TEMP_DIR_LINUX)
