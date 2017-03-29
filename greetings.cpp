#include "greetings.h"
#include "ui_greetings.h"

greetings::greetings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::greetings)
{
    ui->setupUi(this);
}

greetings::~greetings()
{
    delete ui;
}
