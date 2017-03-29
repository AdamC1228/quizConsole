#ifndef QUESTION_H
#define QUESTION_H

#include <QVector>
#include <QString>


class question
{
public:
    question();
    QString theQuestion;
    int answer;
    QVector<QString> choices;
    void addAnswer(QString temp);
    void setQuestion(QString temp);
    void setAnswer(int temp);
    int getAnswer();
    QString getQuestion();
    QVector<QString> getChoices();
};

#endif // QUESTION_H
