cmake_minimum_required(VERSION 3.26)


project(MagazinCDuri CXX)

set(CMAKE_CXX_STANDARD 17)


set(MAIN_PROJECT_NAME "MagazinCDuri_app")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

set(MAIN_EXECUTABLE_NAME MagazinCDuri_app)

# Executabilul principal al aplicației (fără fișierul de test)
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
        MERCHANDISE.cpp
        MERCHANDISE.h
)


set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})


install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

