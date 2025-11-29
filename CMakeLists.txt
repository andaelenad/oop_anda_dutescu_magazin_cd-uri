
cmake_minimum_required(VERSION 3.10)


project(MagazinCDuri CXX)


set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.26)

# Uniformizam numele proiectului si executabilului la cel vazut in log-uri: MagazinCDuri_app
set(MAIN_PROJECT_NAME "MagazinCDuri_app")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# Setam numele executabilului la cel corect
set(MAIN_EXECUTABLE_NAME MagazinCDuri_app)

# CORECTIE ESENTIALA: Adaugam TOATE fisierele sursa folosite pentru a crea executabilul
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        CLIENT.cpp
        CD.cpp
        COMANDA.cpp
        MAGAZIN.cpp
        PRODUSMUZICAL.cpp
        PRODUSMUZICAL.h
        VINIL.cpp
        VINIL.h
        CASETA.cpp
        CASETA.h
        COS_CUMPARATURI.cpp
        COS_CUMPARATURI.h
        EroriMuzicale.h
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${MAIN_EXECUTABLE_NAME} <SomeLib>)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})