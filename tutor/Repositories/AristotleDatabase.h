#pragma once
#include "interface/IRepository.h"
#include <QtSql/QtSql>
#include <memory>
#include <map>

class AristotleDatabase : private repository::IRepository,
                          private repository::IUser,
                          private repository::IProfile,
                          private repository::ILanguage,
                          private repository::IDictionary
{
    Q_OBJECT

private:
    class Variable : public repository::IVariable
    {
    public:
        Variable() {}
        Variable(QString value) : m_value(value) {}
    private:
        QString GetValue() { return m_value;}
        QString m_value;
    };

public:
    static AristotleDatabase& Get();
    bool Connect(const QString &path);
    bool Autogenerate(const QString &path);
    repository::IRepository& GetRepository() { return *this; }

private:
    AristotleDatabase();

    // IRepository:
    repository::IUser* GetUser() { return this; }

    // IUser:
    QString GetName();
    IProfile& GetProfile() { return *this; }

    // IProfile:
    QString GetProfileName();
    repository::IVariable* GetVariable(QString name);
    repository::ILanguage& GetLanguage() { return *this; }
    QString GetCoachType() { return "Alexandra"; }
    repository::IBookmark* GetBookmark(QString id) { throw "Not Implemented"; }
    repository::ILibrary& GetPersonalLibrary() { throw "Not Implemented"; }

    // ILanguage:
    QString GetLanguageName();
    repository::IDictionary& GetDictionary() { return *this; }

    // IDictionary:
    std::vector<std::pair<QString, QString>> GetNWordPairs(size_t num);
    void RecordAnswer(const QString& word, bool isCorrect);
    double GetProgress();

    void x_ReadVariables();

    QString m_path;
    QSqlDatabase m_sqliteDatabase;
    std::map<QString, std::unique_ptr<Variable>> m_variables;
};
