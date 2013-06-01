#include "dados.h"
#include "ui_dados.h"

Dados::Dados(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dados)
{
    ui->setupUi(this);
}

Dados::~Dados()
{
    delete ui;
}

void Dados::definirDados( Treinador *tr, QString nomeTr )
{
    treinador = tr;
    ui->lineEdit_treinador->setText( nomeTr );
}
