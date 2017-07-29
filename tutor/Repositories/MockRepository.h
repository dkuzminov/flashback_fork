#pragma once

#include "interface/IRepository.h"

class MockRepository : public repository::IRepository,
                       private repository::IUser,
                       private repository::IProfile,
                       private repository::ILanguage,
                       private repository::IDictionary
{
public:
    static MockRepository& Get();

private:
    MockRepository();

    // IUser:
    IUser* GetUser() { return this; }
    QString GetName() { return "Mock User"; }
    IProfile& GetProfile() { return *this; }

    // IProfile:
    QString GetProfileName() { return "Mock Profile"; }
    repository::IVariable* GetVariable(QString name);
    ILanguage& GetLanguage() { return *this; }
    QString GetCoachType() { return "Alexandra"; }
    repository::IBookmark* GetBookmark(QString id);
    repository::ILibrary& GetPersonalLibrary() { throw "Not implemented"; }

    // ILanguage:
    QString GetLanguageName() { return "Latin"; }
    IDictionary& GetDictionary() {return *this; }

    // IDictionary:
    std::vector<std::pair<QString, QString>> GetNWordPairs(size_t num);
    void RecordAnswer(const QString& word, bool isCorrect) {}
    double GetProgress() { throw "Not implemented"; }
};

