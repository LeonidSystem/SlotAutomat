cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(slotAutomat)

find_package(SFML COMPONENTS graphics window system)

add_executable(slotAutomat slotAutomat.cpp RenderHelper/RenderHelper.cpp States/StartState/StartState.cpp States/SpinState/SpinState.cpp States/StopState/StopState.cpp States/StateMachine/StateMachine.cpp)

target_link_libraries(slotAutomat sfml-graphics sfml-window sfml-system)