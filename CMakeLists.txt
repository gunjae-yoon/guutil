cmake_minimum_required(VERSION 3.20)
project(guutil CXX)

##########################################################################
# general settings
##########################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fpermissive)

set(BUILD_LIB "Build guutil library" ON)
set(BUILD_TEST "Build test application" OFF)

if (BUILD_LIB)
	##########################################################################
	# automatic code generations
	##########################################################################
	set(GEN_SRC
		${PROJECT_SOURCE_DIR}/src/guutil/version.cpp
	)
	add_custom_command(
		OUTPUT ${GEN_SRC}
		COMMAND bash "${PROJECT_SOURCE_DIR}/script/version.sh"
		COMMENT "Try to update version"
	)
	add_custom_target(GEN_TARGET DEPENDS ${GEN_SRC})

	##########################################################################
	# build guutil library
	##########################################################################
	set(TARGET_LIB "guutil")
	add_library(${TARGET_LIB} SHARED
		${GEN_SRC}
		src/guutil/memory/memorymanager.cpp
		src/guutil/memory/impl/buddy.cpp
	)
	add_dependencies(${TARGET_LIB} GEN_TARGET)
	target_include_directories(${TARGET_LIB} PRIVATE
		include
		src
	)
endif ()

if (BUILD_TEST)
	##########################################################################
	# build test application
	##########################################################################
	set(TARGET_APP "test")
	add_executable(${TARGET_APP}
		src/app/main.cpp
	)
	target_include_directories(${TARGET_APP} PRIVATE
		include
	)
	target_link_libraries(${TARGET_APP} PRIVATE
		guutil
	)
endif ()
