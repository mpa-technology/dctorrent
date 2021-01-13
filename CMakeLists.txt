cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(dctorrent CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

file(GLOB SOURCE "src/*.cpp")


add_executable( ${PROJECT_NAME} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} -lstdc++ -lboost_system -lboost_locale -ltorrent-rasterbar -lpthread  )


target_include_directories( ${PROJECT_NAME} PUBLIC include/)

if(WIN32)

    target_link_libraries( ${PROJECT_NAME} ws2_32 -liconv )

endif()



