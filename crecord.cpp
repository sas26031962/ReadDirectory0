#include "crecord.h"

cRecord::cRecord()
{
    qDebug() << "#cRecrod created";
}

void cRecord::showList()
{
    int RecordListCount = cRecord::RecordList->count();
    qDebug() << "RecordList count=" << RecordListCount;

    for(int i = 0; i < RecordListCount; i++)
     {
        cRecord::RecordList->at(i).show();
        qDebug() << "Index=" << i;
    }
}

void cRecord::show() const
{
    qDebug() << "Name: " << qsName;
    qDebug() << "Path: " << qsPath;
    qDebug() << "Size: " << iSize;
    qDebug() << "Is Directory: " << IsDir;
    qDebug() << ">>Record size=" << sizeof (this);
    qDebug() << "--------------------";
}
