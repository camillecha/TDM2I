#--------------------------------------------
#         CamiTK Extension Project
#--------------------------------------------
cmake_minimum_required(VERSION 3.0)

# Find CamiTK SDK
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
find_package(CamiTK REQUIRED)
include(${CAMITK_USE_FILE})

# This extension is C++11 compliant
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(CTest)
enable_testing()

# to create specific target: camitk-test-coverage
option(CAMITK_TEST_COVERAGE "Code coverage" OFF)
include(macros/camitk/test/CamiTKTestCoverage)

# define the CEP
camitk_extension_project(NAME "Mesh Projection" 
                         CONTACT "Emmanuel.Promayon@imag.fr"
                         DESCRIPTION "Mesh projection on 2D slices"
                         ENABLED
)



