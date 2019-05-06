#include "controle.hpp"


typedef struct mnemonico
{
    string nome_mne;
    byte mne_end;
    int comprimento;
};


void controle(char* opcode)
{   microcode rom [512];
    vector <byte> prog; //tem que ser vector pq não sabemos o tamanho do programa
    lerArquivos (prog, *rom);
    vector <mnemonico> mnemonicos = criaMne();
    for (int i=4; prog.size();i++) //começa do byte 5 pq os 4 primeiros é só o tamanho do programa
    {
        processador(rom [prog[i]]); //na minha cabeça, executa o microprograma pega o endereço da instrução no programa e executa usando o processador
        i = i+procuraMnemonico(prog[i], mnemonicos) //precisamos avançar o comprimento do mnemonico nos bytes do programa quando usamos variaveis etc


    }


}



void lerArquivos (vector<byte> &prog, microcode &rom)
{
    ifstream ReadMicro;
    ifstream ReadProg;
    ReadMicro.open("microprog.rom", ios::binary);
    ReadProg.open("progEmulado2.exe", ios::binary);

    ReadMicro.read((char*)&rom, 512*sizeof(microcode));//ler microprog
    byte atual;
    while (true)
    {
        ReadProg >> atual;
        if (!ReadProg.good()) // se não fizer assim, ele repete o ultimo byte
        {
            break;
        }

        prog.push_back(atual);
    }

}

int procuraMnemonico(byte endereco, vector<mnemonico> mnemonicos) //retorna comprimento do mnemonico que tá sendo executado no microprograma
{
    for (int i=0; i<mnemonicos.size(); i++)
    {
        if (endereco == mnemonicos[i].mne_end)
        {
            return mnemonicos[i].comprimento;
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


