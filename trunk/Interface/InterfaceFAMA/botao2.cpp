#include "botao2.h"

Botao2::Botao2(QWidget *parent) :
    QWidget(parent)
{
}

void Botao2::habilitarBotao(int index)
{
    if( index )
        setEnabled( true );
}
