#include <QDebug>
#include <QList>
#include <QStringList>
#include "classes.h"

int Config::ASIN = 1;
QList<QStringList> Config::profiles = QList<QStringList>();

int main(int argc, char *argv[])
{
    Config start;
    if (start.read() == 0) return 1;
    return 0;
}
