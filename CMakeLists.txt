cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
  SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

# TODO: rename project and delete this comment
project(template)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(gumbo)
find_package(gumbo CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS thread program_options)
find_package(Boost CONFIG REQUIRED thread program_options)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

hunter_add_package(Beast)
find_package(Beast CONFIG REQUIRED)

# TODO: change template word to project name and delete this comment
add_library(template STATIC
  # enum your files and delete this comment
        sources/main.cpp
        #sources/crawler.cpp
        #include/crawler.hpp
        #sources/downloader.cpp
        #include/downloader.hpp
        #sources/parser.cpp
        #include/parser.hpp
        include/root_certificates.hpp)
add_executable(tests
  # TODO: enum your files and delete this comment
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        sources/crawler.cpp
        include/crawler.hpp
        sources/downloader.cpp
        include/downloader.hpp
        sources/parser.cpp
        include/parser.hpp
        include/root_certificates.hpp)

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
        #sources/crawler.cpp
        #include/crawler.hpp
        #sources/downloader.cpp
        #include/downloader.hpp
        #sources/parser.cpp
        #include/parser.hpp
        include/root_certificates.hpp)

# TODO: change template word to project name and delete this comment
target_include_directories(template
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/ThreadPool
)
target_include_directories(tests
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/ThreadPool
)
target_link_directories(main
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/ThreadPool
        )
# TODO: change template word to project name and delete this comment
target_link_libraries(template
        GTest::gtest_main
        gumbo::gumbo
        OpenSSL::SSL
        Beast::Beast
        Boost::program_options
        Boost::thread)
target_link_libraries(tests
        GTest::gtest_main
        gumbo::gumbo
        OpenSSL::SSL
        Beast::Beast
        Boost::program_options
        Boost::thread
        template)
target_link_libraries(main
        gumbo::gumbo
        Beast::Beast
        OpenSSL::SSL
        Boost::program_options
        Boost::thread
        template)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if(BUILD_COVERAGE)
  function(ENABLE_PROJECT_COVERAGE PROJECT)
    target_compile_options(${PROJECT} PRIVATE --coverage)
    target_link_libraries(${PROJECT} --coverage)
    add_coverage(${PROJECT})
  endfunction()

  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  # TODO: change template word to project name and delete this comment
  enable_project_coverage(template)
  enable_project_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
