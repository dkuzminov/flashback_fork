#include "Database.h"
#include "Settings.h"
#include "MockRepository.h"
#include "Log.h"
#include <QtWidgets>

Database& Database::Get()
{
    static Database instance;
    return instance;
}

Database::Database()
{
    m_coreDatabase = QSqlDatabase::addDatabase("QSQLITE", "Core");
}

IRepository& Database::GetRepository()
{
    if (BasicSettings::Get().UseMockRepository()) {
        return MockRepository::Get();
    }
    return *this;
}

class User : public IRepository::IUser,
             private IRepository::IProfile
{
public:
    User(QString name, QString filename, QString libraryDbFilename);

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
    QString GetCoachType() { return "Naive"; }
    IRepository::IStatistics* GetStatistics() { return NULL; }
    IRepository::IBookmark* GetBookmark(QString id);
    IRepository::ILibrary& GetPersonalLibrary() { throw "Not implemented"; }

    QString m_name;
    QString m_filename;
    QSqlDatabase m_userDatabase;
    QMap<QString, Variable> m_variables;
    QMap<QString, Bookmark> m_bookmarks;
};

IRepository::IUser* Database::GetUser() { return m_user.get(); }

bool Database::Connect(const QString &filename)
{
    LOG(Note, "Database::Connect(\"" + filename + "\")");

    m_path.clear();
    int pos = filename.lastIndexOf("/", -1, Qt::CaseInsensitive);
    if (pos != -1) {
        m_path = filename.left(pos);
    }

    m_coreDatabase.setDatabaseName(filename);
    if (!m_coreDatabase.open()) {
        LOG(Warning, "Failed to open Core database");
        return false;
    }
    x_ReadVariables();
    if (m_variables.count("User")) {
        x_selectUser(m_variables["User"]);
    }
    return true;
}

void Database::x_ReadVariables()
{
    QSqlQuery query(m_coreDatabase);
    if (!query.exec("SELECT name, value FROM Variable")) {
        LOG(Error, "Failed to select Variable");
        return;
    }
    while(query.next()) {
        QString name = query.value(0).toString();
        QString value = query.value(1).toString();
        LOG(Note, "Read variable: name = " + name + ", value = " + value);
        m_variables.insert(name, value);
    }
}

void Database::x_selectUser(const QString &id)
{
    QSqlQuery query(m_coreDatabase);
    query.prepare("SELECT name, filename FROM User WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        LOG(Error, "Failed to select User");
        return;
    }

    query.next();
    QString name = query.value(0).toString();
    QString filename = query.value(1).toString();
    LOG(Error, "Read user: name = " + name + ", filename = " + filename);
    m_user.reset(new User(name, m_path + "/" + filename, m_path + "/Library.db"));
}

////////////////////////////////////////////////////////////////////////////
// class User
////////////////////////////////////////////////////////////////////////////

User::User(QString name, QString filename, QString libraryDbFilename)
    : m_name(name)
{
    LOG(Note, "User::User(" + name + ", " + filename + ", " + libraryDbFilename + ")");
    m_userDatabase = QSqlDatabase::addDatabase("QSQLITE", "User");
    m_userDatabase.setDatabaseName(filename);
    if (!m_userDatabase.open()) {
        LOG(Warning, "Failed to open User database");
    }
    else {
        QSqlQuery query(m_userDatabase);
        if (!query.exec("ATTACH DATABASE '" + libraryDbFilename + "' AS 'Library'")) {
            LOG(Error, "Failed to attach Library database");
        }
    }
}

IRepository::IVariable* User::GetVariable(QString name)
{
    auto iter = m_variables.find(name);
    if (iter != m_variables.end()) {
        return &iter.value();
    }

    QSqlQuery query(m_userDatabase);
    query.prepare("SELECT value FROM Variable WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();
    if (query.next()) {
        QString value = query.value(0).toString();
        LOG(Note, "Read value = " + value);
        iter = m_variables.insert(name, value);
        return &iter.value();
    }
    return NULL;
}

IRepository::IBookmark* User::GetBookmark(QString id)
{
    auto iter = m_bookmarks.find(id);
    if (iter != m_bookmarks.end()) {
        return &iter.value();
    }

    QSqlQuery query(m_userDatabase);
    query.prepare("SELECT book_id, page_id FROM Bookmark WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    if (query.next()) {
        QString book_id = query.value(0).toString();
        QString page_id = query.value(1).toString();
        LOG(Note, "Read book_id = " + book_id);
        iter = m_bookmarks.insert(id, Bookmark(book_id, page_id, m_userDatabase));
        return &iter.value();
    }
    return NULL;
}

QString User::Bookmark::GetHtml()
{
    QSqlQuery query(*m_libraryDatabase);
    if (m_pageId == "first") {
        query.prepare(
                "SELECT a.contents FROM Page a "
                "LEFT JOIN Page b "
                "       ON b.book_id = a.book_id AND "
                "          b.number < a.number AND b.number > 0 "
                "WHERE b.number IS NULL AND a.book_id = :book_id");
        query.bindValue(":book_id", m_bookId);
    }
    else {
        query.prepare("SELECT contents FROM Page WHERE id = :id AND book_id = :book_id");
        query.bindValue(":id", m_pageId);
        query.bindValue(":book_id", m_bookId);
    }

    query.exec();
    if (query.next()) {
        QString contents = query.value(0).toString();
        LOG(Note, "contents = " + contents);
        return contents;
    }
    return "";
}
