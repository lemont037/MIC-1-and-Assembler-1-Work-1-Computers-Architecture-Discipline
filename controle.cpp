#include "controle.hpp"


void controle(char* opcode)
{   microcode rom [512];
    vector <byte> prog; //tem que ser vector pq não sabemos o tamanho do programa
    lerArquivos (prog, *rom);
    vector <mnemonico> mnemonicos = criaMne();



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

