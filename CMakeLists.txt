cmake_minimum_required(VERSION 3.26)


set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "MagazinCDuri_app")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)


include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED OFF)


FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        GIT_SHALLOW    1
)
FetchContent_MakeAvailable(nlohmann_json)


find_package(Threads REQUIRED)


set(SOURCE_FILES
        main.cpp
        CLIENT.cpp
        CD.cpp
        COMANDA.cpp
        MAGAZIN.cpp
        PRODUSMUZICAL.cpp
        VINIL.cpp
        CASETA.cpp
        COS_CUMPARATURI.cpp
        MERCHANDISE.cpp
        COMANDALIVRARE.cpp
        COMANDALIVRARE.h
)


add_executable(${MAIN_EXECUTABLE_NAME} ${SOURCE_FILES})


target_link_libraries(${MAIN_EXECUTABLE_NAME}
        nlohmann_json::nlohmann_json
        Threads::Threads
)


install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})


copy_files(FILES comenzi.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()