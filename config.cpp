#include "classes.h"

int Config::read(QString filename){
    /*this function is called at start up, and whenever the config is updated*/
    QFile file(CONFPATH+filename);
    /*If the file doesn't exist, nothing can run, so return 1 for failure, service will stop*/
    if (!file.exists()) return 1;
    file.open(QFile::ReadOnly);
    /*Nested loops handle profile configurations, stored in a 3 dimensional array compressed into 2 dimensions using CSV*/
    while (!file.atEnd()) {
        QString line = file.readLine();
        if (line.startsWith("ASIN ")) ASIN = line.remove("ASIN ").toInt();
        else if (line.startsWith("PROFILE ")){
            QString profileName = line.remove("PROFILE ");
            QStringList files = QStringList();
            QStringList dirs = QStringList();
            QStringList hives = QStringList();
            QStringList browsers = QStringList();
            QStringList translations = QStringList();
            while (!file.atEnd()) {
                line = file.readLine();
                if (line.startsWith("/PROFILE")) {
                    /*Compress all the individual QStringLists into CSV QStrings, store in a single QStringList*/
                    QStringList container = QStringList() << profileName.trimmed() << files.join(",") << dirs.join(",") <<
                                hives.join(",") << browsers.join(",") << translations.join(",");
                    profiles.append(container);
                    break;
                }
                else if (line.startsWith("FILE ")) files.append(line.remove("FILE ").trimmed());
                else if (line.startsWith("PATH ")) dirs.append(line.remove("PATH ").trimmed());
                else if (line.startsWith("HIVE ")) hives.append(line.remove("HIVE ").trimmed());
                else if (line.startsWith("BROWSER ")) browsers.append(line.remove("BROWSER ").trimmed());
                else if (line.startsWith("TRANSLATION ")) translations.append(line.remove("TRANSLATION ").trimmed());
            }
        }
    }
    return profiles.length(); /*If this returns zero, program will exit*/
}
int Config::index(QString arg){
    /*This returns an index of name to index of profiles for referencing Config::profiles by name, -1 on failure*/
    int length = profiles.length() - 1;
    for ( int index = 0; index <= length; index++ ){
        if (arg == profiles[index][0]) return index;
    }
    return -1;
}

int Config::getASIN(){
    return ASIN;
}
QStringList Config::getProfile(int arg){
    return profiles[arg];
}
QStringList Config::getProfile(QString arg){
    return profiles[index(arg)];
}

QStringList Config::getProfileNames(){
    QStringList container = QStringList();
    int length = profiles.length() - 1;
    for ( int index = 0; index <= length; index++ ) container.append(profiles[index][0]);
    return container;
}
