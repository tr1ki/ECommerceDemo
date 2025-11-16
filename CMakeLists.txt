# ECommerceProject/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ECommerceDemo)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директорию 'include' в пути поиска
include_directories(include)

# Находим все исходные файлы в 'src'
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Создаем исполняемый файл из main.cpp и всех .cpp в src
add_executable(ECommerceDemo main.cpp ${SOURCES})

# Выводим сообщение о сборке
message(STATUS "Project configured for C++17")