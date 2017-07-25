#pragma once

#include "interface/IRepository.h"
#include <QtSql/QtSql>
#include <memory>

struct IDatabase;

class User : public repository::IUser,
             private repository::IProfile
{
public:
    User(IDatabase& owner, QString name, QString path, QString libraryDbFilename, bool createNew = false);

private:
    class Variable : public repository::IVariable
    {
    public:
        Variable() {}
        Variable(QString value) : m_value(value) {}

    private:
        QString GetValue() { return m_value;}

        QString m_value;
    };

    class Bookmark : public repository::IBookmark,
                     private repository::IPage
    {
    public:
        Bookmark() {}
        Bookmark(QString bookId, QString pageId, QSqlDatabase &database)
            : m_bookId(bookId),
              m_pageId(pageId),
              m_libraryDatabase(&database)
        {
        }

    private:
        IPage& GetPage() { return *this; }
        QString GetHtml();

        QString m_bookId;
        QString m_pageId;
        QSqlDatabase *m_libraryDatabase;
    };

    // IUser:
    QString GetName() { return m_name; }
    repository::IProfile& GetProfile() { return *this; }

    // IProfile:
    QString GetProfileName() { return "Stub"; }
    repository::IVariable* GetVariable(QString name);
    repository::ILanguage& GetLanguage();
    QString GetCoachType() { return "Alexandra"; }
    repository::IBookmark* GetBookmark(QString id);
    repository::ILibrary& GetPersonalLibrary() { throw "Not implemented"; }

    IDatabase& m_owner;
    QString m_name;
    QString m_filename;
    QSqlDatabase m_userDatabase;
    QMap<QString, std::shared_ptr<Variable>> m_variables;
    QMap<QString, std::shared_ptr<Bookmark>> m_bookmarks;
    repository::ILanguage *m_language;
};
