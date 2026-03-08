#include "AdminManager.h"

AdminManager::AdminManager(BookManager& manager) : bookManager(manager), isAuthenticated(false) {}

bool AdminManager::authenticate(const std::string& password) {
    if (password == ADMIN_PASSWORD) {
        isAuthenticated = true;
        return true;
    }
    return false;
}

bool AdminManager::isAdminAuthenticated() const {
    return isAuthenticated;
}

bool AdminManager::addNewBook(const std::string& title, const std::string& description,
                           const std::string& coverPath) {
    if (!isAuthenticated) return false;

    Book book;
    book.id = "book_" + std::to_string(books.size() + 1);
    book.title = title;
    book.description = description;
    book.coverPath = coverPath;

    return bookManager.addBook(book);
}

bool AdminManager::editBook(const std::string& bookId, const std::string& title,
                         const std::string& description) {
    if (!isAuthenticated || books.find(bookId) == books.end()) return false;

    auto& book = books[bookId];
    book.title = title;
    book.description = description;

    bookManager.saveData();
    return true;
}

bool AdminManager::addNewChapter(const std::string& bookId, const std::string& title) {
    if (!isAuthenticated || books.find(bookId) == books.end()) return false;

    Chapter chapter;
    chapter.id = "chapter_" + std::to_string(chapters.size() + 1);
    chapter.title = title;
    chapter.textPath = "data/books/" + bookId + "/chapter_" +
                     std::to_string(chapters.size() + 1) + ".txt";

    return bookManager.addChapter(chapter, bookId);
}

bool AdminManager::editChapter(const std::string& chapterId, const std::string& title) {
    if (!isAuthenticated || chapters.find(chapterId) == chapters.end()) return false;

    auto& chapter = chapters[chapterId];
    chapter.title = title;

    bookManager.saveData();
    return true;
}
