cmake_minimum_required(VERSION 3.10)

# Установка имени проекта
project(TODO-task-list VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение каталогов с заголовочными файлами
include_directories(include)

# Поиск всех исходных файлов
file(GLOB SOURCES "src/*.cpp")

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} "include/BaseDashboard.h")

# Альтернативный вариант с явным указанием файлов (предпочтительнее)
# add_executable(${PROJECT_NAME} 
#     src/main.cpp
#     src/Date.cpp
#     src/Task.cpp
#     src/User.cpp
# )