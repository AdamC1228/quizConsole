#ifndef GREETINGS_H
#define GREETINGS_H

#include <QDialog>

namespace Ui {
class greetings;
}

class greetings : public QDialog
{
    Q_OBJECT

public:
    explicit greetings(QWidget *parent = 0);
    ~greetings();

private:
    Ui::greetings *ui;
};

#endif // GREETINGS_H
