###############################################################################
# Create static library -> executable liblaml
###############################################################################
add_library(laml STATIC)

file(GLOB_RECURSE laml_SRC CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE laml_INC CONFIGURE_DEPENDS "include/*.h")
set(laml_SRC 
	"src/vector2.cpp"
	"src/vector3.cpp"
	"src/vector4.cpp"
)

# print out source and header files
set(PRINT_FILES OFF)
if (PRINT_FILES)
    message(STATUS "Source files:")
    foreach(FILE_PATH IN LISTS laml_SRC)
    	file(RELATIVE_PATH STRIPPED_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE_PATH}")
    	message(STATUS "    ${STRIPPED_PATH}")
    endforeach()
    message(STATUS "Header files:")
    foreach(FILE_PATH IN LISTS laml_INC)
    	file(RELATIVE_PATH STRIPPED_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE_PATH}")
    	message(STATUS "    ${STRIPPED_PATH}")
    endforeach()
endif()

target_sources(laml
	PRIVATE 
		FILE_SET SOURCES
		BASE_DIRS src/
		FILES ${laml_SRC}
	PUBLIC  
		FILE_SET HEADERS 
		BASE_DIRS include
		FILES ${laml_INC})

target_compile_options(laml PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wno-unused-parameter -Wno-unused-variable -Wno-attributes -Wno-missing-designated-field-initializers)
target_include_directories(laml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/laml.config.h.in" 
    "${PROJECT_SOURCE_DIR}/laml/include/laml.config.h")

