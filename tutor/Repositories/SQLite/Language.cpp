#include "Language.h"
#include "Log.h"

Language::Language(QString name, QString path)
{
    LOG(Note, "Language::Language('" + name + "', '" + path + "')");
    m_languageDatabase = QSqlDatabase::addDatabase("QSQLITE", "Language");
    m_languageDatabase.setDatabaseName(path + name + ".db");
    if (!m_languageDatabase.open()) {
        LOG(Error, "Failed to open Language database");
        // ToDo: throw an exception; nothing can be done without a connection
        return;
    }
}

std::vector<std::pair<QString, QString>> Language::GetNWordPairs(size_t num)
{
    std::vector<std::pair<QString, QString>> result;

    QSqlQuery query(m_languageDatabase);
    query.prepare("SELECT Word, Translation FROM Words ORDER BY Random() LIMIT :num");
    query.bindValue(":num", num);

    query.exec();
    while (query.next()) {
        QString word = query.value(0).toString();
        QString translation = query.value(1).toString();
        result.push_back(std::make_pair(word, translation));
    }
    return move(result);
}
