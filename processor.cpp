#include <string>
#include "ULA_auxfunctons.hpp"

//Recorders
class recor{
	char data[32];
};
class recorder : recor{
	bool read;
	bool write;
};
class recorderJW : recor{
	bool write;
};
class recorderDR : recor{
	bool readPart;
	bool readComp;
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
			//Call Decoder to the set as true the recorder that will be read
			char decoderCommand[] = {MIR[32],MIR[33],MIR[34],MIR[35]};
			decoder(decoderCommand);
			//Get the data recorder, with bool read true, to bus B
			if(MDR.read)
				busB = MDR.data;
			else if(PC.read)
				busB = PC.data;
			else if(MBR.read)
				busB = MBR.data;
			else if(SP.read)
				busB = SP.data;
			else if(LV.read)
				busB = LV.data;
			else if(CPP.read)
				busB = CPP.data;
			else if(TOS.read)
				busB = TOS.data;
			else if(OPC.read)
				busB = OPC.data;
			//Call ULA
			char ULACommand[] = {MIR[12],MIR[13],MIR[14],MIR[15],MIR[16],MIR[17],MIR[18],MIR[19]};
			ULA(ULACommand);
			//Set the data recorder, with bool write true, to bus C
			
		}

	private:
		//Decoder
		void decoder(string command){
			MDR.read = false;
			PC.read = false;
			MBR.read = false;
			SP.read = false;
			LV.read = false;
			CPP.read = false;
			TOS.read = false;
			OPC.read = false;
			H.read = false;
			if(command == "0000")
				MDR.read = true;
			else if(command == "0001")
				PC.read = true;
			else if(command == "0010")
				MBR.readPart = true;
			else if(command == "0011")
				MBR.readComp = true;
			else if(command == "0100")
				SP.read = true;
			else if(command == "0101")
				LV.read = true;
			else if(command == "0110")
				CPP.read = true;
			else if(command == "0111")
				TOS.read = true;
			else if(command == "1000")
				OPC.read = true;
		}
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