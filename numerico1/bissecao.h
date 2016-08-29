#ifndef BISSECAO_H
#define BISSECAO_H

#include <QWidget>

namespace Ui {
class bissecao;
}

class bissecao : public QWidget
{
    Q_OBJECT

public:
    explicit bissecao(QWidget *parent = 0);
    ~bissecao();

private:
    Ui::bissecao *ui;
};

#endif // BISSECAO_H
