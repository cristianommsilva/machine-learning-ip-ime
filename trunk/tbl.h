#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "classificadortbl.h"

class TBL : public Treinador
{
        int toleranciaScore;
    public:
        TBL( int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
