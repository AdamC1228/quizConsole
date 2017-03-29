#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "threader.h"
#include <QTimer>


int main(int argc, char *argv[])
{
    //Autogen
    QCoreApplication app(argc, argv);

    //CommandLine Argument Setup

    QCoreApplication::setApplicationName("Quizinator 5000");
    QCoreApplication::setApplicationVersion("2.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Quiz taking application");
    parser.addHelpOption();
    parser.addVersionOption();

    //define options
    QCommandLineOption inputFile(QStringList() << "i" << "infile",
            QCoreApplication::translate("main", "Source <file> containing all of the quiz questions."),
            QCoreApplication::translate("main", "file"));

    QCommandLineOption time(QStringList() << "t" << "time",
            QCoreApplication::translate("main", "Time in seconds for the quiz duration. Time must be a postitive integer greater than 1."),"30");

    QCommandLineOption numQuestion (QStringList() << "n" << "number-of-questions",
            QCoreApplication::translate("main", "Sets the amount of questions to be asked. Number of questions must be a positive integer greater than 1. "),"1");

    //default values
    time.setDefaultValue("30");
    numQuestion.setDefaultValue("1");

    //Add options
    parser.addOption(inputFile);
    parser.addOption(time);
    parser.addOption(numQuestion);

    //END COMMANLINE ARGUMENT SETUP



    //Grab and process all the arguments passed to the program
    parser.process(app);

    if(parser.value(inputFile).isEmpty()||parser.value(inputFile).isNull())
    {
        qDebug()<<"ERROR: You must specify at least a file to take this quiz.";
        exit(EXIT_FAILURE);
    }

    threader temp(parser.value(inputFile),parser.value(time),parser.value(numQuestion));


    return app.exec();
}


