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
include src/CMakeFiles/SamplePointReconstruction.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/SamplePointReconstruction.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/SamplePointReconstruction.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/SamplePointReconstruction.dir/flags.make

src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o: src/CMakeFiles/SamplePointReconstruction.dir/flags.make
src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o: /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SamplePointReconstruction/SamplePointReconstruction.cpp
src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o: src/CMakeFiles/SamplePointReconstruction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o -MF CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o.d -o CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o -c /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SamplePointReconstruction/SamplePointReconstruction.cpp

src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.i"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SamplePointReconstruction/SamplePointReconstruction.cpp > CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.i

src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.s"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src/SamplePointReconstruction/SamplePointReconstruction.cpp -o CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.s

# Object files for target SamplePointReconstruction
SamplePointReconstruction_OBJECTS = \
"CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o"

# External object files for target SamplePointReconstruction
SamplePointReconstruction_EXTERNAL_OBJECTS =

/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SamplePointReconstruction: src/CMakeFiles/SamplePointReconstruction.dir/SamplePointReconstruction/SamplePointReconstruction.cpp.o
/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SamplePointReconstruction: src/CMakeFiles/SamplePointReconstruction.dir/build.make
/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SamplePointReconstruction: src/CMakeFiles/SamplePointReconstruction.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SamplePointReconstruction"
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SamplePointReconstruction.dir/link.txt --verbose=$(VERBOSE)
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake -E copy_directory /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/lib/3dcamera/linux/x64/ /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin >nul

# Rule to build all files generated by this target.
src/CMakeFiles/SamplePointReconstruction.dir/build: /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/bin/SamplePointReconstruction
.PHONY : src/CMakeFiles/SamplePointReconstruction.dir/build

src/CMakeFiles/SamplePointReconstruction.dir/clean:
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src && $(CMAKE_COMMAND) -P CMakeFiles/SamplePointReconstruction.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/SamplePointReconstruction.dir/clean

src/CMakeFiles/SamplePointReconstruction.dir/depend:
	cd /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411 /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/src /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src /home/robo/cosmetic_robot/face_model/chishine3d_sdk/3DCameraSDK-v3.2.20.20230411/build/src/CMakeFiles/SamplePointReconstruction.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/SamplePointReconstruction.dir/depend
