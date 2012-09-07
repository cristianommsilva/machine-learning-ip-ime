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

void Param::ajustarModelo( QAbstractItemModel &m )
{
    ui->tableView->setModel(&m);
    ui->tableView->show();
}

void Param::iniciarDialog()
{
    ModeloParam *m = ( ModeloParam* )ui->tableView->model();
    int i, tam = m->rowCount();
    parametros.resize( tam );
    for( i = 0; i < tam; ++i )
        if( m->isWidget( i, 1 ) )
            parametros[i].second = ui->tableView->indexWidget( m->index(i,1) );
        else
            parametros[i].first = m->data( m->index(i,1) ).toString().toStdString();
    exec();
}

std::string Param::pegarString( int row )
{
    if( row >= (int)parametros.size() )
    {
        std::ostringstream erro;
        erro << "Erro: pegarString\nDimensao de parametros invalida (" << row << parametros.size() << ')';
        throw erro.str();
    }
    return parametros[row].first;
}

QWidget* Param::pegarWidget( int row )
{
    if( row >= (int)parametros.size() )
    {
        std::ostringstream erro;
        erro << "Erro: pegarWidget\nDimensao de parametros invalida (" << row << parametros.size() << ')';
        throw erro.str();
    }
    return parametros[row].second;
}

QTableView* Param::pegarView()
{
    return ui->tableView;
}

void Param::accept()
{
    ModeloParam *m = ( ModeloParam* )ui->tableView->model();
    int i, tam = m->rowCount();
    parametros.resize( tam );
    for( i = 0; i < tam; ++i )
        if( m->isWidget( i, 1 ) )
            parametros[i].second = ui->tableView->indexWidget( m->index(i,1) );
        else
            parametros[i].first = m->data( m->index(i,1) ).toString().toStdString();
    QDialog::accept();
}

void Param::reject()
{
    (( QCheckBox* )ui->tableView->indexWidget( ui->tableView->model()->index(2,1) ))->setChecked( true );
    QDialog::reject();
}

void Param::escolherAtributos( bool state )
{
    if( state )
    {
        ModeloParam *m = ( ModeloParam* )ui->tableView->model();
        QSpinBox *sbox = ( QSpinBox* )ui->tableView->indexWidget( m->index(3,1) );
        m->removeRows( 4, sbox->value() );
        sbox->setEnabled( false );
        //sbox->setValue(1);
    }
    else
    {
        int aux;
        ModeloParam *m = ( ModeloParam* )ui->tableView->model();
        m->inserirDados( aux = m->rowCount(), 0, "Atributo1" );
        m->inserirDados( aux, 1, "1" );
        ui->tableView->indexWidget( m->index(3,1) )->setEnabled( true );
    }
}

void Param::redimensionarAtributos( int tam )
{
    ModeloParam *m = ( ModeloParam* )ui->tableView->model();
    int aux = m->rowCount();
    if( tam > aux - 4 )
    {
        std::string num = QVariant( m->rowCount() - 3 ).toString().toStdString();
        m->inserirDados( aux, 0, "Atributo" + num );
        m->inserirDados( aux, 1, num );
    }
    else
        m->removeRows( aux-1, 1 );
}
