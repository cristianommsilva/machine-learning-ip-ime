#include "modeloparam.h"

ModeloParam::ModeloParam(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int ModeloParam::rowCount(const QModelIndex &parent) const
{
    return Dados.size();
}

int ModeloParam::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ModeloParam::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch( role )
    {
        case Qt::DisplayRole :
            return QString::fromStdString(Dados[row][col].second);
            break;
        case Qt::TextAlignmentRole :
            return Qt::AlignCenter;
            break;
        case Qt::FontRole :
            if( col == 0 )
            {
                QFont boldFont;
                boldFont.setBold( true );
                return boldFont;
            }
    }
    return QVariant();
}

bool ModeloParam::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if( index.column() == 0 ) return false;
    if( role == Qt::EditRole )
    {
        Dados[index.row()][index.column()].second = value.toString().toStdString();
        //emit dataChanged();
    }
    return true;
}

Qt::ItemFlags ModeloParam::flags(const QModelIndex &index) const
{
    if( index.column() != 0 )
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void ModeloParam::inserirDados( int row, int column, std::string v )
{
    if( Dados.size() <= row )
    {
        Dados.resize( row+1 );
        Dados[row].resize( 2 );
    }
    Dados[row][column].first = false;
    Dados[row][column].second = v;
}

void ModeloParam::inserirDados( int row, int column, Param &ct, QWidget *x, std::string aux )
{
    if( Dados.size() <= row )
    {
        Dados.resize( row+1 );
        Dados[row].resize( 2 );
    }
    Dados[row][column].first = true;
    Dados[row][column].second = aux;
    ct.pegarView()->setIndexWidget( index( row, column ), x );
}
