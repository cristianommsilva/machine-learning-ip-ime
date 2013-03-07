#ifndef JANELA_H
#define JANELA_H


#include <QFileDialog>
#include "param.h"
#include "../../corpus/corpusmatrizui.h"
#include "../../treinador/maisprovavel.h"
#include "../../treinador/hmm.h"
#include "../../treinador/tbl.h"
#include "../../validador/validadorteste.h"
#include "../../validador/validadortreino.h"
#include "../../validador/validadorkdobras.h"
#include "../../validador/validadordivisao.h"
#include "../../avaliador/avaliador_acuracia.h"


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
    void executarValidacao();
};

#endif // JANELA_H
