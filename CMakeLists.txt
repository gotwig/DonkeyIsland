

    cmake_minimum_required(VERSION 3.3)

    project(thirdsemestergame)
    set(CMAKE_CXX_STANDARD 14)

    set(SOURCE_FILES
            thirdsemestergame/brick.h
            thirdsemestergame/AnimatedSprite.cpp
            thirdsemestergame/AnimatedSprite.hpp
            thirdsemestergame/Animation.cpp
            thirdsemestergame/Animation.hpp
            thirdsemestergame/gamescene.cpp
            thirdsemestergame/gamescene.h
            thirdsemestergame/Header.h
            thirdsemestergame/Inventory.cpp
            thirdsemestergame/Inventory.h
            thirdsemestergame/lake_grass.h
            thirdsemestergame/main.cpp
            thirdsemestergame/main.h
            thirdsemestergame/Quests.cpp
            thirdsemestergame/Quests.h
            thirdsemestergame/tinyxml2.cpp
            thirdsemestergame/tinyxml2.h
            thirdsemestergame/lake_grass.cpp thirdsemestergame/house.cpp thirdsemestergame/house.h)


    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
    find_package(SFML 2 REQUIRED system window graphics network audio)

    add_executable(thirdsemestergame ${SOURCE_FILES})
    target_link_libraries(thirdsemestergame ${SFML_LIBRARIES})
    target_include_directories(thirdsemestergame PRIVATE thirdsemestergame/tinyxml2)