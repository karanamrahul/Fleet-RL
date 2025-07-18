cmake_minimum_required(VERSION 3.28)
project(CPP_RAII_Move_Kata)

# Generate compile_commands.json for IDE support (clangd, VS Code, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enhanced compiler warning flags (properly formatted for CMake)
set(WARNING_FLAGS 
    "-Wall"                    # Enable most warning messages
    "-Wextra"                  # Enable extra warning flags not covered by -Wall
    "-Wpedantic"              # Issue warnings for uses of extensions to ISO C++
    "-Wshadow"                # Warn when a local variable shadows another local variable
    "-Wnon-virtual-dtor"      # Warn when a class has virtual functions but not virtual destructor
    "-Wold-style-cast"        # Warn on C-style casts
    "-Wcast-align"            # Warn on casts that increase alignment requirements
    "-Wunused"                # Warn on anything being unused
    "-Woverloaded-virtual"    # Warn when overload hides virtual function
    "-Wconversion"            # Warn on type conversions that may lose data
    "-Wsign-conversion"       # Warn on sign conversions
    "-Wmisleading-indentation" # Warn on misleading indentation
    "-Wduplicated-cond"       # Warn on duplicated conditions in if-else chains
    "-Wduplicated-branches"   # Warn on duplicated branches in if-else chains
    "-Wlogical-op"            # Warn on suspicious logical operations
    "-Wnull-dereference"      # Warn on null pointer dereferences
    "-Wuseless-cast"          # Warn on useless casts
    "-Wdouble-promotion"      # Warn on implicit double promotions
    "-Wformat=2"              # Extra format string checking
)

# Sanitizer flags for debug builds (properly formatted for CMake)
set(SANITIZER_FLAGS
    "-fsanitize=address"          # AddressSanitizer (ASan) - detects memory errors
    "-fsanitize=undefined"        # UndefinedBehaviorSanitizer (UBSan) - detects undefined behavior
    "-fsanitize=leak"             # LeakSanitizer - detects memory leaks (part of ASan)
    "-fno-sanitize-recover=all"   # Abort on first sanitizer error (don't continue)
    "-fsanitize-address-use-after-scope"  # Detect use-after-scope bugs
)

# Create executables for each kata
add_executable(kata1_basic_raii kata1_basic_raii.cpp)
add_executable(kata2_smart_pointers kata2_smart_pointers.cpp)
add_executable(kata3_advanced_move kata3_advanced_move.cpp)

# Set compiler flags based on build type
target_compile_options(kata1_basic_raii PRIVATE ${WARNING_FLAGS})
target_compile_options(kata2_smart_pointers PRIVATE ${WARNING_FLAGS})
target_compile_options(kata3_advanced_move PRIVATE ${WARNING_FLAGS})

# Apply sanitizer flags and debug options for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(kata1_basic_raii PRIVATE ${SANITIZER_FLAGS} "-g" "-O0" "-DDEBUG")
    target_compile_options(kata2_smart_pointers PRIVATE ${SANITIZER_FLAGS} "-g" "-O0" "-DDEBUG")
    target_compile_options(kata3_advanced_move PRIVATE ${SANITIZER_FLAGS} "-g" "-O0" "-DDEBUG")
    
    target_link_options(kata1_basic_raii PRIVATE ${SANITIZER_FLAGS})
    target_link_options(kata2_smart_pointers PRIVATE ${SANITIZER_FLAGS})
    target_link_options(kata3_advanced_move PRIVATE ${SANITIZER_FLAGS})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(kata1_basic_raii PRIVATE "-O3" "-DNDEBUG" "-DRELEASE")
    target_compile_options(kata2_smart_pointers PRIVATE "-O3" "-DNDEBUG" "-DRELEASE")
    target_compile_options(kata3_advanced_move PRIVATE "-O3" "-DNDEBUG" "-DRELEASE")
else()
    target_compile_options(kata1_basic_raii PRIVATE "-O2" "-g" "-DNDEBUG")
    target_compile_options(kata2_smart_pointers PRIVATE "-O2" "-g" "-DNDEBUG")
    target_compile_options(kata3_advanced_move PRIVATE "-O2" "-g" "-DNDEBUG")
endif()

# Function to set common properties for all targets
function(set_kata_properties target_name)
    set_target_properties(${target_name} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        # Enable colored output for better readability
        CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always"
    )
    
    # Add sanitizer-specific properties for debug builds
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target_name} PRIVATE
            # Additional debugging flags
            -fno-omit-frame-pointer     # Keep frame pointers for better stack traces
            -fno-optimize-sibling-calls # Disable tail call optimization for cleaner traces
        )
    endif()
endfunction()

# Apply common properties to all kata targets
set_kata_properties(kata1_basic_raii)
set_kata_properties(kata2_smart_pointers)
set_kata_properties(kata3_advanced_move)

# Add clang-tidy checks (optional but recommended)
find_program(CLANG_TIDY_EXE NAMES "clang-tidy-20" "clang-tidy")
if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
    
    # Educational-friendly clang-tidy configuration
    set(CLANG_TIDY_CHECKS
        "bugprone-*"                                # Enable bug-prone patterns
        "modernize-*"                               # Enable modernization suggestions
        "performance-*"                             # Enable performance checks
        "readability-*"                             # Enable readability checks
        "cppcoreguidelines-*"                       # Enable C++ Core Guidelines
        "-modernize-use-trailing-return-type"       # Allow traditional function syntax
        "-readability-magic-numbers"                # Allow magic numbers in examples
        "-readability-identifier-length"            # Allow short variable names in examples
        "-cppcoreguidelines-avoid-magic-numbers"    # Allow magic numbers in kata code
        "-cppcoreguidelines-prefer-member-initializer" # Allow assignment in constructor body for clarity
        "-misc-non-private-member-variables-in-classes" # Allow public members in examples
        "-google-readability-todo"                  # Allow TODO comments without usernames
        "-misc-include-cleaner"                     # Don't require explicit includes for examples
        "-performance-avoid-endl"                   # Allow std::endl in educational code
        "-misc-const-correctness"                   # Allow non-const variables for learning
        "-misc-use-internal-linkage"                # Allow global functions in kata files
    )
    
    string(JOIN "," CLANG_TIDY_CHECKS_STR ${CLANG_TIDY_CHECKS})
    
    set_target_properties(kata1_basic_raii PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=${CLANG_TIDY_CHECKS_STR}"
    )
    set_target_properties(kata2_smart_pointers PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=${CLANG_TIDY_CHECKS_STR}"
    )
    set_target_properties(kata3_advanced_move PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=${CLANG_TIDY_CHECKS_STR}"
    )
else()
    message(WARNING "clang-tidy not found - static analysis disabled")
endif()

# Add clang-format support (optional)
find_program(CLANG_FORMAT_EXE NAMES "clang-format-20" "clang-format")
if(CLANG_FORMAT_EXE)
    message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")
    
    # Create format target for all source files
    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp *.h)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting all source files with clang-format"
        VERBATIM
    )
else()
    message(WARNING "clang-format not found - code formatting target disabled")
endif()

# Print build configuration summary
message(STATUS "=== C++ Kata Build Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Compile commands export: ${CMAKE_EXPORT_COMPILE_COMMANDS}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Sanitizers enabled: AddressSanitizer, UBSan, LeakSanitizer")
    message(STATUS "Extra debugging: Frame pointers, detailed stack traces")
endif()

message(STATUS "Warning flags: Enhanced (-Wall -Wextra + 15 additional checks)")
message(STATUS "==========================================")

# Add usage target to show available targets
add_custom_target(usage
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Available targets:"
    COMMAND ${CMAKE_COMMAND} -E echo "  kata1_basic_raii     - Build and run RAII kata"
    COMMAND ${CMAKE_COMMAND} -E echo "  kata2_smart_pointers - Build and run smart pointer kata"
    COMMAND ${CMAKE_COMMAND} -E echo "  kata3_advanced_move  - Build and run advanced move semantics kata"
    COMMAND ${CMAKE_COMMAND} -E echo "  format               - Format all source files with clang-format"
    COMMAND ${CMAKE_COMMAND} -E echo "  usage                - Show this help message"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Build modes:"
    COMMAND ${CMAKE_COMMAND} -E echo "  Debug (default)      - With sanitizers, full warnings, debug info"
    COMMAND ${CMAKE_COMMAND} -E echo "  Release              - Optimized, no sanitizers"
    COMMAND ${CMAKE_COMMAND} -E echo "  RelWithDebInfo       - Optimized but with debug info"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    VERBATIM
)
