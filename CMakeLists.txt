cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(verySmallCompiler)

execute_process(COMMAND pip show pylint
    RESULT_VARIABLE PIP_PYLING
    OUTPUT_QUIET
)

execute_process(COMMAND pip show autopep8
    RESULT_VARIABLE PIP_AUTOPEP8
    OUTPUT_QUIET
)

if(NOT PIP_PYLING EQUAL 0 AND NOT PIP_AUTOPEP8 EQUAL 0)
    execute_process(COMMAND pip install pylint autopep8)
endif()

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
