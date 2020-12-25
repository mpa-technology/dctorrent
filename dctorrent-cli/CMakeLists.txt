project(dctorrent-cli CXX)


set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    )

set(SOURCES
    "main.cpp"
    "App.cpp"
    )
set(HEADER
    "App.hpp"
    )



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lstdc++ -lboost_system -ltorrent-rasterbar -lpthread -lboost_signals  )
