#include "filehelper.h"
#include <QDebug>

fileHelper::fileHelper()
{
}



QString fileHelper::readFile()
{
    return "HELLO";
}

bool fileHelper::openFile(QString filePath)
{
    file.setFileName(filePath);
    file.open(QIODevice::ReadOnly);
    //QTextStream file(&myFile);

    QString temp;
    QString tempQuest;
    int answer;
    QString choice;

    question * tempQuestion;

    try{
        while(!file.atEnd())
        {
            temp=file.readLine().trimmed();
            //qDebug()<<temp;
            if(temp.startsWith("@Q"))
            {
                tempQuestion = new question();
                temp=file.readLine();
                while(!temp.startsWith("@A"))
                {
                    tempQuest+=temp;
                    temp=file.readLine();
                }
                tempQuestion->setQuestion(tempQuest.trimmed());
            }

            if(temp.startsWith("@A"))
            {

                temp = file.readLine().trimmed();
                //Consume Blanks
                while(temp.isNull() || temp.isEmpty())
                {
                      temp = file.readLine().trimmed() ;
                }

                //Se anser
                answer = temp.trimmed().toInt();
                tempQuestion->setAnswer(answer);

                temp=file.readLine().trimmed();
                while(!temp.startsWith("@E"))
                {
                    //Add if not blank
                    if(!(temp.isNull() || temp.isEmpty()))
                    {
                        tempQuestion->addAnswer(temp);
                    }
                    temp = file.readLine().trimmed();
                }

                dataArray.insert(dataArray.length(),tempQuestion);
                tempQuest = "";

            }
        }
    }
    catch(...)
    {
        qDebug() << "Found end of file too early!";
        file.close();
        return false;
    }

    file.close();

    if(dataArray.length()==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


int fileHelper::getTotal()
{
    return dataArray.count();
}

QVector<question *> fileHelper::getData()
{
    return dataArray;
}
