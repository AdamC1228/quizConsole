#ifndef CONSOLETHREAD_H
#define CONSOLETHREAD_H
#include <QThread>
#include <QMutex>
#include <QStringList>

class consoleThread :QThread
{
    Q_OBJECT
public:
    consoleThread(QString,QString);
    void run();
    void terminate();
private:

    QString file;
    QString num;
};

#endif // CONSOLETHREAD_H
