cmake_minimum_required(VERSION 3.16)
project(Platformer-Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CPP src/Action.cpp src/Animation.cpp src/Assets.cpp src/Entity.cpp 
    src/EntityManager.cpp src/GameEngine.cpp src/main.cpp src/Physics.cpp 
    src/Scene_InGame.cpp src/Scene_Menu.cpp src/Scene.cpp src/Vec2.cpp)


set(H src/Action.h src/Animation.h src/Assets.h src/Entity.h 
    src/EntityManager.h src/GameEngine.h src/Component.h src/Physics.h 
    src/Scene_InGame.h src/Scene_Menu.h src/Scene.h src/Vec2.h)

add_executable(main ${CPP} ${H})
target_link_libraries(main PRIVATE sfml-graphics sfml-audio )
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
