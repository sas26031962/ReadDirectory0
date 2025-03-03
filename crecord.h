#ifndef CRECORD_H
#define CRECORD_H

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>

class cRecord
{

public:
    //Атрибуты

    static QList<cRecord> * RecordList;

    QString qsName = "NoName";
    QString qsPath = "";
    size_t iSize = 0;
    bool IsDir = false;

    //Конструктор
    cRecord();

    //Методы
    static void showList();
    static int readDirectory(QString directoryPath);
    void show() const;

signals:

public slots:

};

#endif // CRECORD_H
