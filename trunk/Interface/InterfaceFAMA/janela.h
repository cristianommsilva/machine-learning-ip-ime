#ifndef JANELA_H
#define JANELA_H


#include <QFileDialog>
#include "param.h"
#include "../../corpus/corpusmatriz.h"
#include "../../classificador/classificador_maisprovavel.h"
#include "../../classificador/classificadorhmm.h"
#include "../../classificador/classificadortbl.h"
#include "../../treinador/maisprovavel.h"
#include "../../treinador/hmm.h"
#include "../../treinador/tbl.h"

namespace Ui {
class Janela;
}

class Janela : public QWidget
{
    Q_OBJECT

public:
    explicit Janela(QWidget *parent = 0);
    ~Janela();

private:
    Ui::Janela *ui;
    Corpus *corpus;
    Treinador *treinador;
    QString s;
    Param popUp;
    void logicaDeAbertura();

public slots:
    void abrirArquivo();
    void habilitarBotao( int index );
    void atributoSelecionado( int row, int column );
    void definirParametros();
    void escolherClassificador( int index );
    void definirParametrosTreinador();
};

#endif // JANELA_H
