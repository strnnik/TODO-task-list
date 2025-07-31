cmake_minimum_required(VERSION 3.10)
project(002-RAM)
set(CMAKE_CXX_STANDARD 11)
# Явно указываем необходимость pthread
find_package(Threads REQUIRED)
add_executable(002-RAM main.cpp)

# Добавляем линковку с pthread
target_link_libraries(002-RAM PRIVATE Threads::Threads)
