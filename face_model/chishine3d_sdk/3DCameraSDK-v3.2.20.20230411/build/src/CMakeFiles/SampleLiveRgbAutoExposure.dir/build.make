# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build

# Include any dependencies generated for this target.
include src/CMakeFiles/SampleLiveRgbAutoExposure.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/SampleLiveRgbAutoExposure.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/SampleLiveRgbAutoExposure.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/SampleLiveRgbAutoExposure.dir/flags.make

src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o: src/CMakeFiles/SampleLiveRgbAutoExposure.dir/flags.make
src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o: /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp
src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o: src/CMakeFiles/SampleLiveRgbAutoExposure.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o -MF CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o.d -o CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o -c /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp

src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.i"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp > CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.i

src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.s"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp -o CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.s

# Object files for target SampleLiveRgbAutoExposure
SampleLiveRgbAutoExposure_OBJECTS = \
"CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o"

# External object files for target SampleLiveRgbAutoExposure
SampleLiveRgbAutoExposure_EXTERNAL_OBJECTS =

/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SampleLiveRgbAutoExposure: src/CMakeFiles/SampleLiveRgbAutoExposure.dir/SampleLiveRgbAutoExposure/SampleLiveRgbAutoExposure.cpp.o
/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SampleLiveRgbAutoExposure: src/CMakeFiles/SampleLiveRgbAutoExposure.dir/build.make
/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SampleLiveRgbAutoExposure: src/CMakeFiles/SampleLiveRgbAutoExposure.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SampleLiveRgbAutoExposure"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SampleLiveRgbAutoExposure.dir/link.txt --verbose=$(VERBOSE)
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake -E copy_directory /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/lib/3dcamera/linux/x64/ /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin >nul

# Rule to build all files generated by this target.
src/CMakeFiles/SampleLiveRgbAutoExposure.dir/build: /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SampleLiveRgbAutoExposure
.PHONY : src/CMakeFiles/SampleLiveRgbAutoExposure.dir/build

src/CMakeFiles/SampleLiveRgbAutoExposure.dir/clean:
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && $(CMAKE_COMMAND) -P CMakeFiles/SampleLiveRgbAutoExposure.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/SampleLiveRgbAutoExposure.dir/clean

src/CMakeFiles/SampleLiveRgbAutoExposure.dir/depend:
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411 /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src/CMakeFiles/SampleLiveRgbAutoExposure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/SampleLiveRgbAutoExposure.dir/depend

