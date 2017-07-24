#include "User.h"
#include "Repositories/SQLite/Database.h"
#include "Log.h"

User::User(IDatabase& owner, QString name, QString path, QString libraryDbFilename, bool createNew)
    : m_owner(owner)
{
    // ToDo: Avoid passing library filename and path
    LOG(Note, "User::User('" + name + "', '" + path + "', '" + libraryDbFilename + "'" + createNew + ")");
    m_userDatabase = QSqlDatabase::addDatabase("QSQLITE", "User");
    m_userDatabase.setDatabaseName(path + name + ".db");
    if (!m_userDatabase.open()) {
        LOG(Error, "Failed to open User database");
        // ToDo: throw an exception; nothing can be done without a connection
        return;
    }

    QSqlQuery query(m_userDatabase);
    if (createNew) {
        static const char* fileList[] = {
                ":/sql/User/tables",
                ":/sql/User/values"};
        for (auto filename : fileList) {
            QFile scriptFile(filename);
            scriptFile.open(QIODevice::ReadOnly);
            QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(";", QString::SkipEmptyParts);
            for (auto scriptQuery : scriptQueries) {
                LOG(Note, "Executing query: " + scriptQuery);
                query.exec(scriptQuery);
            }
        }
    }
    if (!query.exec("ATTACH DATABASE '" + libraryDbFilename + "' AS 'Library'")) {
        LOG(Error, "Failed to attach Library database");
    }

    IRepository::IVariable* var = GetVariable("Language");
    if (var) {
        m_language = owner.GetLanguage(var->GetValue());
    }
    else {
        m_language = NULL;
        LOG(Error, "No language specified in User database");
        // ToDo: throw an exception
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

IRepository::ILanguage& User::GetLanguage()
{
    return *m_language;
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
