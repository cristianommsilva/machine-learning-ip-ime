#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "classificadortbl.h"
#include "maisprovavel.h"
#include "regra.h"
#include <algorithm>
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_UTILIZADO "pos"
#define ATRBT_CLASSIFICADO 0

class TBL : public Treinador
{
        Classificador *classInicial;
        int toleranciaScore;
        vector< multimap< int, string > > moldeRegras;
        bool carregarMolde( string arqMoldeRegras );
        bool salvarEstado( string saveFile, vector< Regra > regras );
        bool carregarEstado( string saveFile, vector< Regra > &regras );
    public:
        TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
