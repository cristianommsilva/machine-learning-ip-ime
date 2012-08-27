#ifndef PARAM_H
#define PARAM_H

#include <QDialog>
#include <QAbstractItemModel>
#include <vector>
#include "modeloparam.h"

namespace Ui {
class Param;
}

class Param : public QDialog
{
    Q_OBJECT
    
public:
    explicit Param(QWidget *parent = 0);
    ~Param();
    void ajustaModelo( QAbstractItemModel &m );

    std::vector< std::vector< std::string > > parametros;
private:
    Ui::Param *ui;
    QTableView* pegarView();

    friend class ModeloParam;
};

#endif // PARAM_H
