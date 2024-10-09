# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/xmrig

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/xmrig/build

# Include any dependencies generated for this target.
include src/3rdparty/libethash/CMakeFiles/ethash.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/3rdparty/libethash/CMakeFiles/ethash.dir/compiler_depend.make

# Include the progress variables for this target.
include src/3rdparty/libethash/CMakeFiles/ethash.dir/progress.make

# Include the compile flags for this target's objects.
include src/3rdparty/libethash/CMakeFiles/ethash.dir/flags.make

src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.o: src/3rdparty/libethash/CMakeFiles/ethash.dir/flags.make
src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.o: ../src/3rdparty/libethash/ethash_internal.c
src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.o: src/3rdparty/libethash/CMakeFiles/ethash.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/xmrig/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.o"
	cd /root/xmrig/build/src/3rdparty/libethash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.o -MF CMakeFiles/ethash.dir/ethash_internal.c.o.d -o CMakeFiles/ethash.dir/ethash_internal.c.o -c /root/xmrig/src/3rdparty/libethash/ethash_internal.c

src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ethash.dir/ethash_internal.c.i"
	cd /root/xmrig/build/src/3rdparty/libethash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/xmrig/src/3rdparty/libethash/ethash_internal.c > CMakeFiles/ethash.dir/ethash_internal.c.i

src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ethash.dir/ethash_internal.c.s"
	cd /root/xmrig/build/src/3rdparty/libethash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/xmrig/src/3rdparty/libethash/ethash_internal.c -o CMakeFiles/ethash.dir/ethash_internal.c.s

src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.o: src/3rdparty/libethash/CMakeFiles/ethash.dir/flags.make
src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.o: ../src/3rdparty/libethash/keccakf800.c
src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.o: src/3rdparty/libethash/CMakeFiles/ethash.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/xmrig/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.o"
	cd /root/xmrig/build/src/3rdparty/libethash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.o -MF CMakeFiles/ethash.dir/keccakf800.c.o.d -o CMakeFiles/ethash.dir/keccakf800.c.o -c /root/xmrig/src/3rdparty/libethash/keccakf800.c

src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ethash.dir/keccakf800.c.i"
	cd /root/xmrig/build/src/3rdparty/libethash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/xmrig/src/3rdparty/libethash/keccakf800.c > CMakeFiles/ethash.dir/keccakf800.c.i

src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ethash.dir/keccakf800.c.s"
	cd /root/xmrig/build/src/3rdparty/libethash && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/xmrig/src/3rdparty/libethash/keccakf800.c -o CMakeFiles/ethash.dir/keccakf800.c.s

# Object files for target ethash
ethash_OBJECTS = \
"CMakeFiles/ethash.dir/ethash_internal.c.o" \
"CMakeFiles/ethash.dir/keccakf800.c.o"

# External object files for target ethash
ethash_EXTERNAL_OBJECTS =

src/3rdparty/libethash/libethash.a: src/3rdparty/libethash/CMakeFiles/ethash.dir/ethash_internal.c.o
src/3rdparty/libethash/libethash.a: src/3rdparty/libethash/CMakeFiles/ethash.dir/keccakf800.c.o
src/3rdparty/libethash/libethash.a: src/3rdparty/libethash/CMakeFiles/ethash.dir/build.make
src/3rdparty/libethash/libethash.a: src/3rdparty/libethash/CMakeFiles/ethash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/xmrig/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libethash.a"
	cd /root/xmrig/build/src/3rdparty/libethash && $(CMAKE_COMMAND) -P CMakeFiles/ethash.dir/cmake_clean_target.cmake
	cd /root/xmrig/build/src/3rdparty/libethash && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ethash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/3rdparty/libethash/CMakeFiles/ethash.dir/build: src/3rdparty/libethash/libethash.a
.PHONY : src/3rdparty/libethash/CMakeFiles/ethash.dir/build

src/3rdparty/libethash/CMakeFiles/ethash.dir/clean:
	cd /root/xmrig/build/src/3rdparty/libethash && $(CMAKE_COMMAND) -P CMakeFiles/ethash.dir/cmake_clean.cmake
.PHONY : src/3rdparty/libethash/CMakeFiles/ethash.dir/clean

src/3rdparty/libethash/CMakeFiles/ethash.dir/depend:
	cd /root/xmrig/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/xmrig /root/xmrig/src/3rdparty/libethash /root/xmrig/build /root/xmrig/build/src/3rdparty/libethash /root/xmrig/build/src/3rdparty/libethash/CMakeFiles/ethash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/3rdparty/libethash/CMakeFiles/ethash.dir/depend

