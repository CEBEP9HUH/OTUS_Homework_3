cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.42)
endif()

configure_file(description.json.in description.json)

set(INCLUDE_FOLDER ${CMAKE_BINARY_DIR}/../include)
include_directories(${INCLUDE_FOLDER})

set(SOURCE_FOLDER ${CMAKE_BINARY_DIR}/../source)
add_executable(allocator ${SOURCE_FOLDER}/main.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
else()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
