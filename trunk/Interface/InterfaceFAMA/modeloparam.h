#ifndef MODELOPARAM_H
#define MODELOPARAM_H

#include <QAbstractTableModel>
#include <QFont>
#include <QCheckBox>
#include <QTableView>
#include <vector>
#include "param.h"

class Param;

class ModeloParam : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModeloParam(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const ;
    void inserirDados( int row, int column, std::string v );
    void inserirDados(int row, int column, Param &ct, QWidget *x, std::string aux = "" );
signals:
    
public slots:

private:
    std::vector< std::vector< std::pair<bool, std::string > > > Dados;
    
};

#endif // MODELOPARAM_H
