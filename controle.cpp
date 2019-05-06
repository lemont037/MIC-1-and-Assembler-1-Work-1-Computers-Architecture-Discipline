#include "controle.hpp"


void controle(char* opcode)
{   microcode rom [512];
    vector <byte> prog; //tem que ser vector pq não sabemos o tamanho do programa
    lerArquivos (prog, *rom);
    for (int i=4; prog.size();i++) //começa do byte 5 pq os 4 primeiros é só o tamanho do programa
    {
        processador(rom [prog[i]]); //na minha cabeça, executa o microprograma pega o endereço da instrução no programa e executa usando o processador
        
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

