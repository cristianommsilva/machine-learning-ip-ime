#ifndef CLASSIFICADORTBL_H
#define CLASSIFICADORTBL_H

#include "classificador.h"
#include <fstream>

class ClassificadorTBL : public Classificador
{
        vector< map< string, string > > regras;
        vector< map< string, string > > respRegras;
    public:
        ClassificadorTBL( );
        virtual ~ClassificadorTBL();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORTBL_H
