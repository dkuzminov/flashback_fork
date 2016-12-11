#include "Database.h"
#include "Repositories/SQLite/User.h"
#include "Repositories/MockRepository.h"
#include "Settings.h"
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

IRepository::IUser* Database::GetUser() { return m_user.get(); }

bool Database::Connect(const QString &path)
{
    LOG(Note, "Database::Connect(\"" + path + "\")");

    m_path = path;
    m_coreDatabase.setDatabaseName(m_path + "Core.db");
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

bool Database::Reconstruct(const QString &path)
{
    LOG(Note, "Database::Reconstruct(\"" + path + "\")");

    m_path = path;
    x_RemoveDatabaseFiles();

    m_coreDatabase.setDatabaseName(m_path + "Core.db");
    if (!m_coreDatabase.open()) {
        LOG(Warning, "Failed to create Core database");
        return false;
    }

    static const char* scriptList[] = {
            ":/sql/Core/tables",
            ":/sql/Core/values"};
    QSqlQuery query(m_coreDatabase);
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

    QDir().mkdir(m_path + "Users");
    QDir().mkdir(m_path + "Libraries");

    x_ReconstructSampleLibrary();
    return true;
}

bool Database::CreateUser(const QString &name)
{
    LOG(Note, "Database::CreateUser(\"" + name + "\")");

    // ToDo: check that user doesn't exist
    m_user.reset(new User(name, m_path + "Users/", m_path + "Libraries/Sample.db", true));
    QString id = name.toLower();
    QSqlQuery query(m_coreDatabase);
    query.prepare("INSERT INTO Variable (name, value) VALUES ('User', :id)");
    query.bindValue(":id", id);
    query.exec();
    {{
        QSqlQuery query(m_coreDatabase);
        query.prepare("INSERT INTO User (id, name, filename) VALUES (:id, :name, :filename)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":filename", name + ".db");
        query.exec();
    }}
    return true;
}

void Database::x_RemoveDatabaseFiles()
{
    // ToDo: Make this procedure smarter
    QFile(m_path + "Core.db").remove();
    x_RemoveDirectory(m_path + "Users/");
    x_RemoveDirectory(m_path + "Libraries/");
}

void Database::x_RemoveDirectory(const QString &dirName)
{
    QDir dir(dirName);
    if (dir.exists()) {
        for (auto info : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files)) {
            QFile::remove(info.absoluteFilePath());
        }
        QDir().rmdir(dirName);
    }
}

void Database::x_ReconstructSampleLibrary()
{
    QSqlDatabase libraryDatabase = QSqlDatabase::addDatabase("QSQLITE", "Library");
    libraryDatabase.setDatabaseName(m_path + "/Libraries/Sample.db");
    if (libraryDatabase.open()) {
        QSqlQuery query(libraryDatabase);

        static const char* fileList[] = {
                ":/sql/Library/tables",
                ":/sql/Library/values"};
        for (auto filename : fileList) {
            QFile scriptFile(filename);
            scriptFile.open(QIODevice::ReadOnly);
            QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(";", QString::SkipEmptyParts);
            for (auto scriptQuery : scriptQueries) {
                LOG(Warning, "Executing query: " + scriptQuery);
                query.exec(scriptQuery);
            }
        }
    }
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
    m_user.reset(new User(name, m_path + "Users/", m_path + "Libraries/Sample.db"));
}
