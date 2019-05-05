#include <string>
#include "ULA_auxfunctons.hpp"

//Recorders
class recor{
	char data[32];
};
class recorder : recor{
	bool read = false;
	bool write = false;
};
class recorderJW : recor{
	bool write = false;
};
class recorderDR : recor{
	bool readPart = false;
	bool readComp = false;
};

class processador{
	private:
		//Recorders
		recorderJW MAR;
		recorder MDR;
		recorder PC;
		recorderDR MBR;
		recorder SP;
		recorder LV;
		recorder CPP;
		recorder TOS;
		recorder OPC;
		recorderJW H;
		char busB;
		char busC;

	public:
		void processar(char MIR){
			//To be implemented
			//Read the MIR's bits array
			//Get the data recorder, with bool read true, to bus B
			//Call ULA
			//Set the data recorder, with bool write true, to bus C
		}

	private:
		//ULA function
		void ULA(string command){
			if(command == "011000"){
				//A
				busC = H.data;
			}else if(command == "010100"){
				//B
				busC = busB;
			}else if(command == "011010"){
				//~A
				busC = ~H.data;
			}else if(command == "101100"){
				//~B
				busC = ~busB;
			}else if(command == "111100"){
				//A + B
				adder(H.data, busB, busC, false);
			}else if(command == "111101"){
				//A + B + 1
				adder(H.data, busB, busC, true);;
			}else if(command == "111001"){
				//A + 1
				addOne(H.data,busC);
			}else if(command == "110101"){
				//B + 1
				addOne(busB,busC);
			}else if(command == "111111"){
				//B - A
				subtract(busB,H.data, busC, false);
			}else if(command == "110110"){
				//B - 1
				subOne(busB,busC);
			}else if(command == "111011"){
				//-A
				busC = -H.data;
			}else if(command == "001100"){
				//A and B
				if(H.data && busB)
					busC = 1;
				else
					busC = 0;
			}else if(command == "011100"){
				//A or B
				if(H.data || busB)
					busC = 1;
				else
					busC = 0;
			}else if(command == "010000"){
				//0
				busC = 0;
			}else if(command == "110001"){
				//1
				busC = 1;
			}else if(command == "110010"){
				//-1
				busC = -1;
			}
		}
}