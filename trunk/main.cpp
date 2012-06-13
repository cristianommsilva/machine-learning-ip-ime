#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "corpusmatriz.h"
#include "maisprovavel.h"
#include "hmm.h"
#include "tbl.h"
#include "avaliador_acuracia.h"
#include "classificador_maisprovavel.h"
#include "classificadorhmm.h"
#include "classificadortbl.h"

#define LIM_FREQ_UNKNOWN 3
#define ATRBT_ANALISADO 1
#define ATRBT_CLASSIFICADO 0
#define ATRBT_NOVO 3

using namespace std;

int main()
{
    vector<string> atributos;
    atributos.push_back("word");
    atributos.push_back("pos");
    atributos.push_back("adpos");

    // cria um objeto corpus
    CorpusMatriz objCorpus( atributos );
    //objCorpus.carregarArquivo( "inputs/Corpus_Saude_EtiquetadoPOSx.txt" );// CORPUS ANTIGO COMPLETO
    objCorpus.carregarArquivo( "inputs/train.txt" );// NOVO CORPUS (professor)
    //objCorpus.carregarArquivo( "corpusTeste.txt" );// EXTRATO DO CORPUS PARA TESTES

    Classificador *objClass;
    MaisProvavel objMProv( LIM_FREQ_UNKNOWN );
    ///objClass = objMProv.executarTreinamento( objCorpus, ATRBT_ANALISADO );
    ///HMM objHMM;
    //objClass = objHMM.executarTreinamento( objCorpus, ATRBT_ANALISADO );
    //objClass->carregarConhecimento( "outputs/conhecimentoMProv.txt" );
    TBL objTBL( objMProv.executarTreinamento( objCorpus, ATRBT_ANALISADO ), "inputs/molde.txt", 1 );
    objClass = objTBL.executarTreinamento( objCorpus, ATRBT_ANALISADO );

    CorpusMatriz objCorpusProva( atributos );
    //objCorpusProva.carregarArquivo( "inputs/CorpusProva.txt" );
    objCorpusProva.carregarArquivo( "inputs/test.txt" );
    //objCorpusProva.carregarArquivo( "Corpus_Saude_EtiquetadoPOSx.txt" );
    //objCorpusProva.gravarArquivo( "corpusGravado.txt" );
    //objClass->carregarConhecimento("inputs/conhecimentoTeste.txt");
    objClass->executarClassificacao( objCorpusProva, ATRBT_CLASSIFICADO );
    AvaliadorAcuracia objAvalAcur;

    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpusProva, ATRBT_ANALISADO, ATRBT_NOVO )[ 0 ] );
    objCorpusProva.gravarArquivo( "outputs/corpusGravado.txt" );
    objClass->gravarConhecimento( "outputs/conhecimentoTBL.txt" );
    delete objClass;

	return 0;
}
