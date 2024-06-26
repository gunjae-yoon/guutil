cmake_minimum_required(VERSION 3.20)
project(guutil VERSION 0.1.2 LANGUAGES CXX)

##########################################################################
# general settings
##########################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fpermissive)

option(BUILD_LIB "Build guutil library" ON)
option(BUILD_TEST "Build test application" OFF)

message("==================================================")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Build guutil library: ${BUILD_LIB}")
message(STATUS "Build test application: ${BUILD_TEST}")
message("==================================================")

if (BUILD_LIB)
	##########################################################################
	# automatic code generations
	##########################################################################
	set(GEN_SRC
		${PROJECT_SOURCE_DIR}/src/guutil/version.cpp
	)
	if (NOT TARGET guutil_GETN_TARGET)
		add_custom_command(
			OUTPUT ${GEN_SRC}
			COMMAND bash "${PROJECT_SOURCE_DIR}/script/version.sh"
			COMMENT "Try to update version"
		)
		add_custom_target(guutil_GEN_TARGET DEPENDS ${GEN_SRC})
	endif()

	##########################################################################
	# build guutil library
	##########################################################################
	set(TARGET_LIB "guutil")
	add_library(${TARGET_LIB} SHARED
		${GEN_SRC}
		src/guutil/io/console.cpp
		src/guutil/io/file.cpp
		src/guutil/log/logger.cpp
		src/guutil/log/stringify.cpp
		src/guutil/memory/memorymanager.cpp
		src/guutil/memory/impl/buddy.cpp
		src/guutil/memory/impl/memorymanager_impl.cpp
		src/guutil/memory/impl/plain.cpp
		src/guutil/process/named_mutex.cpp
	)
	add_dependencies(${TARGET_LIB} guutil_GEN_TARGET)
	target_include_directories(${TARGET_LIB} PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
		PRIVATE src
	)
	set_target_properties(${TARGET_LIB} PROPERTIES
		EXPORT_NAME guutil
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}
	)

	##########################################################################
	# settings for make install
	##########################################################################
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include
		FILES_MATCHING PATTERN "*.h"
	)
	install(
		TARGETS ${TARGET_LIB}
		EXPORT guutilTargets
		LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
	)
	install(EXPORT guutilTargets
		FILE guutilTargets.cmake
		NAMESPACE guutil::
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/guutil
	)
	
	include(CMakePackageConfigHelpers)
	write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/guutilConfigVersion.cmake"
		VERSION ${PROJECT_VERSION}
		COMPATIBILITY AnyNewerVersion
	)
	configure_package_config_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/script/config.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/guutilConfig.cmake"
		INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/guutil
	)

	install(FILES
		"${CMAKE_CURRENT_BINARY_DIR}/guutilConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/guutilConfigVersion.cmake"
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/guutil
	)
	
	install(CODE "
		file(APPEND \"${CMAKE_INSTALL_PREFIX}/guutil.install_manifest.txt\" \"${CMAKE_INSTALL_PREFIX}/include/\n\")
		file(GLOB_RECURSE headers \"${PROJECT_SOURCE_DIR}/include/*.h\")
		foreach(header \${headers})
			file(RELATIVE_PATH rel_header \"${PROJECT_SOURCE_DIR}\" \${header})
			file(APPEND \"${CMAKE_INSTALL_PREFIX}/guutil.install_manifest.txt\" \"${CMAKE_INSTALL_PREFIX}/\${rel_header}\n\")
		endforeach()
		file(APPEND \"${CMAKE_INSTALL_PREFIX}/guutil.install_manifest.txt\" \"${CMAKE_INSTALL_PREFIX}/lib/lib${TARGET_LIB}.so\n\")
	")
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/script/cmake_uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
		IMMEDIATE @ONLY
	)
	add_custom_target(uninstall
		COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
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

