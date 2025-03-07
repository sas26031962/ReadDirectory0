#include "cinifile.h"

cIniFile::cIniFile(QString sourcePath)
{
    directoryPath = sourcePath;
    qDebug() << "INI file created at: " << sourcePath;//cIniFile::iniFilePath;
}

QString cIniFile::getDirectoryPah()
{
    return directoryPath;
}

void cIniFile::addInitalSection(int n)
{
    cIniFile::IniFile.iRecordListLength = n;

    cIniFile::settings.beginGroup("RecordList");
    cIniFile::settings.setValue("root_path", cIniFile::IniFile.getDirectoryPah());
    cIniFile::settings.setValue("length", cIniFile::IniFile.iRecordListLength);
    cIniFile::settings.endGroup();
}
