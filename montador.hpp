#ifndef MONTADOR_HPP_INCLUDED
#define MONTADOR_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>




using namespace std;

typedef unsigned int word;
typedef unsigned char byte;
typedef unsigned short twoByte;



typedef struct mnemonico;
typedef struct label;

void montador(char* nomeASM);
word primeiraLida(char* nomeASM, vector<label>& labels, vector<string>& variaveis, vector <mnemonico>& mnemonicos);
void segundaLida(char* nomeASM, vector<label>& labels, vector<string>& variaveis, vector <mnemonico>& mnemonicos, word length);
vector <mnemonico> criaMne ();
void insereLabel (string nome_label, int posicao, vector<label>& labels);
bool procuraMnemonico (string linha, string mne);
mnemonico extrairOpcode (string linha, vector<mnemonico> mnemonicos);


bool verificaMnemonico (string palavra, vector<mnemonico> mnemonicos);
bool verificaVariavel (string palavra, vector<string> variaveis);
bool verificaLabel (string palavra, vector<label> labels);
byte achaEndereco (string palavra, vector<mnemonico> mnemonicos);
byte achaVariavel (string palavra, vector<string> variaveis);
twoByte achaPosicao (string palavra, vector<label> labels);



#endif // MONTADOR_HPP_INCLUDED
