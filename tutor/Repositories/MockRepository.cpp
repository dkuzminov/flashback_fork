#include "Log.h"
#include "MockRepository.h"
#include <QFile>
#include <QTextStream>

MockRepository& MockRepository::Get()
{
    static MockRepository instance;
    return instance;
}

MockRepository::MockRepository()
{

}

class Bookmark : public IRepository::IVariable,
                 public IRepository::IBookmark,
                 public IRepository::IPage
{
public:
    Bookmark(QString variableValue, QString resourceName)
        : m_variableValue(variableValue),
          m_resourceName(resourceName) {}
private:
    // IVariable:
    QString GetValue() { return m_variableValue; }

    // IBookmark:
    IPage& GetPage() { return *this; }

    // IPage:
    QString GetHtml()
    {
        QFile file(m_resourceName);
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&file);
        return in.readAll();
    }

    QString m_variableValue;
    QString m_resourceName;
};

static Bookmark TextbookBookmark("text", ":/html/templates/demo/mock_repository/TextbookPage1");
static Bookmark FictionBookmark("fiction", ":/html/templates/demo/mock_repository/FictionPage1");

IRepository::IVariable* MockRepository::GetVariable(QString name)
{
    if (name == "TextbookBookmark") {
        return &TextbookBookmark;
    }
    else if (name == "FictionBookmark") {
        return &FictionBookmark;
    }
    return NULL;
}

IRepository::IBookmark* MockRepository::GetBookmark(QString id)
{
    if (id == "text") {
        return &TextbookBookmark;
    }
    else if (id == "fiction") {
        return &FictionBookmark;
    }
    return NULL;
}
