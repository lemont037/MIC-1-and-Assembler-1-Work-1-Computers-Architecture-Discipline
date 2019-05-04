#include <map>

//Recorders
class recor{
	char data;
};
class recorder : recor{
	bool read = false;
	bool write = false;
};
class recorderMar : recor{
	bool write = false;
};
class recorderMbr : recor{
	bool readPart = false;
	bool readComp = false;
};
class recorderH : recor{
	bool write = false;
};

class processador{
	private:
		//ULA comands map
		map<char,int> command = {{'011000',011000},{}}
		//Recorders
		recorderMar MAR;
		recorder MDR;
		recorder PC;
		recorderMbr MBR;
		recorder SP;
		recorder LV;
		recorder CPP;
		recorder TOS;
		recorder OPC;
		recorderH H;
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
		void ULA(char command){
			switch(command){
				case '011000':
				//A
				busC = H.data;
				break;
				case '010100':
				//B
				busC = busB;
				break;
				case '011010':
				//~A

				break;
				case '101100':
				//~B

				break;
				case '111100':
				//A + B

				break;
				case '111101':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				case '':

				break;
				
			}

		}
}