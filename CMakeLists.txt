cmake_minimum_required(VERSION 3.23)
project(Topic1Demo)

add_executable(Topic1Demo)

option(USE_ASAN "Use address sanitizer if available" OFF)
option(USE_UBSAN "Use undefined behavior sanitizer if available" OFF)
option(USE_CLANGTIDY "Use clang-tidy if available" OFF)
option(USE_CPPCHECK "Use Cppcheck if available" OFF)
option(GCC_ANALYZE "Use static analysis for gcc" OFF)

set(target Topic1Demo)

target_sources(${target}
        PRIVATE
        main.cpp
        raw_float.cpp)

target_compile_features(${target} PRIVATE cxx_std_23)
set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)

# Set options for gnu-like
target_compile_options(${target} PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor >
        # debug optimisation in Debug
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # O3 optimisation Release
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g -fno-omit-frame-pointer>
        # static gcc analyzer
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<BOOL:${GCC_ANALYZE}>>:-fanalyzer>
        )

if (USE_ASAN)
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
            OUTPUT_VARIABLE LIBASAN_PATH
            RESULT_VARIABLE ASAN_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(HAS_ASAN FALSE)

    if (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
        message("libasan found @${LIBASAN_PATH}")
        message("To disable the address sanitizer set USE_ASAN to OFF.\n")
        set(HAS_ASAN TRUE)
    endif ()

    if (HAS_ASAN AND USE_ASAN)
        target_compile_options(${target} PRIVATE -fsanitize=address -fsanitize-recover=address)
        target_link_options(${target} PRIVATE -fsanitize=address)
    endif ()
endif()


if (USE_UBSAN)

    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libubsan.so
            OUTPUT_VARIABLE LIBUBSAN_PATH
            RESULT_VARIABLE UBSAN_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(HAS_UBSAN FALSE)

    if (USE_UBSAN AND (${UBSAN_RESULT} EQUAL 0) AND (NOT ${LIBUBSAN_PATH} STREQUAL ""))
        message("libubsan found @${LIBUBSAN_PATH}")
        message("To disable the undefined behavior sanitizer set USE_UBSAN to OFF.\n")
        set(HAS_UBSAN TRUE)
    endif ()

    if (HAS_UBSAN AND USE_UBSAN)
        target_compile_options(${target} PRIVATE -fsanitize=undefined -fsanitize-recover=undefined)
        target_link_options(${target} PRIVATE -fsanitize=undefined)
    endif ()
endif()

if (USE_CPPCHECK)
    find_program(CPPCHECK NAMES cppcheck HINTS $ENV{PROGRAMFILES}/cppcheck)
    if(CPPCHECK AND NOT (CPPCHECK MATCHES "NOTFOUND"))
        message(STATUS "which cppcheck: ${CPPCHECK}")

        set(CPPCHECK_CMD "${CPPCHECK}"
                "--enable=all"
                "--inconclusive"
                "--inline-suppr"
                "--suppress=unmatchedSuppression"
                "--template='{file}:{line}: warning: {id} ({severity}): {message}'")

        set_target_properties(${target} PROPERTIES
                CXX_CPPCHECK "${CPPCHECK_CMD}"
                )
    endif()
endif(USE_CPPCHECK)

if (USE_CLANGTIDY)
    find_program(CLANGTIDY NAMES clang-tidy clang-tidy-14 clang-tidy-13 clang-tidy-12 clang-tidy-11)

    if(CLANGTIDY AND NOT (CLANGTIDY MATCHES "NOTFOUND"))
        message(STATUS "which clang-tidy: ${CLANGTIDY}")
        set_target_properties(${target} PROPERTIES
                CXX_CLANG_TIDY "${CLANGTIDY};-checks=-*,google-*,clang-analyzer-*,cppcoreguidelines-*,modernize-*,portability-*,readability-*"
                )
    endif()
endif(USE_CLANGTIDY)