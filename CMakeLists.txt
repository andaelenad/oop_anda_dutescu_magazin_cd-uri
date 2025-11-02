
cmake_minimum_required(VERSION 3.10)


project(MagazinCDuri CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(PROJECT_SOURCES
        main.cpp
        CD.cpp
        CLIENT.cpp
        COMANDA.cpp
        MAGAZIN.cpp


)


add_executable(MagazinCDuri_app ${PROJECT_SOURCES})