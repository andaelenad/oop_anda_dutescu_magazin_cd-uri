cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
# CRITICAL FIX: The executable name is explicitly and correctly defined.
set(MAIN_EXECUTABLE_NAME "MagazinCDuri_app")

project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# external dependencies with FetchContent
include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
# FIX: Set to OFF to allow downloading dependencies on the first run.
set(FETCHCONTENT_UPDATES_DISCONNECTED OFF)

# ELIMINAT: Google Test

# 1. nlohmann/json (Robust, header-only JSON library)
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)
FetchContent_MakeAvailable(nlohmann_json)


# NOTE: Also update env vars used for caching in
#         - .github/actions/configure-cmake/action.yml
#         - .github/workflows/cmake.yml
# FetchContent_Declare(
#         SomeLib
#         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
# )
#
# FetchContent_MakeAvailable(SomeLib)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)

###############################################################################


set(SOURCE_CLASSES_CPP
        CLIENT.cpp
        CD.cpp
        COMANDA.cpp
        MAGAZIN.cpp
        PRODUSMUZICAL.cpp
        VINIL.cpp
        CASETA.cpp
        COS_CUMPARATURI.cpp
        MERCHANDISE.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
)


set(HEADER_FILES
        PRODUSMUZICAL.h
        VINIL.h
        CASETA.h
        COS_CUMPARATURI.h
        EroriMuzicale.h
        MERCHANDISE.h
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        ${SOURCE_CLASSES_CPP}
        ${HEADER_FILES}
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
)




# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME} run_tests)
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################
## 🔗 Linking for Main Application
###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)

# Linking nlohmann/json and Threads
target_link_libraries(${MAIN_EXECUTABLE_NAME}
        nlohmann_json::nlohmann_json
        Threads::Threads
)




# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6

if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES comenzi.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

