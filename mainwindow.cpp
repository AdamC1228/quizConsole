#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette* paletteGreen = new QPalette();
    paletteGreen->setColor(QPalette::WindowText,"#24a30b");

    QPalette* paletteRed = new QPalette();
    paletteRed->setColor(QPalette::WindowText,"#a30b0b");

    ui->lblCorrect->setPalette(*paletteGreen);
    ui->lblWrong->setPalette(*paletteRed);
    currentQuestion = 0;
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/************************************************************
 ************************************************************
 ************************************************************

                    Logic Methods

 ************************************************************
 ************************************************************
 ***********************************************************/

void MainWindow::startQuiz()
{
    randomize();
    myTimer.start();
    nextQuestion();
}

void MainWindow::on_btnSubmit_clicked()
{
    if(currentQuestion<numofQuestions-1)
    {
        checkAnswer();
        currentQuestion++;
        nextQuestion();
    }
    else
    {
        checkAnswer();
        ui->btnQuit->click();
    }
}

void MainWindow::on_btnQuit_clicked()
{
    finalScore();
    exit(EXIT_SUCCESS);
}

void MainWindow::finalScore()
{
    double percentage = ((ui->lblCorrect->text().toInt()/ numofQuestions) * 100);

    int ms = myTimer.elapsed();
    int s  = ms / 1000;

    QString time = QDateTime::fromTime_t(s).toUTC().toString("hh:mm:ss");

    QMessageBox thankYou;
    thankYou.setWindowTitle("Quiz Over");
    thankYou.setText("Thank you for using the Quizinator 5000. Your final score was as follows: "
                     "\n Correct: \t"+ui->lblCorrect->text() +
                     "\n Incorrect: \t"+ui->lblWrong->text() +
                     "\n Percentage correct was: \t" + QString::number(percentage) +
                     "\n Total Time to complete "+ QString::number(numofQuestions)+" questions was: \t" + time);
    thankYou.exec();
}

void MainWindow::randomize()
{
    int nElms=dataArray.count();
    qDebug()<<"Nelms is: "+ QString::number(nElms);
    int tempElm;
    question *tempQuest;

    for(int i=0; i<nElms-1 ;i++)
    {
        tempElm = rand() % (i + (nElms-i)) ;
        qDebug()<<"The temp elm is: " +QString::number(tempElm);
        tempQuest = dataArray.at(i);

        //Swap elements
        dataArray[i]=dataArray[tempElm];
        dataArray[tempElm]=tempQuest;
    }
}


/************************************************************
 ************************************************************
 ************************************************************

                    Question Methods

 ************************************************************
 ************************************************************
 ***********************************************************/

void MainWindow::nextQuestion()
{
    ui->lblQuestion->setText(dataArray.at(currentQuestion)->getQuestion());


    ui->rdo0->setText(dataArray.at(currentQuestion)->getChoices().at(0));
    ui->rdo1->setText(dataArray.at(currentQuestion)->getChoices().at(1));

    if(2<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo2->setVisible(true);
        ui->rdo2->setText(dataArray.at(currentQuestion)->getChoices().at(2));
    }
    else
        ui->rdo2->setVisible(false);

    if(3<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo3->setText(dataArray.at(currentQuestion)->getChoices().at(3));
        ui->rdo3->setVisible(true);
    }
    else
    {
        ui->rdo3->setVisible(false);
    }

    if(4<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo4->setText(dataArray.at(currentQuestion)->getChoices().at(4));
        ui->rdo4->setVisible(true);
    }
    else
    {
        ui->rdo4->setVisible(false);
    }

    if(5<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo5->setText(dataArray.at(currentQuestion)->getChoices().at(5));
        ui->rdo5->setVisible(true);
    }
    else
    {
        ui->rdo5->setVisible(false);
    }

    if(6<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo6->setText(dataArray.at(currentQuestion)->getChoices().at(6));
        ui->rdo6->setVisible(true);
    }
    else
    {
        ui->rdo6->setVisible(false);
    }

    if(7<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo7->setText(dataArray.at(currentQuestion)->getChoices().at(7));
        ui->rdo7->setVisible(true);
    }
    else
    {
        ui->rdo7->setVisible(false);
    }

    if(8<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo8->setText(dataArray.at(currentQuestion)->getChoices().at(8));
        ui->rdo8->setVisible(true);
    }
    else
    {
        ui->rdo8->setVisible(false);
    }

    if(9<dataArray.at(currentQuestion)->getChoices().count())
    {
        ui->rdo9->setText(dataArray.at(currentQuestion)->getChoices().at(9));
        ui->rdo9->setVisible(true);
    }
    else
    {
        ui->rdo9->setVisible(false);
    }
}

void MainWindow::checkAnswer()
{
    QList<QRadioButton *> allButtons = ui->grpAnswer->findChildren<QRadioButton *>(); //groupBox->findChildren<QRadioButton *>();

    for(int i = 0; i < allButtons.size(); ++i)
    {
        for(int j=0;j<allButtons.size();j++)
        {
            if(allButtons[i]->objectName()==("rdo"+QString::number(j)))
            {
                if(allButtons[i]->isChecked())
                {
                    if(j==(dataArray.at(currentQuestion)->getAnswer()-1))
                    {
                        ui->lblCorrect->setText(QString::number((ui->lblCorrect->text().toInt()+1)));
                    }
                    else
                    {
                        ui->lblWrong->setText(QString::number((ui->lblWrong->text().toInt()+1)));
                    }
                    break;
                }
            }
        }
    }
}


/************************************************************
 ************************************************************
 ************************************************************

                    Setup Functions

 ************************************************************
 ************************************************************
 ***********************************************************/



//Prepair the quiz game.

void MainWindow::setup()
{
    bool incorrectSettings=true;
    greetings start;

    while(incorrectSettings)
    {
        if(start.exec()==QDialog::Accepted)
        {
            setupQuizFile();
            setupQuizLength();
            incorrectSettings=false;
        }
        else
        {
            if (quitPrompt())
            {
                exit(EXIT_FAILURE);
            }
        }
    }

    QMessageBox thankYou;
    thankYou.setWindowTitle("Begin Quiz");
    thankYou.setText("Press OK to begin the quiz.");
    thankYou.exec();

    startQuiz();
}

//Ask the user for the question file for the quiz

void MainWindow::setupQuizFile()
{
    QString fileName;
    do{
        fileName = QString();
        while(fileName.isNull())
        {
            fileName = QFileDialog::getOpenFileName(this,tr("Open Quiz File"), QDir::currentPath(), tr("All Files (*.*)"));
            if(fileName.isNull())
            {
                if (quitPrompt())
                {
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    while(!myHelper.openFile(fileName));

    qDebug()<< "setupQuizFile Function Filename is: " + fileName;


    dataArray = myHelper.getData();
}

//Ask the user for the amount of questions they wish to take for the quiz

void MainWindow::setupQuizLength()
{
    bool ok = false;
    qDebug()<<myHelper.getTotal();

    numofQuestions = QInputDialog::getInt(this,tr("Quiz Length"),"Please specify the quiz length. (Min: 1 Max: " + QString::number(myHelper.getTotal()) + " )",1,1,myHelper.getTotal(),1,&ok);
    if(ok == false)
    {
        if (quitPrompt())
        {
            exit(EXIT_FAILURE);
        }
    }
}


bool MainWindow::quitPrompt()
{
    QMessageBox error("Operation Cancelled",
                          "You have pressed cancel. Are you sure you wish to exit the Quizinator 5000?",
                          QMessageBox::Question,
                          QMessageBox::Yes | QMessageBox::Default,
                          QMessageBox::No | QMessageBox::Escape,
                          QMessageBox::NoButton);
    if (error.exec() == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}




/************************************************************
 ************************************************************
 ************************************************************

                    Removed Code

 ************************************************************
 ************************************************************
 ***********************************************************/



//void MainWindow::nextQuestion()
//{
//        ui->lblQuestion->setText(dataArray.at(currentQuestion)->getQuestion());

//        QList<QRadioButton *> allButtons = ui->grpAnswer->findChildren<QRadioButton *>(); //groupBox->findChildren<QRadioButton *>();

//        sortListAlpha();

//        for(int i = 0; i < allButtons.size(); ++i)
//        {
//            allButtons[i]->setChecked(false);
//            if(i<dataArray.at(currentQuestion)->getChoices().count())
//            {
//                qDebug()<<dataArray.at(currentQuestion)->getChoices().at(i);
//                qDebug()<<allButtons[i]->objectName();
//                qDebug()<<dataArray.at(currentQuestion)->getChoices().count();
//                qDebug()<< " ";

//                allButtons[i]->setText(dataArray.at(currentQuestion)->getChoices().at(i));
//                allButtons[i]->setVisible(true);
//            }
//            else
//            {
//                allButtons[i]->setVisible(false);
//            }
//        }
//}

