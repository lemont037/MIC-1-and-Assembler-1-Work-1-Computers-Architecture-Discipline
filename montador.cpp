#include "montador.hpp"


typedef unsigned int word;
typedef unsigned char byte;
typedef unsigned short twoByte;



typedef struct mnemonico
{
    string nome_mne;
    byte mne_end;
    int comprimento;
};

typedef struct label
{
    string nome_label;
    twoByte posicao;

};





void montador(char* nomeASM)
{
    vector <mnemonico> mnemonicos = criaMne();
    vector <label> labels = {};
    vector <string> variaveis = {};
    word length;
    length = primeiraLida(nomeASM, labels, variaveis, mnemonicos);
    segundaLida (nomeASM, labels, variaveis, mnemonicos, length);



}


word primeiraLida(char* nomeASM, vector<label>& labels, vector<string>& variaveis, vector <mnemonico>& mnemonicos)
{
    ifstream ReadFile;
    ReadFile.open(nomeASM);
    ofstream WriteFile("progEmulado2.exe", ios::binary); //abre arquivos


    string linha, variavel, aux;
    mnemonico opcode;

    word length = 20;
    twoByte posicao;

    while (ReadFile.good())
    {
        getline(ReadFile, linha);
        aux = linha.substr(0, linha.find(' '));

        if (aux.size() != 0 ) //linha é rotulada?
        {   posicao = length-20;
            insereLabel(aux, posicao, labels); //-20 da inicialização

        }

        if (procuraMnemonico(linha, "istore")) // existe uma variável na linha?
        {
            aux = linha.substr(10, linha.size());
            if (find(variaveis.begin(), variaveis.end(), aux) == variaveis.end()) // verifica se a palavra já está no vetor de variáveis
            {
                variaveis.push_back(aux);

            }

        }
        if (linha.size()!=0 ) // aparentemente, existe uma linha sem nada escrito (provavelmente a ultima)
        {
            opcode = extrairOpcode (linha, mnemonicos);
            length = length + opcode.comprimento;
        }






    }

    ReadFile.clear();
    ReadFile.seekg(0, ios::beg);
    return length;


}

void segundaLida(char* nomeASM, vector<label>& labels, vector<string>& variaveis, vector <mnemonico>& mnemonicos, word length)
{
    ifstream ReadFile;
    ReadFile.open(nomeASM);
    ofstream WriteFile("progEmulado2.exe", ios::binary); //abre arquivos


    string linha, variavel, aux;
    word posicao = 0;
    twoByte posicaoLabel;
    mnemonico opcode;
    byte escreve;
    int aux1;
    WriteFile.write((char*) &(length), sizeof(word));
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
    while (true)
    {
        ReadFile >> aux;
        if (!ReadFile.good()) // se não fizer assim, ele repete o ultimo byte
        {
            break;
        }


        if (verificaMnemonico(aux, mnemonicos)) //palavra é mnemonico
        {
            escreve = achaEndereco (aux, mnemonicos);
            WriteFile.write((char*) &(escreve), sizeof(byte));
            posicao++;

        }

        else if (verificaVariavel(aux, variaveis)) //palavra é variável
        {
            escreve = achaVariavel (aux, variaveis);
            WriteFile.write((char*) &(escreve), sizeof(byte));
            posicao++;
        }

        else if (verificaLabel(aux, labels)) //palavra é label
        {
            posicaoLabel = achaPosicao(aux, labels);
            if (posicaoLabel != posicao)
            {
                posicaoLabel = (posicaoLabel - posicao) + 1;
                posicaoLabel = posicaoLabel * 256; //inverter a ordem dos bytes
                WriteFile.write((char*) &(posicaoLabel), sizeof(twoByte));
                posicao = posicao + 2;
            }


        }

        else //então é constante
        {
            istringstream iss (aux);
            iss>>aux1;
            WriteFile.write((char*) &(aux1), sizeof(byte));
            posicao++;
        }





    }


}




vector <mnemonico> criaMne ()
{
    vector <mnemonico> mnemonicos;
    mnemonico tmp;
    tmp.nome_mne = "nop";
    tmp.comprimento = 1;
    tmp.mne_end=0x01;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "iadd";
    tmp.comprimento = 1;
    tmp.mne_end=0x02;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "isub";
    tmp.comprimento = 1;
    tmp.mne_end=0x05;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "iand";
    tmp.comprimento = 1;
    tmp.mne_end=0x08;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "ior";
    tmp.comprimento = 1;
    tmp.mne_end=0x0B;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "dup";
    tmp.comprimento = 1;
    tmp.mne_end=0x0E;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "pop";
    tmp.comprimento = 1;
    tmp.mne_end=0x10;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "swap";
    tmp.comprimento = 1;
    tmp.mne_end=0x13;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "bipush";
    tmp.comprimento = 2;
    tmp.mne_end=0x19;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "iload";
    tmp.comprimento = 2;
    tmp.mne_end=0x1C;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "istore";
    tmp.comprimento = 2;
    tmp.mne_end=0x22;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "wide";
    tmp.comprimento = 1;
    tmp.mne_end=0x28;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "ldc_w";
    tmp.comprimento = 2;
    tmp.mne_end=0x32;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "iinc";
    tmp.comprimento = 3;
    tmp.mne_end=0x36;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "goto";
    tmp.comprimento = 3;
    tmp.mne_end=0x3C;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "iflt";
    tmp.comprimento = 3;
    tmp.mne_end=0x43;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "ifeq";
    tmp.comprimento = 3;
    tmp.mne_end=0x47;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "if_icmpeq";
    tmp.comprimento = 3;
    tmp.mne_end=0x4B;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "invokevirtual";
    tmp.comprimento = 3;
    tmp.mne_end=0x55;
    mnemonicos.push_back(tmp);
    tmp.nome_mne = "ireturn";
    tmp.comprimento = 3;
    tmp.mne_end=0x6B;
    mnemonicos.push_back(tmp);
    return mnemonicos;
}

void insereLabel (string nome_label, int posicao, vector<label> & labels)
{
    label tmp;
    tmp.nome_label = nome_label;
    tmp.posicao = posicao;
    labels.push_back(tmp);
}

bool procuraMnemonico (string linha, string mne)
{
    return (linha.find(mne)!=-1);
}

mnemonico extrairOpcode (string linha, vector<mnemonico> mnemonicos)
{
    for (int i=0; i<mnemonicos.size(); i++)
    {
        if (procuraMnemonico(linha, mnemonicos[i].nome_mne))
        {
            return mnemonicos[i];
        }
    }
}

bool verificaMnemonico (string palavra, vector<mnemonico> mnemonicos)
{
    for (int i=0; i<mnemonicos.size(); i++)
    {
        if (palavra == mnemonicos[i].nome_mne)
        {
            return true;
        }
    }

    return false; //qualquer endereço que não exista nos mnemonicos;
}

bool verificaVariavel (string palavra, vector<string> variaveis)
{
    return distance(variaveis.begin(), find(variaveis.begin(), variaveis.end(), palavra)) != variaveis.size();
}

bool verificaLabel (string palavra, vector<label> labels)
{
    for (int i=0; i<labels.size(); i++)
    {
        if (palavra == labels[i].nome_label)
        {
            return true;
        }
    }

    return false;
}


byte achaEndereco (string palavra, vector<mnemonico> mnemonicos)
{
    for (int i=0; i<mnemonicos.size(); i++)
    {
        if (palavra == mnemonicos[i].nome_mne)
        {
            return mnemonicos[i].mne_end;
        }
    }
}

byte achaVariavel (string palavra, vector<string> variaveis)
{
    for (int i=0; i<variaveis.size(); i++)
    {
        if (palavra == variaveis[i])
        {
            return i;
        }
    }
}

twoByte achaPosicao (string palavra, vector<label> labels)
{
    for (int i=0; i<labels.size(); i++)
    {
        if (palavra == labels[i].nome_label)
        {
            return labels[i].posicao;
        }
    }

}
