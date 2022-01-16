cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
  SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
  LOCAL
)

# TODO: rename project and delete this comment
project(template VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(Beast)
find_package(Beast CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS  thread filesystem)
find_package(Boost CONFIG REQUIRED thread filesystem)
find_package(Threads)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(${PROJECT_NAME} STATIC
  # enum your files and delete this comment
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
)
add_executable(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )

target_link_libraries(demo ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

if(BUILD_TESTS)
  add_executable(tests
    # TODO: enum your files and delete this comment
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
  )
  target_include_directories(tests
          PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
          )
  target_link_libraries(tests ${PROJECT_NAME}
          Beast::Beast
          Boost::filesystem
          Boost::thread
          GTest::gmock_main
          nlohmann_json::nlohmann_json)
  enable_testing()
  add_test(NAME unit_tests COMMAND tests)
endif()
