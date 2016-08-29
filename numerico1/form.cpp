#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::setInf(QString func, double x, double Fx){
    ui->func->setText("f(x) = " + func);
    ui->x->setText(QString::number(x));
    ui->fx->setText(QString::number(Fx));
}
