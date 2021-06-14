cmake_minimum_required(VERSION 3.16.3)
project(sde-test-solution)

set(CMAKE_CXX_STANDARD 20)

add_executable(sde-test-solution main.cpp Bond.cpp)

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(sde-test-solution PRIVATE nlohmann_json::nlohmann_json)




