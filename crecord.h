#ifndef CRECORD_H
#define CRECORD_H

#include <memory>
#include <QDebug>

class cRecord
{

public:
    //Атрибуты

    //static QList<cRecord> * RecordList;

    QString qsName = "NoName";
    QString qsPath = "";
    size_t iSize = 0;
    bool IsDir = false;

    //Конструктор
    cRecord();
//    ~cRecord();

    //Методы
    //static void showList();
    void show() const;

signals:

public slots:

};

#endif // CRECORD_H
