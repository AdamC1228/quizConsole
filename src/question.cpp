#include "question.h"

question::question()
{
    theQuestion = "";
    answer = -1;
}

void question::setQuestion(QString temp)
{
    theQuestion = temp;
}

void question::setAnswer(int temp)
{
    answer = temp;
}

void question::addAnswer(QString temp)
{
    choices.insert(choices.length(),temp);
}

int question::getAnswer()
{
    return answer;
}

QString question::getQuestion()
{
    return theQuestion;
}

QVector<QString> question::getChoices()
{
    return choices;
}
