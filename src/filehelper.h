#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QFile>
#include <QDir>
#include <question.h>

class fileHelper
{
public:
    fileHelper();
    bool openFile(QString);
    QString readFile();
    int getTotal();
    QVector<question *> getData();
private:
    QVector<question * > dataArray;
    QFile file;
};

#endif // FILEHELPER_H
