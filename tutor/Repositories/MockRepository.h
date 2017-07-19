#pragma once

#include "interface/IRepository.h"

class MockRepository : public IRepository,
                       private IRepository::IUser,
                       private IRepository::IProfile,
                       private IRepository::ILanguage,
                       private IRepository::IDictionary
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
    IVariable* GetVariable(QString name);
    ILanguage& GetLanguage() { return *this; }
    QString GetCoachType() { return "Alexandra"; }
    IStatistics* GetStatistics() { return NULL; }
    IBookmark* GetBookmark(QString id);
    ILibrary& GetPersonalLibrary() { throw "Not implemented"; }

    // ILanguage:
    QString GetLanguageName() { return "Latin"; }
    IDictionary& GetDictionary() {return *this; }

    // IDictionary:
    std::vector<std::pair<QString, QString>> GetNWordPairs(size_t num);
};

