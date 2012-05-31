#include "tbl.h"

TBL::TBL( int toleranciaScore )
{
    this->toleranciaScore = toleranciaScore;
}

TBL::~TBL()
{
    //dtor
}

Classificador *TBL::executarTreinamento( Corpus &corpus, int atributo )
{
    return NULL;
}
