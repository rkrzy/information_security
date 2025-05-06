cmake_minimum_required(VERSION 3.30)
project(information_security C)

set(CMAKE_C_STANDARD 11)

add_executable(information_security main.c Encryption.c Decryption.c Calculate.c)
