#ifndef THREADER_H
#define THREADER_H
#include "console.h"
#include <QTimer>
#include <QString>
#include "quiz.h"

class threader: public QObject
{
    Q_OBJECT
public:
    threader(QString,QString,QString);
protected slots:
    void quitThread();
    void abnormalTermination();
private:
    console *theConsole;
    quiz * theQuiz;
    QTimer *timer;
};

#endif // THREADER_H
