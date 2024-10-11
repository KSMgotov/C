cmake_minimum_required(VERSION 3.23)
project(Parser LANGUAGES CXX)

add_library(stack INTERFACE)
target_sources(stack INTERFACE 
    FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES "Stack.h" "my_exception.h")
add_subdirectory("Stack")
add_executable(ParserTest)
target_sources(ParserTest PRIVATE ParserTest.cpp Lexer.h Lexer.cpp Parser.h Parser.cpp)
target_link_libraries(ParserTest PRIVATE stack)

install(TARGETS stack FILE_SET HEADERS)