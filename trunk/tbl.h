#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "classificadortbl.h"
#include "maisprovavel.h"
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_UTILIZADO "pos"
#define ATRBT_CLASSIFICADO 0

class TBL : public Treinador
{
        Classificador *classInicial;
        int toleranciaScore;
    public:
        TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
