# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dameon0430/Documents/Dev/SFML/learno

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dameon0430/Documents/Dev/SFML/learno/build

# Include any dependencies generated for this target.
include CMakeFiles/learnSFML.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/learnSFML.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/learnSFML.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/learnSFML.dir/flags.make

CMakeFiles/learnSFML.dir/src/particleTest.cpp.o: CMakeFiles/learnSFML.dir/flags.make
CMakeFiles/learnSFML.dir/src/particleTest.cpp.o: ../src/particleTest.cpp
CMakeFiles/learnSFML.dir/src/particleTest.cpp.o: CMakeFiles/learnSFML.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dameon0430/Documents/Dev/SFML/learno/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/learnSFML.dir/src/particleTest.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnSFML.dir/src/particleTest.cpp.o -MF CMakeFiles/learnSFML.dir/src/particleTest.cpp.o.d -o CMakeFiles/learnSFML.dir/src/particleTest.cpp.o -c /Users/dameon0430/Documents/Dev/SFML/learno/src/particleTest.cpp

CMakeFiles/learnSFML.dir/src/particleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnSFML.dir/src/particleTest.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dameon0430/Documents/Dev/SFML/learno/src/particleTest.cpp > CMakeFiles/learnSFML.dir/src/particleTest.cpp.i

CMakeFiles/learnSFML.dir/src/particleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnSFML.dir/src/particleTest.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dameon0430/Documents/Dev/SFML/learno/src/particleTest.cpp -o CMakeFiles/learnSFML.dir/src/particleTest.cpp.s

# Object files for target learnSFML
learnSFML_OBJECTS = \
"CMakeFiles/learnSFML.dir/src/particleTest.cpp.o"

# External object files for target learnSFML
learnSFML_EXTERNAL_OBJECTS =

learnSFML: CMakeFiles/learnSFML.dir/src/particleTest.cpp.o
learnSFML: CMakeFiles/learnSFML.dir/build.make
learnSFML: SFML/lib/libsfml-graphics-d.2.5.1.dylib
learnSFML: SFML/lib/libsfml-window-d.2.5.1.dylib
learnSFML: SFML/lib/libsfml-system-d.2.5.1.dylib
learnSFML: CMakeFiles/learnSFML.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dameon0430/Documents/Dev/SFML/learno/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable learnSFML"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/learnSFML.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/learnSFML.dir/build: learnSFML
.PHONY : CMakeFiles/learnSFML.dir/build

CMakeFiles/learnSFML.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/learnSFML.dir/cmake_clean.cmake
.PHONY : CMakeFiles/learnSFML.dir/clean

CMakeFiles/learnSFML.dir/depend:
	cd /Users/dameon0430/Documents/Dev/SFML/learno/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dameon0430/Documents/Dev/SFML/learno /Users/dameon0430/Documents/Dev/SFML/learno /Users/dameon0430/Documents/Dev/SFML/learno/build /Users/dameon0430/Documents/Dev/SFML/learno/build /Users/dameon0430/Documents/Dev/SFML/learno/build/CMakeFiles/learnSFML.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/learnSFML.dir/depend

