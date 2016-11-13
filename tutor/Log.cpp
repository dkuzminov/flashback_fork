#include "Log.h"
#include <QFile>
#include <QTextStream>

class Log
{
public:
    static Log& Get()
    {
        static Log instance;
        return instance;
    }

    QTextStream& operator << (const QString& msg)
    {
        out << msg;
        out.flush();
        return out;
    }

private:
    Log();
    QFile m_file;
    QTextStream out;
};

Log::Log()
    : m_file("Log.txt")
{
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    out.setDevice(&m_file);
}

void LOG(LogType, const QString &msg)
{
    Log::Get() << msg << '\n';
}
