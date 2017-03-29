#include "console.h"

console::console(QString file, QString num, quiz *temp) : in(stdin)
{
    myQuiz=temp;
    filePath=file;
    tempNum=num.toInt();
}

void console::sleep()
{
    usleep(10000);
}

void console::run()
{
    //Call primary setup stub method
    initializeQuiz();
}

/************************************************************
 ************************************************************
 ************************************************************

                    Quiz Functions

 ************************************************************
 ************************************************************
 ***********************************************************/

void console::beginQuiz()
{


    qDebug() << " Welcome to the quizinator 5000! Thank you for choosing this software\n" <<
           "for your quiztaking needs.";

    qDebug() << "\n Your quiz has been setup. Good luck!";
    //in.readLine();

    //Initial question
    qDebug().noquote().nospace()<< "\n\nQuestion " + QString::number(myQuiz->getCurrentQuestion()+1) + " of " + QString::number(myQuiz->numToAsk());
    myQuiz->start();

    //Keep asking questions till we run out
    do
    {
        answer();

        if(myQuiz->numToAsk()>myQuiz->getCurrentQuestion())
        {
            score();
            qDebug().noquote().nospace()<< "\n\n" ;
            qDebug().noquote().nospace()<< "Question " + QString::number(myQuiz->getCurrentQuestion()+1) + " of " + QString::number(myQuiz->numToAsk());
        }

        myQuiz->nextQuestion();

    }while(myQuiz->numToAsk()>myQuiz->getCurrentQuestion());

    //Quiz is now over
    endQuiz();
}

void console::endQuiz()
{
    qDebug().noquote().nospace() << myQuiz->quizOver();
}


void console::answer()
{
    int value;
    bool status=false;

    qDebug()<<"\n Please enter the number only for the answer of your choice:";

    do
    {
        value = in.readLine().toInt(&status);

        if(status == false)
        {
            qDebug().noquote() << "\n It would seem you did not enter a valid option. Please enter only\n" <<
                                    "the integer (number) of your choice listed above." ;
        }
        else if((value<1) || (value > myQuiz->numOfChoices()))
        {
            qDebug().noquote() << "\n You chose an answer outside of the valid options. In order to continue \n" <<
                                    "you must chose a valid option.";
        }
    }while((value<1) || (value > myQuiz->numOfChoices()) );


    myQuiz->checkAnswer(value);


}

void console::score()
{
    qDebug() <<"\n";

    qDebug().noquote().nospace()<< "Current number correct is: \t" << QString::number(myQuiz->getCorrect());
    qDebug().noquote().nospace()<< "Current number incorrect is: \t" << QString::number(myQuiz->getWrong());

    //qDebug().noquote().nospace()<< "Current number correct is: \t" << "\e[32m" << QString::number(myQuiz->getCorrect());
    //qDebug().noquote().nospace()<< "Current number incorrect is: \t" << "\e[93m" << QString::number(myQuiz->getWrong());
}


/************************************************************
 ************************************************************
 ************************************************************

                    Setup Functions

 ************************************************************
 ************************************************************
 ***********************************************************/

//Primary Setup stub
void console::initializeQuiz()
{
    if(tempNum <= 0)
    {
        qDebug()<<"The time must be a positive integer greater than 1.";
        return;
    }

    //If File is invalid Exit
    QFileInfo check(filePath.trimmed());

    if(!(check.exists() || !check.isFile()))
    {
        qDebug()<<"Invalid file.";
        return;
    }

    myQuiz->setup(filePath.trimmed());

    //If there are no questions to ask exit
    if(myQuiz->maxQuestions()==0)
    {
        qDebug() << "\n Since the quiz file you chose has no valid questions the program will\n"<<
                              "now exit. Thank you and have a great day.";
        return;
    }


    int result = myQuiz->setQuizLength(tempNum);
    //If we select an invalid number of questions exit
    if(result == 102)
         {
             qDebug().noquote() << "\n You exceeded the number of available questions.\n";
             return;
         }
         else if(result == 103)
         {
             qDebug().noquote() << "\n You chose a quiz length of 0 or less.\n" ;
             return;
         }
         else if(result != 0)
         {
             qDebug().noquote() << "\n It would seem you did not enter a valid quiz length.\n";
             return;
         }

        beginQuiz();
}
