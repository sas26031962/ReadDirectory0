#include <QCoreApplication>
#include <QSettings>
#include <QImage>
#include <memory>
#include "crecord.h"

//Глобальные переменные
QList<cRecord> * cRecord::RecordList;

//Главная функция программы
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::unique_ptr<QList<cRecord> > ptrRecordList(new QList<cRecord>());
    cRecord::RecordList = ptrRecordList.get();

    // Путь к каталогу, который нужно прочитать.
    QString directoryPath = "/home/andy/From Smartfone"; // Путь для linux mint
    //QString directoryPath = "C:/Work/Pictures"; // Путь для Windows10

    //Создаём файл конфигурации
    QDir executableDir(QCoreApplication::applicationDirPath());

    // Создаем путь к INI-файлу в той же директории
    QString iniFilePath = executableDir.filePath("../Data/FilesConfig.ini");

    // Создаем объект QSettings с указанием формата INI и пути к файлу
    QSettings settings(iniFilePath, QSettings::IniFormat);
/*
    // Записываем значения
    settings.beginGroup("MyGroup");
    settings.setValue("setting1", "value1");
    settings.setValue("setting2", 123);
    settings.endGroup();

    // Читаем значения (для проверки)
    settings.beginGroup("MyGroup");
    QString value1 = settings.value("setting1", "default_value").toString();
    int value2 = settings.value("setting2", 0).toInt();
    settings.endGroup();

    qDebug() << "setting1: " << value1;
    qDebug() << "setting2: " << value2;
*/
    qDebug() << "INI file created at: " << iniFilePath;

    //---Очистка рабочего списка
    cRecord::RecordList->clear();

    //---Чтение содержимого каталога ---
    if(cRecord::readDirectory(directoryPath) > 0)
    {
        //qDebug() << "Directory not found: " << directoryPath;
        return 1;
    }

    qDebug() << "====================";

    //---Чтение данных---

    //cRecord::showList();//Отображение даных

    int iRecordListLength = cRecord::RecordList->count();

    settings.beginGroup("RecordList");
    settings.setValue("length", iRecordListLength);
    settings.endGroup();

    int Id = 0;

    //---Добавление данных в файл конфигурации
    for(int i = 0; i < cRecord::RecordList->count(); i++)
     {
        QString name = cRecord::RecordList->at(i).qsName;
        int iDotPosition = name.indexOf('.');
        QString groupName = name.mid(0, iDotPosition);
        //qDebug() << "groupName=" << groupName;

        Id++;//Счётчик записей

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

            settings.beginGroup(groupName);
            settings.setValue("Id", Id);
            settings.setValue("name", name);
            settings.setValue("path", PathWithoutName);
            settings.setValue("size", size);
            if(IsError)
            {
                settings.setValue("error", true);
            }
            else
            {
                settings.setValue("width", width);
                settings.setValue("height", height);
            }
            settings.endGroup();
    }
    qDebug() << "==================Task is done!!!=========================";
    //---Освобождение ресурсов---

    return a.exec();
}
