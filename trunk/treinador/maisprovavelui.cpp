#include "maisprovavelui.h"

MaisProvavelUI::MaisProvavelUI( string atributoBase, int toleranciaUnknow )
    :MaisProvavel( atributoBase, toleranciaUnknow )
{
}

Treinador* MaisProvavelUI::construirJanela( void *popUp, Corpus &corpus )
{
    Param *popUpPointer = ( Param * )popUp;
    ModeloParam model;
    QStringList sList;
    vector< string > atributos = corpus.pegarAtributos();
    int ok, qtdAtributos = atributos.size();

    model.inserirDados(0,0,"Atributo base:");
    model.inserirDados(1,0,"Tolerancia desconhecido:");

    popUpPointer->ajustarModelo( model );

    //inserção Widgets
    QComboBox *comboBox = new QComboBox();
    for( register int i = 0; i < qtdAtributos; ++i ) sList << QString::fromStdString( atributos[i] );
    comboBox->insertItems( 0, sList );
}
