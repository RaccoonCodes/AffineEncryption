#include<iostream>
#include <string>
#include <algorithm>

/*
* 5/22/2022
* This program uses Affine Encryption where the keys alpha and beta are known in ax + b (mod 26) 
* It ask user to choose to encrypt or decrypt. 
*/

using namespace std;
string affineEncryption(string p,int a, int b) {
	string cipher = "";
	for (int i = 0; i < p.length(); i++) {
		if (p[i] != ' ')
			cipher += (char)((((a * (p[i] - 'A')) + b) % 26) + 'A');  // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
		else
			cipher += p[i];//adding the whitespace in between characters
	}
	return cipher;
}

string affineDecryption(string c, int a, int b) {
	string plain = "";
	int inversal = 0;
	int flag = 0;

	//finding multiplicative inverse of alpha that equals to 1 mod 26 or GCD(alpha,26)
	for (int i = 0; i < 26; i++) {
		flag = (a * i) % 26;
		
		if (flag == 1) 
			inversal = i;
		
	}
	for (int i = 0; i < c.length();i++) {
		if (c[i] != ' ')
			plain += (char)(((inversal * ((c[i] + 'A' - b)) % 26)) + 'A');  
		else
			plain += c[i];
	}
	return plain;
}

int encryptionMode() {
	int alpha = 0;
	int beta = 0;
	int pos_alpha = 0;
	string plaintext = " ";
	string ciphertext = " "; 
	
	cout << "You are currently in Encryption mode!" << endl;
	cout << "\nPlease Enter your two numbers for alpha and beta: " << endl;

	cout << "Alpha is: ";
	cin >> alpha;
	cout << "Beta is: ";
	cin >> beta;

	if (cin.fail()) {
		cout << "ERROR: must be a valid number." << endl;
		cin.clear();
		cin.ignore();
		do {
			cout << "Alpha is: ";
			cin >> alpha;
			cout << "Beta is: ";
			cin >> beta;
		} while (cin.fail());
	}

	cout << "\nYour function is: " << alpha << "x + " << beta << " (mod26)" << endl;
	cout << "Now enter your word or sentence that needs to be encrypted: ";
	cin.ignore();
	getline(cin, plaintext);

	cout << "Encrypting \"" << plaintext << "\"..." << endl << endl;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

	ciphertext = affineEncryption(plaintext, alpha, beta);

	cout << "Cipher text is: " << ciphertext << endl;
	
	//Test decryption
	cout << "Plain text is: " << plaintext << endl;
	
	return 0;
}

int decryptionMode() {
	int alpha = 0;
	int beta = 0;
	string plaintext = " ";
	string ciphertext = " ";

	cout << "\nYou are currently in Decryption mode!" << endl << endl;
	cout << "What is the cipher text?: ";
	cin.ignore();
	getline(cin, ciphertext);

	cout << "What is the alpha from the encryption key? ";
	cin >> alpha;

	cout << "What is the beta from the encryption key? ";
	cin >> beta;

	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);
	plaintext = affineDecryption(ciphertext, alpha, beta);
	cout << "\nPlain text is: " << plaintext << endl;
	return 0;
}

int main() {
	int choice = 0;
	bool flag = false;
	
	cout << "\t\tHello and welcome to Affine Encryption Program!!" << endl;
	cout << "Would you like to use the encryption, decryption algorithm, or encrypt a file? (type 1 or 2)  " << endl;

	while (!flag) {
		cout << "1. Encryption " << endl;
		cout << "2. Decryption " << endl;
		cin >> choice;

		if (cin.fail() || (choice > 2 || choice < 1)) {
			cout << "Please type 1 or 2 " << endl;
			cin.clear();
			cin.ignore();
		}
		else
			flag = true;
	}

	if(choice == 1)
		encryptionMode();
	else
		decryptionMode();


}

