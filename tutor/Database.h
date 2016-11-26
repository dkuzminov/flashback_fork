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
    void x_ReadVariables();
    void x_selectUser(const QString &id);

    QString m_path;
    QSqlDatabase m_coreDatabase;
    QMap<QString, QString> m_variables;
    std::shared_ptr<User> m_user;
};

