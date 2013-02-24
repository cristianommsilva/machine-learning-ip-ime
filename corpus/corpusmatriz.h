#ifndef CORPUSMATRIZ_H
#define CORPUSMATRIZ_H

#include <fstream>
#include "corpus.h"

#define INF 0x3f3f3f3f

class CorpusMatriz : public Corpus
{
    private:
        char separador;
        bool dividirExemplos;
    public:
        void ajustarSeparador(char);
        CorpusMatriz( vector<string> atributos = vector<string>(),
                      char separador = '_', bool dividirExemplos = false);
        bool carregarArquivo( string arquivo );
        bool gravarArquivo( string arquivo );
        Corpus* clone();
        Corpus& construirJanela( Param &popUp );
};

#endif // CORPUSMATRIZ_H
