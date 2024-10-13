cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("bm2")

if (WIN32)
	set(glfw3_DIR vcpkg_installed/x64-windows/share/glfw3)
endif()

find_package(OpenGL)
find_package(glfw3 REQUIRED)

add_subdirectory( include/glm )

# all the source folders
aux_source_directory (source src_files)
aux_source_directory (gameasm gameasm_files)

add_library (gameasm SHARED ${gameasm_files})
add_executable (bm2 ${src_files})
target_include_directories( bm2 PRIVATE include/glm )

if (!WIN32)
	target_link_libraries (bm2 glfw3)
else()
	target_link_directories (bm2 PRIVATE vcpkg_installed/x64-windows/lib)
	target_link_libraries (bm2 glfw3dll)
endif()

target_link_libraries (bm2 gameasm)
target_include_directories (bm2 PRIVATE gameasm)

if (WIN32)
	target_include_directories (bm2 PRIVATE vcpkg_installed/x64-windows/include)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET bm2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
