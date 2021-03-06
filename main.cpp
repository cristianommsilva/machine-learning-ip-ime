#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "corpus/corpusmatriz.h"
#include "treinador/maisprovavel.h"
#include "treinador/hmm.h"
#include "treinador/tbl.h"
#include "avaliador/avaliador_acuracia.h"
#include "classificador/classificador_maisprovavel.h"
#include "classificador/classificadorhmm.h"
#include "classificador/classificadortbl.h"

#define LIM_FREQ_UNKNOWN 0
#define ATRBT_ANALISADO 1
#define ATRBT_CLASSIFICADO 0
#define ATRBT_NOVO 3

using namespace std;
//MaisProvavel
//int main()
//{
//    vector<string> atributos;
//    atributos.push_back("word");
//    atributos.push_back("tpos");
//    atributos.push_back("np");
//
//    CorpusMatriz objCorpus( atributos );
//    objCorpus.carregarArquivo( "inputs/train.txt" );
//    objCorpus.criarAtributo( "pos", "N" );
//
//    Classificador *objClass;
//    MaisProvavel objMProv( "word", LIM_FREQ_UNKNOWN );
//    objClass = objMProv.executarTreinamento( objCorpus, ATRBT_ANALISADO );
//    //objClass->carregarConhecimento( "inputs/conhecimentoMProv.txt" );
//
//    CorpusMatriz objCorpusProva( atributos );
//    objCorpusProva.carregarArquivo( "inputs/test.txt" );
//    objCorpusProva.criarAtributo( "pos", "N" );
//
//    objClass->executarClassificacao( objCorpusProva, ATRBT_NOVO );
//    AvaliadorAcuracia objAvalAcur;
//
//    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpusProva, ATRBT_ANALISADO, ATRBT_NOVO )[ 0 ] );
//    objCorpusProva.gravarArquivo( "outputs/corpusGravado.txt" );
//    objClass->gravarConhecimento( "outputs/conhecimentoMProv.txt" );
//    delete objClass;
//
//	return 0;
//}

//HMM
//int main()
//{
//    vector<string> atributos;
//    atributos.push_back("word");
//    atributos.push_back("tpos");
//    atributos.push_back("np");
//
//    CorpusMatriz objCorpus( atributos );
//    objCorpus.carregarArquivo( "inputs/train.txt" );
//    objCorpus.criarAtributo( "pos", "N" );
//
//    Classificador *objClass;
//    HMM objHMM( "word" );
//    objClass = objHMM.executarTreinamento( objCorpus, ATRBT_ANALISADO );
//    //objClass->carregarConhecimento( "inputs/conhecimentoHMM.txt" );
//
//    CorpusMatriz objCorpusProva( atributos );
//    objCorpusProva.carregarArquivo( "inputs/test.txt" );
//    objCorpusProva.criarAtributo( "pos", "N" );
//
//    objClass->executarClassificacao( objCorpusProva, ATRBT_NOVO );
//    AvaliadorAcuracia objAvalAcur;
//
//    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpusProva, ATRBT_ANALISADO, ATRBT_NOVO )[ 0 ] );
//    objCorpusProva.gravarArquivo( "outputs/corpusGravado.txt" );
//    objClass->gravarConhecimento( "outputs/conhecimentoHMM.txt" );
//    delete objClass;
//
//	return 0;
//}

//TBL
//int main()
//{
//    vector<string> atributos, atributosTeste;
//    atributos.push_back("word");
//    atributos.push_back("tpos");
//    atributos.push_back("np");
//
//    CorpusMatriz objCorpus( atributos );
//    objCorpus.carregarArquivo( "inputs/train.txt" );
//    objCorpus.criarAtributo( "pos", "N" );
//
//    Classificador *objClassInicial;
//    HMM objHMM( "word" );
//    objClassInicial = objHMM.executarTreinamento( objCorpus, ATRBT_ANALISADO );
//
//    Classificador *objClass;
//    TBL objTBL( objClassInicial, "inputs/molde.txt", "pos", 2 );
//    objClass = objTBL.executarTreinamento( objCorpus, ATRBT_ANALISADO );
//
//    //Classificador *objClass = new ClassificadorTBL( objClassInicial );
//    //objClass->carregarConhecimento( "inputs/conhecimentoTBL.txt" );
//
//    atributosTeste.push_back( "word" );
//    atributosTeste.push_back( "tpos" );
//    atributosTeste.push_back( "np" );
//
//    CorpusMatriz objCorpusProva( atributosTeste );
//    objCorpusProva.carregarArquivo( "inputs/test.txt" );
//    objCorpusProva.criarAtributo( "pos", "N" );
//
//    objClass->executarClassificacao( objCorpusProva, ATRBT_NOVO );
//    AvaliadorAcuracia objAvalAcur;
//
//    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpusProva, ATRBT_ANALISADO, ATRBT_NOVO )[ 0 ] );
//    objCorpusProva.gravarArquivo( "outputs/corpusGravado.txt" );
//    objClass->gravarConhecimento( "outputs/conhecimentoTBL.txt" );
//    delete objClass;
//
//	return 0;
//}

//Testes gerais
int main()
{
    CorpusMatriz objCorpus;
    objCorpus.carregarArquivo( "inputs/test.txt" );
    objCorpus.criarAtributo( "x", "X" );
    objCorpus.removerAtributo( "adpos" );

    objCorpus.gravarArquivo("outputs/remocaoAtributo.txt");

    return 0;
}
