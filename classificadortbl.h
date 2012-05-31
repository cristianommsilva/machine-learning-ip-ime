#ifndef CLASSIFICADORTBL_H
#define CLASSIFICADORTBL_H

#include "classificador.h"

class ClassificadorTBL : public Classificador
{
    public:
        ClassificadorTBL( );
        virtual ~ClassificadorTBL();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORTBL_H
