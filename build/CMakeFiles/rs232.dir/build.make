# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Job/Documents/Git/communication-protocols

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Job/Documents/Git/communication-protocols/build

# Include any dependencies generated for this target.
include CMakeFiles/rs232.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rs232.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rs232.dir/flags.make

CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o: CMakeFiles/rs232.dir/flags.make
CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o: /cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Job/Documents/Git/communication-protocols/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o   -c /cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c

CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c > CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.i

CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c -o CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.s

CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.requires:

.PHONY : CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.requires

CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.provides: CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.requires
	$(MAKE) -f CMakeFiles/rs232.dir/build.make CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.provides.build
.PHONY : CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.provides

CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.provides.build: CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o


# Object files for target rs232
rs232_OBJECTS = \
"CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o"

# External object files for target rs232
rs232_EXTERNAL_OBJECTS =

librs232.a: CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o
librs232.a: CMakeFiles/rs232.dir/build.make
librs232.a: CMakeFiles/rs232.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Job/Documents/Git/communication-protocols/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library librs232.a"
	$(CMAKE_COMMAND) -P CMakeFiles/rs232.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rs232.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rs232.dir/build: librs232.a

.PHONY : CMakeFiles/rs232.dir/build

CMakeFiles/rs232.dir/requires: CMakeFiles/rs232.dir/cygdrive/c/Users/Job/Documents/Git/deps/rs232/rs232.c.o.requires

.PHONY : CMakeFiles/rs232.dir/requires

CMakeFiles/rs232.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rs232.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rs232.dir/clean

CMakeFiles/rs232.dir/depend:
	cd /cygdrive/c/Users/Job/Documents/Git/communication-protocols/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Job/Documents/Git/communication-protocols /cygdrive/c/Users/Job/Documents/Git/communication-protocols /cygdrive/c/Users/Job/Documents/Git/communication-protocols/build /cygdrive/c/Users/Job/Documents/Git/communication-protocols/build /cygdrive/c/Users/Job/Documents/Git/communication-protocols/build/CMakeFiles/rs232.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rs232.dir/depend

