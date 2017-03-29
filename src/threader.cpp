#include "threader.h"
#include <QDebug>

threader::threader(QString file, QString time, QString num)
{
    //Create Thread
    QThread *consoleThread = new QThread();

    //create quiz
    theQuiz = new quiz();

    //Timer for monitoring the quiz time
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),this ,SLOT(quitThread()),Qt::DirectConnection);

    if(time.toInt() <= 0)
    {
        qDebug()<<"Specified time was invalid. Please enter a number greater than 1";
        exit(EXIT_FAILURE);
    }
     timer->start(time.toInt()*1000);



    //Create and run thread for the primary console

     theConsole = new console(file,num,theQuiz);
     theConsole->blockSignals(false);
     theConsole->moveToThread(consoleThread);
     QObject::connect(theConsole,SIGNAL(finished()),this, SLOT(abnormalTermination()));
     theConsole->start();

}
void threader::abnormalTermination()
{
    timer->stop();
    qDebug()<<"\n";
    exit(EXIT_FAILURE);
}

void threader::quitThread()
{
    timer->stop();
    //Sleep the quiz thread
    theConsole->sleep();
    theConsole->exit();

    //Print the score
    qDebug()<<"\n\n";
    qDebug()<<"Oops looks like you ran out of time!\n";
    qDebug().noquote().nospace()<<theQuiz->quizOver();

    exit(EXIT_SUCCESS);
}
