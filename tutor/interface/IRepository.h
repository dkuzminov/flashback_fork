#pragma once
#include <QObject>
#include <QString>
#include <vector>

namespace repository {

class IVariable : public QObject
{
    Q_OBJECT

public:
    virtual QString GetValue() = 0;
};

class IDictionary : public QObject
{
    Q_OBJECT

public:
    virtual std::vector<std::pair<QString, QString>> GetNWordPairs(size_t num) = 0;
    virtual void RecordAnswer(const QString& word, bool isCorrect) = 0;
};

// ToDo rename to Thesaurus
class ILanguage : public QObject
{
    Q_OBJECT

public:
    virtual QString GetLanguageName() = 0;
    virtual IDictionary& GetDictionary() = 0;
    //virtual ILibrary& GetLibrary() = 0;
};

class IPage : public QObject
{
    Q_OBJECT

public:
    virtual QString GetHtml() = 0;
    //virtual IBook& GetBook() = 0;
};

class IBook : public QObject
{
    Q_OBJECT

public:
    virtual QString GetId() = 0;
};

class ILibrary : public QObject
{
    Q_OBJECT

public:
    virtual IBook* GetBook(QString id) = 0;
    virtual ILanguage& GetLanguage() = 0;
};

class IBookmark : public QObject
{
    Q_OBJECT

public:
    //virtual QString GetId() = 0;
    virtual IPage& GetPage() = 0;
};

class IProfile : public QObject
{
    Q_OBJECT

public:
    virtual QString GetProfileName() = 0;
    virtual IVariable* GetVariable(QString name) = 0;
    virtual ILanguage& GetLanguage() = 0;
    virtual QString GetCoachType() = 0;
    //virtual IStatistics* GetStatistics() = 0;
    virtual IBookmark* GetBookmark(QString id) = 0;
    // ToDo: Isolate Bookmarks and library into separate interface
    //virtual IBookmarks* GetBookmarks() = 0;
    virtual ILibrary& GetPersonalLibrary() = 0;
};

class IUser : public QObject
{
    Q_OBJECT

public:
    virtual QString GetName() = 0;
    virtual IProfile& GetProfile() = 0;
};

class IRepository : public QObject
{
    Q_OBJECT

public:
    virtual IUser* GetUser() = 0;
};

}
