#pragma once

class QString;

typedef enum {Critical, Error, Warning, Debug, Note} LogType;

void LOG(LogType type, const QString &msg);
