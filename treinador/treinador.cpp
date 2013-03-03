#include "treinador.h"

Treinador::Treinador()
{

}

Treinador::~Treinador()
{
    //dtor
}

Treinador* Treinador::construirJanela( Param &popUp )
{
    ostringstream erro;
    erro << "Construtor de janela nao definido\n";
    throw erro.str();
    return this;
}
