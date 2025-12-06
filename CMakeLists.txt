cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
# CRITICAL FIX: The executable name is explicitly and correctly defined.
set(MAIN_EXECUTABLE_NAME "MagazinCDuri_app")

project(${MAIN_PROJECT_NAME})

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
set(FETCHCONTENT_UPDATES_DISCONNECTED OFF)

# 1. nlohmann/json (Robust, header-only JSON library)
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        GIT_SHALLOW    1
)
FetchContent_MakeAvailable(nlohmann_json)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)

###############################################################################

set(SOURCE_CLASSES_CPP
        CD.cpp
        CLIENT.cpp
        COMANDA.cpp
        COS_CUMPARATURI.cpp
        CASETA.cpp
        MAGAZIN.cpp
        MERCHANDISE.cpp
        PRODUSMUZICAL.cpp
        VINIL.cpp
)

set(HEADER_FILES
        CD.h
        CLIENT.h
        COMANDA.h
        COS_CUMPARATURI.h
        CASETA.h
        EroriMuzicale.h
        MAGAZIN.h
        MERCHANDISE.h
        PRODUSMUZICAL.h
        VINIL.h
)

# NOTE: Am inclus main.cpp doar o singură dată aici, plus toate fișierele .cpp
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        ${SOURCE_CLASSES_CPP}
)


###############################################################################
## 🔗 Linking for Main Application
###############################################################################

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