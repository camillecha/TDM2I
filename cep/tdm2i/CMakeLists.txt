#--------------------------------------------
#         CamiTK Extension Project
#--------------------------------------------
cmake_minimum_required(VERSION 3.0)

# Find CamiTK SDK
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(CamiTK REQUIRED)
include(${CAMITK_USE_FILE})

# define the CEP
camitk_extension_project(NAME "TDM2I" 
                         CONTACT "camille.chadenat@univ-grenoble-alpes.fr"
                         DESCRIPTION "Brainshift navigator"
                         ENABLED
)



