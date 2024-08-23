TARGET_EXEC = sukuna.exe
SRC_DIR = src
RELEASE_DIR = release
TEMP_DIR = $(RELEASE_DIR)/temp
ZIP_FILE = $(RELEASE_DIR)/sukuna-win-v1.zip
WIN_UTIL_DIR = util/win

# MinGW compiler
CXX = x86_64-w64-mingw32-g++
CXXFLAGS = -static

# Default target
all: clean build zip clean-temp

# Create the temp directory and prepare files
prepare-temp:
	mkdir -p $(TEMP_DIR)
	cp -r $(WIN_UTIL_DIR)/* $(TEMP_DIR)/

# Build the executable and place it in temp
build: prepare-temp
	$(CXX) $(CXXFLAGS) -o $(TEMP_DIR)/$(TARGET_EXEC) $(SRC_DIR)/*.cpp

# Create the zip file from the temp directory
zip: build
	cd $(TEMP_DIR) && zip -r ../sukuna-win-v1.zip .

# Clean up
clean:
	rm -f $(RELEASE_DIR)/$(TARGET_EXEC) $(ZIP_FILE)

# Remove the temp directory
clean-temp:
	rm -rf $(TEMP_DIR)