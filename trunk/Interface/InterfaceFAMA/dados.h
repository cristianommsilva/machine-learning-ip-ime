#ifndef DADOS_H
#define DADOS_H

#include <QWidget>
#include "../../treinador/treinador.h"
#include "../../avaliador/avaliador.h"

namespace Ui {
class Dados;
}

class Dados : public QWidget
{
    Q_OBJECT
    
public:
    explicit Dados(QWidget *parent = 0);
    ~Dados();
    void definirDados( Treinador *tr, QString nomeTr, int nv, Avaliador *av, QString nomeAv, QString atrbTreino );
    
private:
    Ui::Dados *ui;
    Treinador *treinador;
    Avaliador *avaliador;
    int numValidacao;
    QString atributoTreino;
};

#endif // DADOS_H
