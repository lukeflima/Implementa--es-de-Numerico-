#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QString>

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void setInf(QString func, double x, double Fx);

private:
    Ui::Form *ui;
};

#endif // FORM_H
