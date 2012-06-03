#ifndef CLASSIFICADORTBL_H
#define CLASSIFICADORTBL_H

#include "classificador.h"
#include "maisprovavel.h"
#include <fstream>
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_ANALISADO 1

class ClassificadorTBL : public Classificador
{
        vector< map< int, map< string, string > > > regras;
        vector< string > respRegras;
    public:
        ClassificadorTBL( );
        virtual ~ClassificadorTBL();
        void inserirRegra( map< int, map< string, string > > rule, string resp );
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORTBL_H
