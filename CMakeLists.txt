cmake_minimum_required(VERSION 3.14)
project(TapeSorter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(tape_sorter
    src/main.cpp
    src/Config.cpp
    src/TapeFile.cpp
    src/Sorter.cpp)

target_include_directories(tape_sorter PRIVATE include)
target_link_libraries(
    tape_sorter PRIVATE
        nlohmann_json::nlohmann_json
        Threads::Threads
)