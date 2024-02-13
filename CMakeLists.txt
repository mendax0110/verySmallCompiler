cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(verySmallCompiler)

set(HEADER_FILES
    ./src/includes/emitter.h
    ./src/includes/lexer.h
    ./src/includes/parser.h
    ./src/includes/tokenizer.h
)

set(SOURCE_FILES
    ./src/emitter.cpp
    ./src/lexer.cpp
    ./src/main.cpp
    ./src/parser.cpp
    ./src/tokenizer.cpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
