cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(openmp-pixelmatch VERSION 0.1.0 LANGUAGES C CXX)

# Option to enable or disable OpenMP
option(ENABLE_OPENMP "Enable OpenMP support" ON)

if(ENABLE_OPENMP)
    # Find OpenMP (optional)
    find_package(OpenMP QUIET)
    if(OpenMP_FOUND)
        message(STATUS "Found OpenMP, enabling parallel code.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    else()
        message(STATUS "OpenMP not found, parallel code will not be enabled.")
    endif()
else()
    message(STATUS "OpenMP support is disabled.")
endif()

set(MAIN_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/benchmark1.cpp
)

add_executable(openmp-pixelmatch ${MAIN_SRC})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(ENABLE_OPENMP)
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "openmp-pixelmatch-openmp-debug")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "openmp-pixelmatch-non-openmp-debug")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(ENABLE_OPENMP)
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "openmp-pixelmatch-openmp-release")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "openmp-pixelmatch-non-openmp-release")
    endif()
else()
    if(ENABLE_OPENMP)
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "openmp-pixelmatch-openmp")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "openmp-pixelmatch-non-openmp")
    endif()
endif()
