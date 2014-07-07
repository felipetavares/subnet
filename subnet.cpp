#include <iostream>
using namespace std;

unsigned char fip[4];
unsigned int intfip[4];

int getbits (char netclass) {
	switch (netclass) {
		case 'A': case 'a':
			return 8;
		case 'B': case 'b':
			return 16;
		case 'C': case 'c':
			return 24;
	}
	return 8;
} 

void setbit (int n, int v) {
	int block = n/8;

	if (v) {
		fip[block] |= 1<<(7-n%8);
	}
	else
		fip[block] &= ~(1<<(7-n%8));
}

int getbit (int n) {
	int block = n/8;

	return (fip[block]>>(n%8))&1;	
}

void printSubnetStart (int netbits, int borrow, int subnet) {
	do {
		setbit(netbits+borrow-1, subnet%2);
		subnet/=2;
	} while (borrow--);

	cout << (unsigned int)(unsigned char)fip[0] << "." <<
			(unsigned int)(unsigned char)fip[1] << "." <<
			(unsigned int)(unsigned char)fip[2] << "." <<
			(unsigned int)(unsigned char)fip[3] << endl;
}

void printSubnetEnd (int netbits, int borrow, int subnet) {
	int b2 = borrow;

	do {
		setbit(netbits+b2-1, subnet%2);
		subnet/=2;
	} while (b2--);

	for (int i=netbits+borrow;i<32;i++) {
		setbit (i, 1);
	}

	cout << (unsigned int)fip[0] << "." <<
			(unsigned int)fip[1] << "." <<
			(unsigned int)fip[2] << "." <<
			(unsigned int)fip[3] << endl;
}

int main () {
	char netclass;
	int netbits;
	int borrow;
	int subnet;

	cin >> intfip[0] >> intfip[1] >> intfip[2] >> intfip[3];
	cin >> netclass;
	cin >> borrow;

	netbits = getbits(netclass);

	do {
		cin >> subnet;

		if (subnet >= 0) {
			fip[0] = intfip[0];
			fip[1] = intfip[1];
			fip[2] = intfip[2];
			fip[3] = intfip[3];
			printSubnetStart(netbits, borrow, subnet);
			fip[0] = intfip[0];
			fip[1] = intfip[1];
			fip[2] = intfip[2];
			fip[3] = intfip[3];
			printSubnetEnd(netbits, borrow, subnet);
		}
	} while (subnet >= 0);

	return 0;
}