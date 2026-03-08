#include "BookManager.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

BookManager::BookManager() {
    loadData();
}

std::vector<Book> BookManager::getBooksList() const {
    std::vector<Book> result;
    for (const auto& pair : books) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<Chapter> BookManager::getChaptersForBook(const std::string& bookId) const {
    std::vector<Chapter> result;
    const auto& book = books.at(bookId);
    for (const auto& chapterId : book.chapters) {
        if (chapters.find(chapterId) != chapters.end()) {
            result.push_back(chapters.at(chapterId));
        }
    }
    return result;
}

std::string BookManager::getChapterText(const std::string& chapterId) const {
    if (chapters.find(chapterId) == chapters.end()) return "";
    const auto& chapter = chapters.at(chapterId);

    std::ifstream file(chapter.textPath);
    if (!file.is_open()) return "Ошибка загрузки текста главы";

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> BookManager::getChapterImages(const std::string& chapterId) const {
    if (chapters.find(chapterId) == chapters.end()) return {};
    return chapters.at(chapterId).images;
}

bool BookManager::addBook(const Book& book) {
    books[book.id] = book;
    saveData();
    return true;
}

bool BookManager::addChapter(const Chapter& chapter, const std::string& bookId) {
    chapters[chapter.id] = chapter;
    books[bookId].chapters.push_back(chapter.id);
    saveData();
    return true;
}

void BookManager::loadData() {
    // Загрузка данных из JSON файла
    std::ifstream file("data/config.json");
    if (file.is_open()) {
        json data;
        file >> data;

        // Загрузка книг
        if (data.contains("books")) {
            for (const auto& jbook : data["books"]) {
                Book book;
                book.id = jbook["id"];
                book.title = jbook["title"];
                book.description = jbook.value("description", "");
                book.coverPath = jbook["coverPath"];
                for (const auto& chId : jbook["chapters"]) {
                    book.chapters.push_back(chId);
                }
                books[book.id] = book;
            }
        }

        // Загрузка глав
        if (data.contains("chapters")) {
            for (const auto& jchapter : data["chapters"]) {
                Chapter chapter;
                chapter.id = jchapter["id"];
                chapter.title = jchapter["title"];
                chapter.textPath = jchapter["textPath"];
                for (const auto& img : jchapter["images"]) {
                    chapter.images.push_back(img);
                }
                chapters[chapter.id] = chapter;
            }
        }
    }
}

void BookManager::saveData() {
    json data;

       // Сохранение книг
    for (const auto& [id, book] : books) {
        json jbook;
        jbook["id"] = book.id;
        jbook["title"] = book.title;
        jbook["description"] = book.description;
        jbook["coverPath"] = book.coverPath;
        for (const auto& chId : book.chapters) {
            jbook["chapters"].push_back(chId);
        }
        data["books"].push_back(jbook);
    }

    // Сохранение глав
    for (const auto& [id, chapter] : chapters) {
        json jchapter;
        jchapter["id"] = chapter.id;
        jchapter["title"] = chapter.title;
        jchapter["textPath"] = chapter.textPath;
        for (const auto& imgPath : chapter.images) {
            jchapter["images"].push_back(imgPath);
        }
        data["chapters"].push_back(jchapter);
    }

    // Запись в файл
    std::ofstream outFile("data/config.json");
    if (outFile.is_open()) {
        outFile << data.dump(4); // 4 — отступ для читаемости
        outFile.close();
    } else {
        // Обработка ошибки записи
        std::cerr << "Ошибка: не удалось сохранить данные в файл data/config.json" << std::endl;
    }
}
