#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>

class utilities
{
public:
    utilities();

    static bool isHexString(const QString &str) {
        bool ok;
        QString editedString = str;
        editedString.removeAt(0);
        editedString.toLongLong(&ok, 16);
        return ok;
    }
};

#endif // UTILITIES_H
