cmake_minimum_required(VERSION 3.11)

project(PekingExpressProject VERSION 1.0
                  DESCRIPTION "PekingExpress assignment"
                  LANGUAGES CXX)

set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
include_directories("${CMAKE_SOURCE_DIR}/include"
					"./include")

# version information
if(NOT DEFINED PekingExpressProject_VERSION_MAJOR)
  set(PekingExpressProject_VERSION_MAJOR 1)
endif()
if(NOT DEFINED PekingExpressProject_VERSION_MINOR)
  set(PekingExpressProject_VERSION_MINOR 0)
endif()
if(NOT DEFINED PekingExpressProject_VERSION_PATCH)
  set(PekingExpressProject_VERSION_PATCH 0)
endif()

add_subdirectory(lib)
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
	find_package(GTest)
	if (GTEST_FOUND)
		enable_testing()
		add_subdirectory(tests)
	else()
		enable_testing()
		include(GoogleTest)
		add_subdirectory(tests)
	endif()
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")