cmake_minimum_required(VERSION 3.10)
project(SlotMachine_OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "C:/Users/aidat/source/repos/Test_task_Octavian_Gaming/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Находим библиотеки OpenGL и GLUT
set(GLUT_INCLUDE_DIR "C:/Users/aidat/source/repos/Test_task_Octavian_Gaming/vcpkg/installed/x64-windows/include")
set(GLUT_LIBRARY "C:/Users/aidat/source/repos/Test_task_Octavian_Gaming/vcpkg/installed/x64-windows/lib/freeglut.lib")

include_directories(${GLUT_INCLUDE_DIR})
link_directories("C:/Users/aidat/source/repos/Test_task_Octavian_Gaming/vcpkg/installed/x64-windows/lib")

find_package(OpenGL REQUIRED)


# Указываем исходные файлы
set(SOURCES
    src/main.cpp
    src/SlotMachine.cpp
    src/TextUtils.cpp
    src/Button.cpp
    src/Reel.cpp
    src/StateMachine.cpp
    src/States/IdleState.cpp
    src/States/SpinningState.cpp
    src/States/WinState.cpp
  )

# Создаем исполняемый файл
add_executable(SlotMachine ${SOURCES} "src/Vec2.h")
target_include_directories(SlotMachine PRIVATE src)
target_link_libraries(SlotMachine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


