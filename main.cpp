#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug> // Для вывода в консоль
#include <QDirIterator>
#include <cstring>

#include "crecord.h"

//Глобальные переменные
QList<cRecord> * cRecord::RecordList;

//Главная функция программы
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::unique_ptr<QList<cRecord> > ptrRecordList = std::make_unique<QList<cRecord> >();
    cRecord::RecordList = ptrRecordList.get();

    // Путь к каталогу, который нужно прочитать.
    QString directoryPath = "/home/andy/Рабочий стол/From Smartfone"; // Путь для linux mint
    //QString directoryPath = "C:/Work/Pictures"; // Путь для Windows10
   // QString directoryPath = QCoreApplication::applicationDirPath(); // текущая папка с исполняемым файлом

    // Объект QDir для работы с каталогом.
    QDir directory(directoryPath);

    // Проверка существования  каталога
    if (!directory.exists())
    {
        qDebug() << "Каталог не существует: " << directoryPath;
        return 1;
    }

    // Фильтры для выбора нужных файлов и каталогов.
    QDir::Filters filters = QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot;
    directory.setFilter(filters);

    // Порядок сортировки.
    directory.setSorting(QDir::Name);

    // Список файлов и каталогов.
    QFileInfoList fileList = directory.entryInfoList();

    // Перебор списка и выведение информации о каждом файле и каталоге.
    qDebug() << "Content of dir: " << directoryPath;

    cRecord Record;

    cRecord::RecordList->clear();

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

        cRecord::RecordList->append(Record);

    }

    //---Чтение данных---

    qDebug() << "====================";

    cRecord::showList();//Отображение даных

    //---Освобождение ресурсов---

    return a.exec();
}
