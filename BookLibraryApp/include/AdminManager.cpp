#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

#include "BookManager.h"

class AdminManager {
private:
    const std::string ADMIN_PASSWORD = "PIRET";
    bool isAuthenticated;
    BookManager& bookManager;

public:
    AdminManager(BookManager& manager);
    bool authenticate(const std::string& password);
    bool isAdminAuthenticated() const;
    bool addNewBook(const std::string& title, const std::string& description,
                   const std::string& coverPath);
    bool editBook(const std::string& bookId, const std::string& title,
                 const std::string& description);
    bool addNewChapter(const std::string& bookId, const std::string& title);
    bool editChapter(const std::string& chapterId, const std::string& title);
};

#endif
