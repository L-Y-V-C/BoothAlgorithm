#include<iostream>
#include<bitset>
#include<math.h>

void toBinary(int num, int *bin, int bitQnty);
void increaseArraySize(int *bin, int bitQnty);
void nor(int *bin, int bitQnty);

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
	std::cout<<"\n";
	return;
}

void nor(int *bin, int bitQnty){
	for(int i=0; i<bitQnty; i++){
		bin[i] = bin[i] ^ 1;
	}
	std::cout<<"\n";
	return;
}

void plus1(int *bin, int bitQnty){
	int bit1[bitQnty];
	int c1, add;
	c1 = 0;
	for(int i=0; i<bitQnty; i++){
		bit1[i] = 0;
	}
	bit1[bitQnty-1] = 1;

	for(int i=0; i<bitQnty; i++){
		std::cout<<bit1[i];
	}

	printf("\n");

	for(int i=bitQnty-1; 0<=i; i--){
		printf("%d %d %d:",bin[i], bit1[i], c1);
		//printf("%d %d %d %d\n",c1,(bin[i] & bit1[i]), (bin[i] & c1) , (bit1[i] & c1));
		add = ((bin[i] ^ c1) ^ bit1[i]);
		c1 = ((bin[i] & bit1[i]) | (bin[i] & c1) | (bit1[i] & c1));
		bin[i] = add;
		printf("%d %d\n",bin[i], c1);
	}
	for(int i=0; i<bitQnty; i++){
		std::cout<<bin[i];
	}
	printf("\n");
	return;
}

int
main()
{
	int m, q, bitQnt;

	std::cout<<"Ingresar cantidad de bits a usar: ";
	std::cin>>bitQnt;

	int binaryM[bitQnt];
	int binaryQ[bitQnt];

	std::cout<<"Ingresar multiplicando(M): ";
	std::cin>>m;
	std::cout<<"Ingresar multiplicador(Q): ";
	std::cin>>q;

	toBinary(m, binaryM, bitQnt);
	toBinary(q, binaryQ, bitQnt);

	printBinary(binaryM, bitQnt);
	printBinary(binaryQ, bitQnt);

	nor(binaryQ, bitQnt);
	printf("after nor\n");
	printBinary(binaryQ, bitQnt);
	plus1(binaryQ, bitQnt);

	printf("\n");

	return 0;
}
