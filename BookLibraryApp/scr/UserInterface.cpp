#include "UserInterface.h"
#include <SFML/Graphics.hpp>

UserInterface::UserInterface()
    : window(sf::VideoMode(1200, 800), "Библиотека книг")
    , adminManager(bookManager)
    , currentState(State::MAIN_MENU) {

    // Настройка тёмной темы
    window.clear(sf::Color(40, 40, 40));

    // Загрузка фона (опционально)
    if (backgroundTexture.loadFromFile("assets/background.jpg")) {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

void UserInterface::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear(sf::Color(40, 40, 40)); // Тёмный фон

        switch (currentState) {
            case State::MAIN_MENU:
                drawMainMenu();
                break;
            case State::READER_MODE:
                drawBooksList();
                break;
            case State::ADMIN_LOGIN:
                drawAdminLogin();
                break;
            case State::ADMIN_MODE:
                drawAdminMode();
                break;
            case State::VIEW_BOOKS:
                drawBooksList();
                break;
            case State::VIEW_CHAPTERS:
                drawChaptersList();
                break;
            case State::VIEW_CHAPTER:
                drawChapterContent();
                break;
        }

        window.display();
    }
}

void UserInterface::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // Обработка нажатий кнопок и навигации
        // Здесь должна быть логика переключения между состояниями
    }
}

// Остальные методы draw* требуют детальной проработки UI элементов
