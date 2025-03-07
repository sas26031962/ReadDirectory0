#ifndef CINIFILE_H
#define CINIFILE_H

#include <QString>
#include <QSettings>
#include <QDebug>
#include <QImage>
#include "crecord.h"

class cIniFile
{
private:
    QString directoryPath;
public:
    //Атрибуты
    static QString iniFilePath;
    static QSettings settings;  //(cIniFile::iniFilePath, QSettings::IniFormat);
    static cIniFile IniFile;

    int iRecordListLength = 0;  //Полное число записей
    int Id = 0;                 //Идентификатор - счётчик записей

    //Конструктор
    cIniFile(QString sourcePath);

    //Методы
    QString getDirectoryPah();

    void addInitalSection(int n);
    void addRecordListData();
};

#endif // CINIFILE_H
