#pragma once

#include "interface/IRepository.h"
#include <QtSql/QtSql>
#include <memory>

class User;
class Language;

struct IDatabase
{
    virtual repository::ILanguage* GetLanguage(QString name) = 0;
};

class Database : private repository::IRepository,
                 private IDatabase
{
    Q_OBJECT

public:
    static Database& Get();
    bool Connect(const QString &path);
    bool Reconstruct(const QString &path);
    bool CreateUser(const QString &name);
    IRepository& GetRepository();

private:
    Database();
    repository::IUser* GetUser();

    // IDatabase:
    repository::ILanguage* GetLanguage(QString name);

    void x_RemoveDatabaseFiles();
    void x_RemoveDirectory(const QString &dirName);
    void x_ReconstructSampleLibrary();
    void x_ReadVariables();
    void x_selectUser(const QString &id);

    QString m_path;
    QSqlDatabase m_coreDatabase;
    QMap<QString, QString> m_variables;
    std::shared_ptr<User> m_user;
    std::shared_ptr<Language> m_language;
};

