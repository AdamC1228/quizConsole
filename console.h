#ifndef CONSOLE_H
#define CONSOLE_H
#include <QDebug>
#include "quiz.h"
#include <QFileInfo>
#include <QThread>

class console : public QThread
{
    Q_OBJECT
public:
    console(QString,QString,quiz*);
    quiz *myQuiz;
    void endQuiz();
    void sleep();
    void run();
private:

    //Variables
    QTextStream in;
    QString filePath;
    QStringList temp;
    int tempNum;
    bool termNow = false;


    int getQuizLength();
    QString getFile();
    void initializeQuiz();
    void beginQuiz();
    void answer();
    void score();
    \
};

#endif // CONSOLE_H
