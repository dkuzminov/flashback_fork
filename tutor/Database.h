#pragma once

#include "interface/IRepository.h"
#include <QtSql/QtSql>
#include <memory>

class User;

class Database : public QObject,
                 private IRepository
{
    Q_OBJECT

public:
    static Database& Get();
    bool Connect(const QString &filename);
    IRepository& GetRepository();

private:
    Database();
    IUser* GetUser();

    QSqlDatabase m_coreDatabase;
    std::shared_ptr<User> m_user;
};

