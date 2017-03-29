#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QVector>
#include <QtAlgorithms>
#include <QRadioButton>
#include "filehelper.h"
#include "question.h"

#include <QTime>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_btnSubmit_clicked();

    void on_btnQuit_clicked();

private:
    Ui::MainWindow *ui;
    int numofQuestions;
    int currentQuestion;
    QString filePath();
    void setup();
    void setupQuizFile();
    void setupQuizLength();
    fileHelper myHelper;
    QVector<question *> dataArray;
    bool quitPrompt();
    void nextQuestion();
    void startQuiz();
    void randomize();
    void checkAnswer();
    QTime myTimer;
        void finalScore();
};

#endif // MAINWINDOW_H
