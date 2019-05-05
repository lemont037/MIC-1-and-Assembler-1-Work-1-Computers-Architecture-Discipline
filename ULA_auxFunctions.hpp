//ULA arithmetic aux functions

//Adder
//Add one
void addOne(char* A, char* result){
	//Coping the bits
	for(int i = 0; i <= 31; i++)
		result[i] = A[i];
	
	int i = 31;
	while(A[i] != '0' && i > -1)
		i--;
	result[i] = '1';
}
//Full adder
void adder(char* A, char* B, char* sum, bool addOneBool){
	char carryIn = '0';

	for(int i = 31; i >= 0; i--){
		sum[i] = (A[i] ^ B[i]) ^ carryIn;
		carryIn = (carryIn & B[i]) | (carryIn & A[i]) | (A[i] & B[i]);
	}

	if(addOneBool)
		addOne(sum,sum);
}

//Subtractor
//Subtract One
void subOne(char* A, char* result){
	//Coping the bits
	for(int i = 0; i <= 31; i++)
		result[i] = A[i];

	int i = 31;
	while(A[i] != '1' && i > -1){
		result[i] = '1';
		i--;
	}
	result[i] = '0';
}
//Full subtractor
void subtract(char* A, char* B, char* sub, bool subOneBool){
	char carryIn = '0';

	for(int i = 31; i >= 0; i--){
		sub[i] = (A[i] ^ B[i]) ^ carryIn;
		carryIn = (carryIn & B[i]) | (carryIn & ~A[i]) | (~A[i] & B[i]);
	}

	if(subOneBool)
		subOne(sub,sub);
}