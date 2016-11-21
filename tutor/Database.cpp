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

class User : public IRepository::IUser
{
    QString GetName() { return "Stub"; }
    IRepository::IProfile& GetProfile() { throw "Not implemented yet"; }
};

IRepository::IUser* Database::GetUser() { return m_user.get(); }

bool Database::Connect(const QString &filename)
{
    LOG(Note, "Database::Connect(\"" + filename + "\")");
    m_coreDatabase.setDatabaseName(filename);
    if (!m_coreDatabase.open()) {
        QMessageBox::warning(0, "Failed", "Failed to open Core database!");
        LOG(Warning, "Failed to open Core database");
        return false;
    }
    m_user.reset(new User);
    return true;
}
