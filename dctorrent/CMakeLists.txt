project(dctorrent CXX)


set_target_properties(${TARGET} PROPERTIES
            CXX_STANDARD 17
            )

set(SOURCES
    "main.cpp"
    "TorrentFile.cpp"
    "Torrent.cpp"
    "Session.cpp"
    "TorrentService.cpp"
    "App.cpp"
    "InputOutputService.cpp"
    "Logger.cpp"
    )
set(HEADER
    "main.hpp"
    "TorrentFile.hpp"
    "Torrent.hpp"
    "Session.hpp"
    "TorrentService.hpp"
    "App.hpp"
    "InputOutputService.hpp"
    "Logger.hpp"
    )



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lstdc++ -lboost_system -ltorrent-rasterbar -lpthread -lboost_signals  )
