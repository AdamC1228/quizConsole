#ifndef QUIZ_H
#define QUIZ_H
#include <QTime>
#include <QVector>
#include <QDebug>
#include "question.h"
#include "filehelper.h"

class quiz
{
public:
    quiz();

    //Methods
    void randomize();
    void start();
    void nextQuestion();
    void checkAnswer(int);
    int setup(QString);

    int setQuizLength(int amount);
    int maxQuestions();
    int numOfChoices();
    int getCurrentQuestion();
    int getCorrect();
    int getWrong();
    int numToAsk();
    QString quizOver();
private:

    //Variables
    int currentQuestion;
    int numCorrect;
    int numIncorrect;
    int numOfQuestionsToAsk;
    fileHelper myHelper;
    QVector<question *> dataArray;
    QTime quizTimer;



};


#endif // QUIZ_H
