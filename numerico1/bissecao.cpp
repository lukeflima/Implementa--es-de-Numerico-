include "bissecao.h"
#include "ui_bissecao.h"

bissecao::bissecao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bissecao)
{
    ui->setupUi(this);
}

bissecao::~bissecao()
{
    delete ui;
}
