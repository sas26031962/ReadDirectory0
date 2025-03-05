#include "crecord.h"

cRecord::cRecord()
{
    //qDebug() << "#cRecrod created";
}

void cRecord::showList()
{
    int RecordListCount = cRecord::RecordList->count();
    qDebug() << "RecordList count=" << RecordListCount;
    qDebug() << "--------------------";

    for(int i = 0; i < RecordListCount; i++)
     {
        qDebug() << "Index=" << i;
        cRecord::RecordList->at(i).show();
    }
}

void cRecord::show() const
{
    qDebug() << "Name: " << qsName;
    qDebug() << "Path: " << qsPath;
    qDebug() << "Size: " << iSize;
    //qDebug() << "Is Directory: " << IsDir;
    //qDebug() << ">>Record size=" << sizeof (this);
    qDebug() << "--------------------";
}

int cRecord::readDirectory(QString directoryPath)
{
    int result = 0;

    // Объект QDir для работы с каталогом.
    QDir directory(directoryPath);

    // Проверка существования  каталога
    if (!directory.exists())
    {
        result = 1;
        qDebug() << "!!!Directory '" << directoryPath << "' not found";
        return result;
    }

    // Фильтры для выбора нужных файлов и каталогов.
    QDir::Filters filters = QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot;
    directory.setFilter(filters);

    // Порядок сортировки.
    directory.setSorting(QDir::Name);

    // Список файлов и каталогов.
    QFileInfoList fileList = directory.entryInfoList();

    // Перебор списка и выведение информации о каждом файле и каталоге.
    qDebug() << "Directory: " << directoryPath;

    cRecord Record;

    //---Запись данных---
    for (const QFileInfo &fileInfo : fileList)
    {
        QString name = fileInfo.fileName();
        QString path = fileInfo.filePath();
        size_t size = fileInfo.size();
        bool isDir = fileInfo.isDir();

        Record.qsName  = name;
        Record.qsPath = path;
        Record.iSize  = size;
        Record.IsDir = isDir;

        //Record.show();

        //Рекурсивный вызов
        if(isDir)
        {
            QString s = fileInfo.filePath();
            cRecord::readDirectory(s);
        }
        else
        {
            cRecord::RecordList->append(Record);
        }
    }

    return result;
}
