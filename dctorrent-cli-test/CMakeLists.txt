project(dctorrent-cli-test CXX)


set_target_properties(${TARGET} PROPERTIES
            CXX_STANDARD 17
            )

set(SOURCES
    "main.cpp"
    "../dctorrent-cli/App.cpp"
    )
set(HEADER

    )



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lstdc++ -lboost_system  -lpthread -lboost_signals -lgtest -lgtest_main)
