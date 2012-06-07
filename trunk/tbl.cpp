#include "tbl.h"

TBL::TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore )
{
    this->classInicial = classInicial;
    this->toleranciaScore = toleranciaScore;
}

TBL::~TBL()
{
    //dtor
}

Classificador *TBL::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorTBL *objClassificador = new ClassificadorTBL();
    int row = corpus.pegarQtdSentencas(), column, numMoldeRegras, numRegras, qtdAtributos, maxScore = toleranciaScore, maxIndice, aux, aux2;
    map<int, map< int, int > >::iterator linha, linha_end;
    map< int, int >::iterator it, it_end;
    //deque< map< int, map< int, int > > >::iterator v1,v2,v3; //usado para filtrar regras
    map< int, map< int, int > > var;
    bool moldeInvalido;
    //vector< int > = new Vector corpus.pegarQtdAtributos();
    vector< map< int, map< int, int > > > regras;
    vector< int > respRegras, respMolde, good, bad;//se for feita mais de uma classificação simultanea respMolde tem que ser atualizado para map
    vector< map< int, int> > moldeRegras;
    regras.resize( 1 ); //testar pra ver se não da problema

    //incializar molde de regras
    map< int, int > mprg;
    mprg[-1] = corpus.pegarPosAtributo( "pos" );
    mprg[1] = corpus.pegarPosAtributo( "pos" );
    respMolde.push_back( corpus.pegarPosAtributo( "pos" ) );
    moldeRegras.push_back( mprg );
    numMoldeRegras = moldeRegras.size();

    //Classificação inicial do corpus
    classInicial->executarClassificacao( corpus, ATRBT_CLASSIFICADO );

    qtdAtributos = corpus.pegarQtdAtributos();

    int imprime = 0;

    while( maxScore >= toleranciaScore && regras.size() > 0 )
    {
        cout << imprime << endl;
        regras.clear();
        respRegras.clear();
        //varre corpus criando as regras
        for( register int i = 0; i < row; i++ )
        {
            column = corpus.pegarQtdTokens( i );
            for( register int j = 0; j < column; j++ )
                if( ( aux = corpus.pegarValor(i,j,atributo) ) != corpus.pegarValor(i,j, qtdAtributos - 1) )
                {
                    for( register int L = 0; L < numMoldeRegras; L++ )
                    {
                        moldeInvalido = false;

                        it_end = moldeRegras[L].end();
                        for( it = moldeRegras[L].begin(); it != it_end; it++ )
                        {
                            if( ( aux2 = j + it->first ) >= column || aux2 < 0 )
                            {
                                moldeInvalido = true;
                                break;
                            }
                            var[it->first][it->second] = corpus.pegarValor(i, aux2, it->second);
                        }
                        if( !moldeInvalido )
                        {
                            numRegras = regras.size();
                            for( register int L = 0; L < numRegras; L++ )
                                if( var == regras[L] )
                                {
                                    if( aux == respRegras[L] )
                                    {
                                        moldeInvalido = true;
                                        break;
                                    }
                                }
                            if( !moldeInvalido )
                            {
                                regras.push_back( var );
                                respRegras.push_back( aux );
                            }
                        }
                        var.clear();
                    }
                }
        }
        //tira regras repetidas
//        for( v1 = regras.begin(); v1 != regras.end() - 1; v1++ )
//            for( v2 = v1 + 1; v2 != regras.end(); ){ cout << imprime++ << ' ' << regras.size() << endl;
//                if( *v2 == *v1 ){ v3=v2; v3++; regras.erase( v2 ); v2=v3;}
//                else v2++;}



        numRegras = regras.size();
        good.resize( numRegras );
        bad.resize( numRegras );
        cout << numRegras << endl;


//        for( register int L = 0; L < numRegras; L++ )
//        {
//            linha_end = regras[L].end();
//            for( linha = regras[L].begin(); linha != linha_end; linha++ )
//            {
//                it_end = linha->second.end();
//                for( it = linha->second.begin(); it != it_end; it++ )
//                    cout << corpus.pegarAtributo(it->first) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(it->second) << ' ';
//            }
//            cout << "=>" << ' ' << corpus.pegarSimbolo(respRegras[L]) << endl;
//        }
        ///varre corpus aplicando as regras e computando o score
        //é melhor varrer o corpus para cada regra ou em cada palavra do corpus verificar todas as regras?
        /*for( register int L = 0; L < numMoldeRegras; L++ )
            for( register int i = 0; i < row; i++ )
            {
                column = corpus.pegarQtdTokens( i );
                for( register int j = 0; j < column; j++ )

            }*/

        for( int i = 0; i < row; i++ )
        {
            column = corpus.pegarQtdTokens( i );
            for( int j = 0; j < column; j++ )
                for( int L = 0; L < numRegras; L++ )
                {
                    moldeInvalido = false;

                    linha_end = regras[L].end();
                    for( linha = regras[L].begin(); linha != linha_end; linha++ )
                    {
                        //tirar esse if em um loop individual?
                        if( ( aux = j + linha->first ) >= column || aux < 0 )
                        {
                            moldeInvalido = true;
                            break;
                        }
                        it_end = linha->second.end();
                        for( it = linha->second.begin(); it != it_end; it++ )
                            if( corpus.pegarValor(i,aux,it->first) != it->second )
                            {
                                moldeInvalido = true;
                                break;
                            }
                        if( moldeInvalido ) break;
                    }
                    if( !moldeInvalido )
                    {
                        if( ( aux = corpus.pegarValor(i,j,atributo) ) == respRegras[L] && aux != corpus.pegarValor(i,j, qtdAtributos - 1) )
                            good[L]++;
                        if( aux != respRegras[L] && aux == corpus.pegarValor(i,j, qtdAtributos - 1) )
                            bad[L]++;
                    }
                }
        }

//        for( register int L = 0; L < numRegras; L++ )
//            cout << good[L] << ' ' << bad[L] << endl;

        maxScore = -999999999;

        for( register int L = 0; L < numRegras; L++ )
            if( ( aux = good[L] - bad[L] ) > maxScore )
            {
                maxScore = aux;
                maxIndice = L;
            }
        cout << maxScore << endl;

        if( maxScore >= toleranciaScore )
        {
            //armazenar regra
            map< int, map< string, string > > rule;
            linha_end = regras[maxIndice].end();
            for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
            {
                it_end = linha->second.end();
                for( it = linha->second.begin(); it != it_end; it++ )
                    rule[linha->first][corpus.pegarAtributo( it->first )] = corpus.pegarSimbolo( it->second );
            }
            objClassificador->inserirRegra( rule, corpus.pegarSimbolo( respRegras[maxIndice] ) );
            //atualizar Corpus com a nova regra
            for( register int i = 0; i < row; i++ )
            {
                column = corpus.pegarQtdTokens( i );
                for( register int j = 0; j < column; j++ )
                {
                    moldeInvalido = false;

                    linha_end = regras[maxIndice].end();
                    for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
                    {
                        //tirar esse if em um loop individual?
                        if( ( aux = j + linha->first ) >= column || aux < 0 )
                        {
                            moldeInvalido = true;
                            break;
                        }
                        it_end = linha->second.end();
                        for( it = linha->second.begin(); it != it_end; it++ )
                            if( corpus.pegarValor(i,aux,it->first) != it->second )
                            {
                                moldeInvalido = true;
                                break;
                            }
                        if( moldeInvalido ) break; //break externo
                    }
                    if( !moldeInvalido )
                        corpus.ajustarValor(i,j,qtdAtributos - 1,respRegras[maxIndice]);
                }
            }
        }
        cout << imprime++ << endl;
    }

    return objClassificador;
}
