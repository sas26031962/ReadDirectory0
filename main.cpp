#include <QCoreApplication>
#include <QSettings>
#include <QImage>
#include <memory>
#include "crecord.h"
#include "cinifile.h"

//=============================================================================
//Глобальные переменные
//=============================================================================
QList<cRecord> * cRecord::RecordList;
QString cIniFile::iniFilePath = "C:/WORK/ReadDirectory0/programm/data/FilesConfigShips.ini";// Путь к INI-файлу
QSettings cIniFile::settings(cIniFile::iniFilePath, QSettings::IniFormat);

// Путь к каталогу, который нужно прочитать.
//cIniFile cIniFile::IniFile("/home/andy/From Smartfone");
cIniFile cIniFile::IniFile("C:/Work/Ships");


//=============================================================================
//Главная функция программы
//=============================================================================
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //---Создание рабочего списка
    std::unique_ptr<QList<cRecord> > ptrRecordList(new QList<cRecord>());
    cRecord::RecordList = ptrRecordList.get();

    //---Очистка рабочего списка
    cRecord::RecordList->clear();

    //---Чтение содержимого каталога ---
    if(cRecord::readDirectory(cIniFile::IniFile.getDirectoryPah()) > 0)
    {
        //qDebug() << "Directory not found: " << directoryPath;
        return 1;
    }

    //---Отображение даных
    //cRecord::showList();

    //---Добавление идентификационной секции
    cIniFile::IniFile.addInitalSection(cRecord::RecordList->count());

    //---Добавление данных в файл конфигурации
    cIniFile::IniFile.addRecordListData();

    //---Освобождение ресурсов---

    return a.exec();
}
