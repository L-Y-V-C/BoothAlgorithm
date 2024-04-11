#include<iostream>
#include<bitset>
#include<math.h>
#include<iomanip>

void toBinary(int num, int *bin, int bitQnty);
void printBinary(int *bin, int bitQnty);
void nor(int *bin, int bitQnty);
void plus1(int *bin, int bitQnty);
void plusAwithM(int *bin1, int *bin2, int bitQnty);
void fillA(int *bin, int bitQnty);
void BoothAlgorithm(int *binA, int *binQ, int *binM, int *binMinusM, int bitQnt);
void printCicles(int *binA, int *binQ, int Q1, int *binM, int bitQnt);
void arithmeticShift(int *binA, int *binQ, int &Q1, int bitQnt);
void copyM(int *binM1, int *binM2, int bitQnt);

void toBinary(int num, int *bin, int bitQnty){
	int q, r, c;
	c = 0;
	for(int i=bitQnty-1; 0<=i; i--){
		bin[i]=num%2;
		num = num/2;
	};
	return;
}

void printBinary(int *bin, int bitQnty){
	for(int i=0; i<bitQnty; i++){
		std::cout<<bin[i];
	}
	return;
}

void nor(int *bin, int bitQnty){
	//std::cout<<"NOR aplicado:\n";
	for(int i=0; i<bitQnty; i++){
		bin[i] = bin[i] ^ 1;
	}
	return;
}

void plus1(int *bin, int bitQnty){
	int bit1[bitQnty];
	int c1, add;
	c1 = 0;
	//std::cout<<"Sumando:\n";
	for(int i=0; i<bitQnty; i++){
		bit1[i] = 0;
	}
	bit1[bitQnty-1] = 1;

	for(int i=bitQnty-1; 0<=i; i--){
		add = ((bin[i] ^ c1) ^ bit1[i]);
		c1 = ((bin[i] & bit1[i]) | (bin[i] & c1) | (bit1[i] & c1));
		bin[i] = add;
	}
	//printf(" <- resultado\n");
	return;
}

void plusAwithM(int *bin1, int *bin2, int bitQnty){
	int c1, add;
	c1 = 0;
	for(int i=bitQnty-1; 0<=i; i--){
		add = ((bin1[i] ^ c1) ^ bin2[i]);
		c1 = ((bin1[i] & bin2[i]) | (bin1[i] & c1) | (bin2[i] & c1));
		bin1[i] = add;
		//printf("%d %d\n",bin[i], c1);
	}
	//std::cout<<"A: ";
	return;
}

void fillA(int *bin, int bitQnty){
	for(int i=0; i<bitQnty; i++){
		bin[i] = 0;
	}
}

void BoothAlgorithm(int *binA, int *binQ, int *binM, int *binMinusM, int bitQnt){
	int Q1, count, width;
	Q1 = 0;
	count = bitQnt;
	width = bitQnt+2;
	std::cout<<"\n"<<std::setw(width)<<"A"<<std::setw(width)<<"Q"<<
		std::setw(5)<<"Q-1"<<std::setw(width)<<"M\n";
	std::cout<<"-------------------------------------------------------\n";
	while(count!=0){
		printCicles(binA, binQ, Q1, binM, bitQnt);
		if( Q1==binQ[bitQnt-1] ){
			std::cout<<"   Arith shift\n";
		}else if( Q1<binQ[bitQnt-1] ){
			std::cout<<"   A = A - M\n";
			plusAwithM(binA, binMinusM, bitQnt);
			printCicles(binA, binQ, Q1, binM, bitQnt);
			std::cout<<"   Arith shift\n";
		}else{
			std::cout<<"   A = A + M\n";
			plusAwithM(binA, binM, bitQnt);
			printCicles(binA, binQ, Q1, binM, bitQnt);
			std::cout<<"   Arith shift\n";
		}
		arithmeticShift(binA, binQ, Q1, bitQnt);
		count--;
	}
	std::cout<<"\n";
	printCicles(binA, binQ, Q1, binM, bitQnt);
	return;
}

void printCicles(int *binA, int *binQ, int Q1, int *binM, int bitQnt){
	int width;
	width = bitQnt+2;
	std::cout<<"  ";
	printBinary(binA, bitQnt);
	std::cout<<"  ";
	printBinary(binQ, bitQnt);
	std::cout<<std::setw(5)<<Q1<<"  ";
	printBinary(binM, bitQnt);
	//std::cout<<"\n";

	return;
}

void arithmeticShift(int *binA, int *binQ, int &Q1, int bitQnt){
	int ext, tmp1, tmp2;
	Q1 = binQ[bitQnt-1];
	tmp1 = binA[bitQnt-1];
	tmp2 = binA[0];
	for(int i=bitQnt-1; 0<=i; i--){
		binQ[i] = binQ[i-1];
		binA[i] = binA[i-1];
	}
	binQ[0] = tmp1;
	binA[0] = tmp2;
	return;
}

void copyM(int *binM1, int *binM2, int bitQnt){
	for(int i=0; i<bitQnt; i++){
		binM2[i] = binM1[i];
	}
	return;
}

int
main()
{
	int m, q, bitQnt;

	std::cout<<"Ingresar cantidad de bits a usar: ";
	std::cin>>bitQnt;

	int binaryM[bitQnt];
	int binaryMinusM[bitQnt];
	int binaryQ[bitQnt];
	int binaryA[bitQnt];

	fillA(binaryA, bitQnt);

	std::cout<<"Ingresar multiplicando(M): ";
	std::cin>>m;
	std::cout<<"Ingresar multiplicador(Q): ";
	std::cin>>q;

	toBinary(m, binaryM, bitQnt);
	toBinary(q, binaryQ, bitQnt);

	copyM(binaryM, binaryMinusM, bitQnt);
	nor(binaryMinusM, bitQnt);
	plus1(binaryMinusM, bitQnt);
	//std::cout<<"M: ";
	//printBinary(binaryM, bitQnt);
	//std::cout<<"Q: ";
	//printBinary(binaryQ, bitQnt);

	BoothAlgorithm(binaryA, binaryQ, binaryM, binaryMinusM, bitQnt);

	printf("\n");

	return 0;
}
