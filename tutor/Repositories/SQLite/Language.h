#pragma once

#include "interface/IRepository.h"
#include <QtSql/QtSql>

class Language : public repository::ILanguage,
                 private repository::IDictionary
{
public:
    Language(QString name, QString path);

private:
    // IRepository::ILanguage:
    QString GetLanguageName() { return m_languageName; }
    IDictionary& GetDictionary() { return *this; }

    // IRepository::IDictionary:
    std::vector<std::pair<QString, QString>> GetNWordPairs(size_t num);

    QString m_languageName;
    QString m_filename;
    QSqlDatabase m_languageDatabase;
};
