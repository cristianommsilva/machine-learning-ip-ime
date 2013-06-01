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

void Dados::definirDados( Treinador *tr, QString nomeTr, int nv, Avaliador *av, QString nomeAv, QString atrbTreino )
{
    treinador = tr;
    ui->lineEdit_treinador->setText( nomeTr );
    numValidacao = nv;
    ui->comboBox_validacao->setCurrentIndex( nv );
    avaliador = av;
    ui->lineEdit_avaliador->setText( nomeAv );
    atributoTreino = atrbTreino;
    ui->lineEdit_atributo->setText( atrbTreino );
}
