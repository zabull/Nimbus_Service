#ifndef CLASSES_H
#define CLASSES_H

#define CONFPATH "C:/Users/Zach/Documents/Source/Nimbus_Service/"
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>

class Config
{
    /*Define variables*/
    static QList<QStringList> profiles;
    /*ASIN stands for Autonomous System Identification Number, and represents the computer
    (or system of computers) that this service is running inside.*/
    static int ASIN;
    static QString server;
    int index(QString);
public:
    Config(){
        /*do nothing*/
    }
    int read(QString filename = "run.conf");
    int getASIN();
    QStringList getProfile(int);
    /*Overloaded getProfile, by name*/
    QStringList getProfile(QString);
    QStringList getProfileNames();
};

#endif // CLASSES_H
