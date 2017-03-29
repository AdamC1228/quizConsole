#include "quiz.h"

quiz::quiz()
{
    numCorrect =0;
    numIncorrect =0;
    currentQuestion = 0;
}
/************************************************************
 ************************************************************
 ************************************************************

                    Question Gen Methods

 ************************************************************
 ************************************************************
 ***********************************************************/

void quiz::nextQuestion()
{
    if(currentQuestion<numOfQuestionsToAsk)
    {
        qDebug().noquote() << " " << dataArray.at(currentQuestion)->getQuestion() << "\n";
        for (int i=0;i<dataArray.at(currentQuestion)->getChoices().count();i++)
        {
            qDebug().noquote() << " "<< (i+1) << ". " <<dataArray.at(currentQuestion)->getChoices().at(i);
        }
    }
    else
    {
        //qDebug().noquote() << "\n You have answered all of the questions at this point";
    }
}



/************************************************************
 ************************************************************
 ************************************************************

                    Logic Methods

 ************************************************************
 ************************************************************
 ***********************************************************/

void quiz::randomize()
{
    int nElms=dataArray.count();
    int tempElm;
    question *tempQuest;

    //Set the seed
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);

    for(int i=0; i<nElms-1 ;i++)
    {
        //Pick a random number between 0 and the maximum elements.
        tempElm = qrand() % (nElms);
        tempQuest = dataArray.at(i);

        //Swap elements
        dataArray[i]=dataArray[tempElm];
        dataArray[tempElm]=tempQuest;
    }
}

void quiz::checkAnswer(int response)
{
        if(dataArray.at(currentQuestion)->getAnswer() == response)
        {
            numCorrect++;
        }
        else
        {
            numIncorrect++;
        }

  currentQuestion++;
}

QString quiz::quizOver()
{
    quizTimer.addSecs(1);

    int ms = quizTimer.elapsed();
    int s  = ms / 1000;
    QString percentage;

    QString time = QDateTime::fromTime_t(s).toUTC().toString("hh:mm:ss");

    if(numIncorrect==0 && numCorrect!=0)
    {
        percentage = "100%";
    }
    else if(numIncorrect==0 && numCorrect==0)
    {
        percentage = "0%";
    }
    else
    {
        percentage = QString::number(((numCorrect /(numOfQuestionsToAsk*1.0))*100)) + "%";
    }

    QString game = "\n\n Thank you for using the quizinator 5000. Your final score was as follows:"+
            QString("\n Number Correct:\n\t") + QString::number(numCorrect) +
            QString("\n Number Incorrect:\n\t") + QString::number(numIncorrect) +
            QString("\n Percentage Correct:\n\t") + percentage +
            QString("\n Total time to complete quiz was:\n\t") + time ;
    return game;
}


/************************************************************
 ************************************************************
 ************************************************************

                    Accessors

 ************************************************************
 ************************************************************
 ***********************************************************/

int quiz::getCorrect()
{
    return numCorrect;
}

int quiz::getWrong()
{
    return numIncorrect;
}

int quiz::maxQuestions()
{
    return myHelper.getTotal();
}

int quiz::numToAsk()
{
    return numOfQuestionsToAsk;
}

int quiz::getCurrentQuestion()
{
    return currentQuestion;
}

int quiz::numOfChoices()
{
    return dataArray.at(currentQuestion)->choices.count();
}

/************************************************************
 ************************************************************
 ************************************************************

                    Setup Functions

 ************************************************************
 ************************************************************
 ***********************************************************/

int quiz::setup(QString temp)
{
    if(!myHelper.openFile(temp))
    {
        return 404;
    }

    if( myHelper.getTotal()==0)
    {
        return 101;
    }

    dataArray = myHelper.getData();

    return 0;
}

int quiz::setQuizLength(int amount)
{
    if(amount>myHelper.getTotal())
        return 102;
    if(amount<=0)
        return 103;

    numOfQuestionsToAsk = amount;

    return 0;
}

void quiz::start()
{
    //qDebug() << "DataArray Count:" << QString::number(dataArray.count());

    randomize();

    quizTimer.start();
    nextQuestion();
}
