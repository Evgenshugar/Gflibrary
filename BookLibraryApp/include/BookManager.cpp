#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <string>
#include <vector>
#include <map>

struct Book {
    std::string id;
    std::string title;
    std::string description;
    std::string coverPath;
    std::vector<std::string> chapters; // IDs глав
};

struct Chapter {
    std::string id;
    std::string title;
    std::string textPath;
    std::vector<std::string> images; // Пути к изображениям
};

class BookManager {
private:
    std::map<std::string, Book> books;
    std::map<std::string, Chapter> chapters;

public:
    BookManager();
    std::vector<Book> getBooksList() const;
    std::vector<Chapter> getChaptersForBook(const std::string& bookId) const;
    std::string getChapterText(const std::string& chapterId) const;
    std::vector<std::string> getChapterImages(const std::string& chapterId) const;
    bool addBook(const Book& book);
    bool addChapter(const Chapter& chapter, const std::string& bookId);
    bool updateBook(const Book& book);
    bool updateChapter(const Chapter& chapter);
    bool deleteBook(const std::string& bookId);
    bool deleteChapter(const std::string& chapterId);
    void loadData();
    void saveData();
};

#endif
