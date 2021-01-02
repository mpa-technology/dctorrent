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

include_directories(include/)

add_executable(${PROJECT_NAME} ${SOURCE} )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lstdc++ -lboost_system -lboost_locale -ltorrent-rasterbar -lpthread  )




if(WIN32)

    target_link_libraries( ${PROJECT_NAME} ws2_32 -liconv )

endif()



