#ifndef TREINADOR_H
#define TREINADOR_H

#include "../corpus/corpus.h"
#include "../classificador/classificador.h"
#include "../Interface/InterfaceFAMA/modeloparam.h"
#include "../Interface/InterfaceFAMA/param.h"

class Treinador
{
    public:
        Treinador();
        virtual ~Treinador();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo ) = 0;
        virtual Treinador* construirJanela( Param &popUp );
};

#endif // TREINADOR_H
