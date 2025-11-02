# 1. Versiunea minimă de CMake
cmake_minimum_required(VERSION 3.10)

# 2. Definirea Proiectului (pentru a elimina Avertismentele)
project(MagazinCDuri CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(PROJECT_SOURCES
        main.cpp
        CD.cpp
        CLIENT.cpp
        COMANDA.cpp
        MAGAZIN.cpp
        ADRESA.cpp
        ADRESA.h

)


add_executable(MagazinCDuri_app ${PROJECT_SOURCES})