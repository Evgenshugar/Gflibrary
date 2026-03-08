#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "BookManager.h"
#include "AdminManager.h"
#include <SFML/Graphics.hpp>

class UserInterface {
private:
    sf::RenderWindow window;
    BookManager bookManager;
    AdminManager adminManager;
    enum class State { MAIN_MENU, READER_MODE, ADMIN_LOGIN, ADMIN_MODE, VIEW_BOOKS, VIEW_CHAPTERS, VIEW_CHAPTER };
    State currentState;
    std::string selectedBookId;
    std::string selectedChapterId;

    // UI элементы
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> texts;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void drawMainMenu();
    void drawReaderMode();
    void drawAdminLogin();
    void drawAdminMode();
    void drawBooksList();
    void drawChaptersList();
    void drawChapterContent();

public:
    UserInterface();
    void run();
    void handleEvents();
};

#endif
