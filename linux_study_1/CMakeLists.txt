# CMakeList.txt : CMake project for linux_study_1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (linux_study_1 "linux_study_1.cpp" "linux_study_1.h")
 
# if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET linux_study_1 PROPERTY CXX_STANDARD 20)
# endif()

cmake_minimum_required(VERSION 3.28)
project(linux_study_1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(server server.cpp)


# TODO: Add tests and install targets if needed.
