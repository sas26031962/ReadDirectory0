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
    for(int i = 0; i < cRecord::RecordList->count(); i++)
     {
        QString name = cRecord::RecordList->at(i).qsName;
        int iDotPosition = name.indexOf('.');
        QString groupName = name.mid(0, iDotPosition);
        //qDebug() << "groupName=" << groupName;

        cIniFile::IniFile.Id++;//Счётчик записей

        QString path = cRecord::RecordList->at(i).qsPath;
        int iNamePosition = path.indexOf(name);
        QString PathWithoutName = path.mid(0, iNamePosition - 1);
        //qDebug() << "Path=" << PathWithoutName;

        int size = cRecord::RecordList->at(i).iSize;

        int iExtensionPosition = path.indexOf('.');
        QString qsExtension = path.mid(iExtensionPosition + 1);

        //qDebug() << "Extension:" << qsExtension.toLower();

        bool IsError = false;
        int width = 0;
        int height = 0;

        if(qsExtension.toLower() == "mp4")
        {
            qDebug() << "Extension: mp4";
        }
        else
        {
            //Фрагмент для обработки файлов изображений
            QImage image(path);//name

            width = image.width();
            height = image.height();
        }

            cIniFile::settings.beginGroup(groupName);
            cIniFile::settings.setValue("Id", cIniFile::IniFile.Id);
            cIniFile::settings.setValue("name", name);
            cIniFile::settings.setValue("path", PathWithoutName);
            cIniFile::settings.setValue("size", size);
            if(IsError)
            {
                cIniFile::settings.setValue("error", true);
            }
            else
            {
                cIniFile::settings.setValue("width", width);
                cIniFile::settings.setValue("height", height);
            }
            cIniFile::settings.endGroup();
    }
    qDebug() << "==================Task is done!!!=========================";
    //---Освобождение ресурсов---

    return a.exec();
}
