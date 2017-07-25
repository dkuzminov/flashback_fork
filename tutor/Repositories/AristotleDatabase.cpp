#include "AristotleDatabase.h"
#include "Log.h"

AristotleDatabase& AristotleDatabase::Get()
{
    static AristotleDatabase instance;
    return instance;
}

AristotleDatabase::AristotleDatabase()
{
    m_sqliteDatabase = QSqlDatabase::addDatabase("QSQLITE", "Core");
}

bool AristotleDatabase::Connect(const QString &path)
{
    LOG(Note, "Database::Connect(\"" + path + "\")");

    m_path = path;
    if (QFile(m_path).exists()) {
        m_sqliteDatabase.setDatabaseName(m_path);
        if (!m_sqliteDatabase.open()) {
            LOG(Warning, "Failed to open Aristotle database at " + m_path);
            return false;
        }
        x_ReadVariables();
        return true;
    }
    else {
        return false;
    }
}

QString AristotleDatabase::GetProfileName()
{
    auto var = GetVariable("ProfileName");
    if (var) {
        return var->GetValue();
    }
    return "";
}

QString AristotleDatabase::GetName()
{
    auto var = GetVariable("UserName");
    if (var) {
        return var->GetValue();
    }
    return "";
}

QString AristotleDatabase::GetLanguageName()
{
    auto var = GetVariable("Language");
    if (var) {
        return var->GetValue();
    }
    return "";
}

bool AristotleDatabase::Autogenerate(const QString &path)
{
    LOG(Note, "AristotleDatabase::Autogenerate(\"" + path + "\")");

    m_path = path;
    QFile(m_path).remove();

    m_sqliteDatabase.setDatabaseName(m_path);
    if (!m_sqliteDatabase.open()) {
        LOG(Warning, "Failed to create Aristotle database");
        return false;
    }

    static const char* scriptList[] = {
            ":/sql/Aristotle/tables",
            ":/sql/Aristotle/values"};
    QSqlQuery query(m_sqliteDatabase);
    for (auto script : scriptList) {
        QFile scriptFile(script);
        scriptFile.open(QIODevice::ReadOnly);
        QStringList queryList =
                QTextStream(&scriptFile).readAll().split(";", QString::SkipEmptyParts);
        for (auto queryStr : queryList) {
            LOG(Warning, "Executing query: " + queryStr);
            query.exec(queryStr);
        }
    }

    return true;
}

repository::IVariable* AristotleDatabase::GetVariable(QString name)
{
    auto iter = m_variables.find(name);
    if (iter != m_variables.end()) {
        return iter->second.get();
    }

    QSqlQuery query(m_sqliteDatabase);
    query.prepare("SELECT value FROM Variable WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();
    if (query.next()) {
        QString value = query.value(0).toString();
        LOG(Note, "Read value = " + value);
        auto p = m_variables.insert(std::make_pair(name, std::unique_ptr<Variable>(new Variable(value))));
        return p.first->second.get();
    }
    return NULL;
}

std::vector<std::pair<QString, QString>> AristotleDatabase::GetNWordPairs(size_t num)
{
    std::vector<std::pair<QString, QString>> result;

    QSqlQuery query(m_sqliteDatabase);
    query.prepare("SELECT Word, Translation FROM Words ORDER BY Random() LIMIT :num");
    query.bindValue(":num", num);

    query.exec();
    while (query.next()) {
        QString word = query.value(0).toString();
        QString translation = query.value(1).toString();
        result.push_back(std::make_pair(word, translation));
    }
    return std::move(result);
}

void AristotleDatabase::x_ReadVariables()
{
    QSqlQuery query(m_sqliteDatabase);
    if (!query.exec("SELECT name, value FROM Variables WHERE name in ('UserName', 'ProfileName', 'Language')")) {
        LOG(Error, "Failed to SELECT FROM Variables");
        return;
    }
    while(query.next()) {
        QString name = query.value(0).toString();
        QString value = query.value(1).toString();
        LOG(Note, "Read variable: name = " + name + ", value = " + value);
        m_variables.insert(std::make_pair(name, std::unique_ptr<Variable>(new Variable(value))));
    }

    if (!m_variables.count("UserName")) {
        LOG(Warning, "Variable UserName not set");
    }
    if (!m_variables.count("ProfileName")) {
        LOG(Warning, "Variable ProfileName not set");
    }
    if (!m_variables.count("Language")) {
        LOG(Warning, "Variable Language not set");
    }
}
