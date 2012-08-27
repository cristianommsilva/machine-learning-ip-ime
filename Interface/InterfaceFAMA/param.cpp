#include "param.h"
#include "ui_param.h"

Param::Param(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Param)
{
    ui->setupUi(this);
}

Param::~Param()
{
    delete ui;
}

void Param::ajustaModelo( QAbstractItemModel &m )
{
    ui->tableView->setModel(&m);
    ui->tableView->show();
}

QTableView* Param::pegarView()
{
    return ui->tableView;
}
