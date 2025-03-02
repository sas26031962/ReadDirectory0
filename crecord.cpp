#include "crecord.h"

cRecord::cRecord()
{
    qDebug() << "#cRecrod created";
}

//void cRecord::showList()
//{
//    if(cRecord::RecordList->size() > 0)
//    {
//        for(int i = 0; i < cRecord::RecordList->count(); i++)
//        {
//            qDebug() << "Name: " << cRecord::RecordList->at(i).qsName;
//            qDebug() << "Path: " << cRecord::RecordList->at(i).qsPath;
//            qDebug() << "Sise: " << cRecord::RecordList->at(i).iSize;
//            qDebug() << "IsDir: " << cRecord::RecordList->at(i).IsDir;
//            qDebug() << "--------------------";
//        }
//    }
//    else
//    {
//        qDebug() << "List is empty";
//    }
//}

void cRecord::show() const
{
    qDebug() << "Name: " << qsName;
    qDebug() << "Path: " << qsPath;
    qDebug() << "Size: " << iSize;
    qDebug() << "Is Directory: " << IsDir;
    qDebug() << ">>Record size=" << sizeof (this);
    qDebug() << "--------------------";
}
