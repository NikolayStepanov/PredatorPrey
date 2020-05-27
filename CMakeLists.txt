cmake_minimum_required(VERSION 3.5)

project(PredatorPrey LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set (HEADERS
    gamemodel.h
    fish.h
    shark.h
    amphiprion.h
    mediatorfishmotor.h
    gameboard.h
    common.h
    cell.h
    objectgame.h
    rock.h
    generator.h
    )

set (SOURCES
    main.cpp
    gamemodel.cpp
    fish.cpp
    shark.cpp
    amphiprion.cpp
    mediatorfishmotor.cpp
    gameboard.cpp
    cell.cpp
    objectgame.cpp
    rock.cpp
    generator.cpp
    )

set (RESOURCES
    qml.qrc
    resource.qrc
    )

add_executable(PredatorPrey ${HEADERS} ${SOURCES} ${RESOURCES})

target_compile_definitions(PredatorPrey
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(PredatorPrey
  PRIVATE Qt5::Core Qt5::Quick)
