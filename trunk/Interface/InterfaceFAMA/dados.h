#ifndef DADOS_H
#define DADOS_H

#include <QWidget>
#include "../../treinador/treinador.h"

namespace Ui {
class Dados;
}

class Dados : public QWidget
{
    Q_OBJECT
    
public:
    explicit Dados(QWidget *parent = 0);
    ~Dados();
    void definirDados( Treinador *tr, QString nomeTr );
    
private:
    Ui::Dados *ui;
    Treinador *treinador;
};

#endif // DADOS_H
