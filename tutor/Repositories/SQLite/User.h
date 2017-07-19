#pragma once

#include "interface/IRepository.h"
#include <QtSql/QtSql>
//#include <memory>

class User : public IRepository::IUser,
             private IRepository::IProfile
{
public:
    User(QString name, QString path, QString libraryDbFilename, bool createNew = false);

private:
    class Variable : public IRepository::IVariable
    {
    public:
        Variable() {}
        Variable(QString value) : m_value(value) {}

    private:
        QString GetValue() { return m_value;}

        QString m_value;
    };

    class Bookmark : public IRepository::IBookmark,
                     private IRepository::IPage
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
    IRepository::IProfile& GetProfile() { return *this; }

    // IProfile:
    QString GetProfileName() { return "Stub"; }
    IRepository::IVariable* GetVariable(QString name);
    IRepository::ILanguage& GetLanguage() { throw "Not implemented"; }
    QString GetCoachType() { return "Alexandra"; }
    IRepository::IStatistics* GetStatistics() { return NULL; }
    IRepository::IBookmark* GetBookmark(QString id);
    IRepository::ILibrary& GetPersonalLibrary() { throw "Not implemented"; }

    QString m_name;
    QString m_filename;
    QSqlDatabase m_userDatabase;
    QMap<QString, Variable> m_variables;
    QMap<QString, Bookmark> m_bookmarks;
};
