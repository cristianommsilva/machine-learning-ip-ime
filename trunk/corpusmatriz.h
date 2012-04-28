#ifndef CORPUSMATRIZ_H
#define CORPUSMATRIZ_H

#include <fstream>
#include "corpus.h"

#define INF 0x3f3f3f3f

class CorpusMatriz : public Corpus
{
    public:
        CorpusMatriz( vector<string> atributos );
        virtual bool carregarArquivo( string arquivo );
        virtual bool gravarArquivo( string arquivo );
};

#endif // CORPUSMATRIZ_H
