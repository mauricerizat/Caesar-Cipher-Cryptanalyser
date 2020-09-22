/*
CAESAR CIPHER ANALYSER
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <cstdlib>
#include <math.h>

using namespace std;

float roundN (float, int);
string decryptShift(string, int);

int main(int argc, char** argv)
{
	//Welcome Message
	cout << "\nWelcome to Caesar Cipher Analyser Program " << endl;
	cout << "--------------------------------------------------------------" << endl;
	
	string cipherFile = ""; //Stores name of ciphertext file
	string cipher = ""; //Stores ciphertext
		
	cout << "Enter Ciphertext file name: "; //Accepting name of cipher text file	
	cin >> cipherFile;

	//Checking for and reading Input file
	cout << "\nReading from Input file..." << endl;
	
	ifstream readFile("data/" + cipherFile); //File to be located in "data" sub-folder
	if (!(readFile.is_open())) //Input file cannot be opened or does not exist
	{
		cout << "\n\tFile named \"" << cipherFile;
		cout << "\" cannot be opened or does not exist.";
		cout << "\n\tPlease try again with a valid file name.\n" << endl;
		return 0;
	}	
	else //Input file exists
	{	
		//Reading Input file
		try 
		{
			string line;
			while (getline(readFile, line))
				cipher += (line + "\n");
			
			cipher = cipher.substr(0, cipher.size()-1);
			
		readFile.close();
		} 
		catch (exception& e) //Handles errors that occurs during file reading
		{
			cout << "An error occured while reading file. Please try again.\n" << endl;
			return 0;
		}
	}
	
	cout << "\nFile Read!\n" << endl;
	
	
	cout << "Analysing ciphertext..." << endl;
	
	//Initialising given letter probabilities
	const float p[] = {	0.082f, 0.015f, 0.028f, 0.043f, 0.127f, 0.022f, 0.020f, 0.061f, 0.070f, 
			0.002f, 0.008f, 0.040f, 0.024f, 0.067f, 0.075f, 0.019f, 0.001f, 0.060f,
			0.063f, 0.091f, 0.028f, 0.010f, 0.023f, 0.001f, 0.020f, 0.001f};
	
	int f[26] = {0}; //Array to store frequency of each letter
	
	int N = 0; //Stores total number of alphabetic characters
	
	float q[26] = {0.0f}; //Array to store values of q = f/N
	
	//Counting the freauency of letter and the number of alphabetical characters in the ciphertext
	for (int i = 0; i < cipher.length(); ++i)
	{
		if (cipher[i] >= 65 && cipher[i] <= 90) //Uppercase characters
		{
			++f[cipher[i] - 65]; //Increment counter of corresponding alphabet
			++N;
		}
		else if (cipher[i] >= 97 && cipher[i] <= 122) //Lowercase characters
		{
			++f[cipher[i] - 97]; //Increment counter of corresponding alphabet
			++N;
		}
	}
	
	//Finding q
	for (int i = 0; i < 26; ++i)
	{
		q[i] = roundN(1.0*f[i]/N, 3); //q is rounded to three palces to avoid exceeding float limit
	}
	
	/*DISPLAY corresponding p, f, and q values. For checking.
	cout << "letter\t\tp\t\tf\t\tq\t\tr(q)" << endl; 
	
	int ch = 65;
	
	for (int i = 0; i < 26; ++i)
	{
		cout << (char)(ch + i) << "\t\t" << p[i] << "\t\t" << f[i] << "\t\t" << q[i] << endl;
	}
	
	cout << "\nN: " << N << endl;
	*/
	
	//Deduce key
	int key = 0; //Stores most likely key
	float bestMIC = 0.0f; //Stores most likely MIC - Value closest to 0.065
	
	cout << "\nCalculating MIC...\n" << endl;
	
	//Finding Key
	for (int j = 0; j < 26; ++j)
	{			
		float MIC = 0.0f; //Stores current MIC
		
		//Calculating MIC
		for (int i = 0; i < 26; ++i)
		{
			MIC += p[i]*q[(i+j)%26];
		} 
		
		//Display corresponding key values and MICs
		cout << "Key Value = " << j;
		cout << "\tMIC = " << MIC << endl;
		
		//Checking if current MIC is closer to 0.065 than most likely MIC
		if (abs(MIC - 0.065) < abs(bestMIC - 0.065))
		{
			//If so, replace most likely MIC and key with current MIC and key
			bestMIC = MIC;
			key = j;
		}
	}
	
	cout << "\nKey Found!" << endl;
	cout << "\tThe Key is " << key << endl; //Display key to user

	if (abs(bestMIC - 0.065) > 0.015f)
	{
		cout << "Warning: The ciphertext may not be of an English Shift Cipher." << endl;
		cout << "Key result is most likely guess." << endl;
	}

	//Decrypting cipher with identified key
	string plain = decryptShift(cipher, key); 
	
	//Display decrypted cipher to user
	cout << "\nThe decrypted Plaintext is:\n" << endl;
	cout << plain << endl;
	
	cout << "\n--------------------------------------------------------------" << endl;
	cout << "Thank you for using the program" << endl;
	
	return 0;
}

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

//Function to round up given number num up to place decimal places
float roundN (float num, int place)
{
	int n = num * pow(10.0, place+1); 
	
	int r = n % 10;
	
	n /= 10;
	
	if (r >= 5)
		n += 1;
		
	num = n / pow(10.0, place);
	
	return num;
}


