/*
CAESAR CIPHER ANALYSER
*/

#include "header.h"

//Function to decrypt given cshift ipher with given key
string decryptShift(string cipher, int k)
{
	k = 26 - k; //We use inverse key for simplicity	

	string plain = ""; //Stores decryoted Plaintext
	
	for (int i = 0; i < cipher.length(); ++i) //Run through every character in ciphertext
	{
		if (cipher[i] >= 65 && cipher[i] <= 90) //Decrypt uppercase characters
			plain += (cipher[i] - 65 + k) % 26 + 65;
		else if (cipher[i] >= 97 && cipher[i] <= 122) //Decrypt lowecase characters
			plain += (cipher[i] - 97 + k) % 26 + 97;
		else
			plain += cipher[i]; //Non-alphabetical characters
	}	
	
	return plain;
}

