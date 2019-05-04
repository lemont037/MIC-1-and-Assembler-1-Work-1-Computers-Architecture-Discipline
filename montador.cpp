#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#include "montador.hpp"

using namespace std;

typedef unsigned int word;
typedef unsigned char byte;
typedef unsigned short label;

void montador(char* nomeASM)
{
    ifstream ReadFile;
    ofstream WriteFile("progEmulado.exe", ios::binary);
    ReadFile.open(nomeASM);
    string linha;
    word tam_prog = 19;
    vector <string> mnemonicos {"nop", "iadd", "isub", "iand", "ior", "dup", "pop", "swap", "bipush", "iload", "istore", "wide", "ldc_w", "iinc",
                                "goto", "iflt", "ifeq", "if_icmpeq", "invokevirtual", "ireturn"};
    vector <byte> mne_end {0x01, 0x02, 0x05, 0x08, 0x0B, 0x0E, 0x10, 0x13, 0x19, 0x1C, 0x22, 0x28, 0x32, 0x36,
                           0x3C, 0x43, 0x47, 0x4B, 0x55, 0x6B};
    vector <string> labels {};
    string palavra;
    vector <string> variaveis {};
    int index;

    while (ReadFile.good())
    {
        getline(ReadFile, linha);
        palavra = linha.substr(0, linha.find(' ')); //chega se no começo da linha tem uma label ou só espaço branco

        if (palavra.size() != 0)
        {
            labels.push_back(palavra);
        }

        if (linha.find("istore")!=-1)
        {
            palavra = linha.substr(10, linha.size());
            if (find(variaveis.begin(), variaveis.end(), palavra) == variaveis.end()) // verifica se a palavra já está no vetor de variáveis
            {
                variaveis.push_back(palavra);

            }


        }




    }

    ReadFile.clear();
    ReadFile.seekg(0, ios::beg);


    int cont=0;
    while (ReadFile.good())
    {   cont++;
        ReadFile>>palavra;
        tam_prog++;
    }


    ReadFile.clear();
    ReadFile.seekg(0, ios::beg);
    WriteFile.write((char*) &(tam_prog), sizeof(word));





    //init
    word tmp = 0x7300;
    WriteFile.write((char*) &(tmp), sizeof(word));
    tmp = 0x0006;
    WriteFile.write((char*) &(tmp), sizeof(word));
    tmp = 0x1001;
    WriteFile.write((char*) &(tmp), sizeof(word));
    tmp = 0x0400;
    WriteFile.write((char*) &(tmp), sizeof(word));
    tmp = 0x1001 + variaveis.size();
    WriteFile.write((char*) &(tmp), sizeof(word));

//////////////////////////////fim init

    cont=0;
    while(ReadFile.good())
    {
        ReadFile>>palavra;
        int aux = 0;

        if (verificaPresenca(palavra, mnemonicos)!=mnemonicos.size())
        {
            index = verificaPresenca(palavra, mnemonicos);
            WriteFile.write((char*) &(mne_end.at(index)), sizeof(byte));

        }
        else if (verificaPresenca(palavra, variaveis)!= variaveis.size())
        {
            index = verificaPresenca(palavra, variaveis);
            WriteFile.write((char*) &(index), sizeof(byte));

        }

        else if (verificaPresenca(palavra, labels) != labels.size())
        {

        }


        else //entao é constante
        {
            istringstream iss (palavra);
            iss>>aux;
            WriteFile.write((char*) &(aux), sizeof(byte));

        }
        cont++;
    }




}


int verificaPresenca(string palavra, vector<string> vetor)
{
    return distance(vetor.begin(), find(vetor.begin(), vetor.end(), palavra));
}

bool verify(string palavra, vector<string> vetor)
{
    return distance(vetor.begin(), find(vetor.begin(), vetor.end(), palavra)) != vetor.size();
}








