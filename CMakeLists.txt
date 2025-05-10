include(FetchContent)
include(ExternalProject)
cmake_minimum_required (VERSION 3.8)
project ("aimp_yandexmusic")

set(CMAKE_DEBUG_OUTPUT ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

message(STATUS "Downloading yandex music api...")

FetchContent_Declare(ymcppapi
  GIT_REPOSITORY https://github.com/DrugsNotIncluded/yandex_music_cppapi
  GIT_TAG 50647c1
  GIT_SUBMODULES ""
  PATCH_COMMAND git apply ${CMAKE_SOURCE_DIR}/patches/fix_api_submodules.patch
  UPDATE_DISCONNECTED 1
)

FetchContent_MakeAvailable(ymcppapi)

message(STATUS "!!! READY: Yandex music api !!!")

file(GLOB_RECURSE SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/deps/
)

target_link_libraries("${PROJECT_NAME}" ymcppapi)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET aimp_yandexmusic PROPERTY CXX_STANDARD 20)
endif()