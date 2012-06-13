#include "tbl.h"

TBL::TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore )
{
    this->classInicial = classInicial;
    this->toleranciaScore = toleranciaScore;
    carregarMolde( arqMoldeRegras );
}

TBL::~TBL()
{
    //dtor
}

Classificador *TBL::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorTBL *objClassificador = new ClassificadorTBL();
    int row = corpus.pegarQtdSentencas(), column, numMoldeRegras = this->moldeRegras.size(), numRegras, qtdAtributos, maxScore = toleranciaScore, maxIndice, aux, aux2;
    map<int, map< int, int > >::iterator linha, linha_end;
    map< int, int >::iterator it, it_end;
    map< int, map< int, int > > var;
    //estrutura de multimap para busca otimizada de regras repetidas
    multimap< map< int, map< int, int > >, int >:: iterator bp, bp_end;
    pair< multimap< map< int, map< int, int > >, int >:: iterator, multimap< map< int, map< int, int > >, int >:: iterator > ret;
    bool moldeInvalido;

    multimap< map< int, map< int, int > >, int > regrasTemporarias;
    set< map< int, map< int, int > > > regrasArmazenadas;
    vector< map< int, map< int, int > > > regras( 1 );
    vector< int > respRegras, good, bad;//se for feita mais de uma classificação simultanea respRegras tem que ser atualizado para map e respMolde tem que ser criado
    vector< map< int, int> > moldeRegras( numMoldeRegras );

    //converter molde de regras
    map< int, string >::iterator itMolde, itMolde_end;
    for( register int i = 0; i < numMoldeRegras; i++ )
    {
        itMolde_end = this->moldeRegras[i].end();
        for( itMolde = this->moldeRegras[i].begin(); itMolde != itMolde_end; itMolde++ )
            moldeRegras[i][itMolde->first] = corpus.pegarPosAtributo( itMolde->second );
    }

    //Classificação inicial do corpus
    classInicial->executarClassificacao( corpus, ATRBT_CLASSIFICADO );

    qtdAtributos = corpus.pegarQtdAtributos();

    int imprime = 0;

    while( maxScore >= toleranciaScore && regras.size() > 0 )
    {
        cout << imprime << endl;
        regras.clear();
        respRegras.clear();
        good.clear();
        bad.clear();
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
                            if( regrasArmazenadas.find( var ) == regrasArmazenadas.end() )
                            {
//                                numRegras = regras.size();
//                                for( register int L = 0; L < numRegras; L++ )
//                                    if( var == regras[L] )
//                                        if( aux == respRegras[L] )
//                                        {
//                                            moldeInvalido = true;
//                                            break;
//                                        }
//                                if( !moldeInvalido )
//                                {
//                                    regras.push_back( var );
//                                    respRegras.push_back( aux );
//                                }
                                ret = regrasTemporarias.equal_range( var );
                                bp_end = ret.second;
                                for( bp = ret.first; bp != bp_end; bp++ )
                                    if( bp->second == aux )
                                    {
                                        moldeInvalido = true;
                                        break;
                                    }
                                if( !moldeInvalido )
                                {
                                    regrasTemporarias.insert( pair< map< int, map< int, int > >, int >( var, aux ) );
                                    regras.push_back( var );
                                    respRegras.push_back( aux );
                                }
                            }
                        }
                        var.clear();
                    }
                }
        }

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
        //impressão da melhor regra
        cout << maxScore << endl;
        linha_end = regras[maxIndice].end();
        for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
        {
            it_end = linha->second.end();
            for( it = linha->second.begin(); it != it_end; it++ )
                cout << corpus.pegarAtributo(it->first) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(it->second) << ' ';
        }
        cout << "=>" << ' ' << corpus.pegarSimbolo(respRegras[maxIndice]) << endl;

        if( maxScore >= toleranciaScore )
        {
            //armazenar regra
            regrasArmazenadas.insert( regras[maxIndice] );
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

bool TBL::carregarMolde( string arqMoldeRegras )
{
    ifstream arqin( arqMoldeRegras.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarMolde!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    string palavra1;
    int posicao;
    char ch ;
    map< int, string > indiceAtributo;

    while( arqin.good() )
    {
        arqin.get( ch );//caso inicial p/ diferenciar de \n
        palavra1.push_back( ch );
        while( ch != '\n' && arqin.good() )
        {
            for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                palavra1.push_back( ch );
            arqin >> posicao;
            indiceAtributo[posicao] = palavra1;
            palavra1.clear();
            arqin.get( ch );
        }
        moldeRegras.push_back( indiceAtributo );
        indiceAtributo.clear();
    }

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarMolde!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Molde de Regras <" << arqMoldeRegras << "> carregado com sucesso!" << endl;
    return true;
}
