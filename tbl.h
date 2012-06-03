#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "classificadortbl.h"
#include "maisprovavel.h"
#include <deque>
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_UTILIZADO "pos"
#define ATRBT_CLASSIFICADO 0

class TBL : public Treinador
{
        int toleranciaScore;
    public:
        TBL( int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
