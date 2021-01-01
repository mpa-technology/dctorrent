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



add_executable(${PROJECT_NAME} src/main.cpp src/torrentinfo.cpp src/torrentnode.cpp src/torrentfile.cpp src/session.cpp src/app.cpp src/notimplementedexception.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lstdc++ -lboost_system -ltorrent-rasterbar -lpthread  )




if(WIN32)

    target_link_libraries( ${PROJECT_NAME} ws2_32)

endif()


target_include_directories (${PROJECT_NAME} PUBLIC include)
