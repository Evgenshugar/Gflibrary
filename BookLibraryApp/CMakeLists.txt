cmake_minimum_required(VERSION 3.10)
project(BookLibraryApp)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(BookLibraryApp
    src/main.cpp
    src/UserInterface.cpp
    src/BookManager.cpp
    src/AdminManager.cpp
)

target_link_libraries(BookLibraryApp sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)

# Создание директорий данных
file(MAKE_DIRECTORY data)
file(MAKE_DIRECTORY data/books)
file(WRITE data/config.json "{}")
