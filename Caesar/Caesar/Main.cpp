#include <iostream>
#include <fstream>
#include <string> // getline
#include <iomanip> // setw

/*******************************************************************************
*    Title: How to make a Caesar cipher in c++
*    Author: David Caron
*    Date: 25/03/2016
*    Code version: N/A
*    Availability: https://www.youtube.com/watch?v=_EQ6TJs_TEk
*******************************************************************************/
/*******************************************************************************
*    Title: Caesar Cipher - Implementation in C++ : Program Source code 
*    Author: Raman Nv
*    Date: 25/03/2016
*    Code version: N/A
*    Availability: http://geekycircle.blogspot.ie/2014/02/caesar-cipher-implementation-in-c.html#.VvW--kdJ1wE
*******************************************************************************/

int main() {

	std::cout << "ADS2 CA1 (Caesar Cipher), X00114659, 25/03/2016" << std::endl << std::endl;

	std::string temp, text;
	int shiftKey;
	std::ifstream inputFile("Poem.txt");

	std::cout << "PLAINTEXT :::::::::::::::::::::::::::::::::::::::::::::::\n\n";

	if (inputFile.is_open()) {
		while (inputFile) {
			std::getline(inputFile, temp);
			text += temp.append(" \n");
			std::cout << temp;
		}
	}
	else {
		std::cout << "File Not Found";
		system("pause");
	}
	inputFile.close();

	std::cout << "INPUT THE SHIFT KEY (NUMBER) ::::::::::::::::::::::::::::\n\n";
	std::cin >> shiftKey;
	shiftKey %= 26;
	if (shiftKey == 0) { shiftKey += 1; }

	std::cout << "\nCIPHERTEXT ::::::::::::::::::::::::::::::::::::::::::::::\n\n";

	for (unsigned int i = 0; i < text.length(); i++)
	{
		if (isalpha(text[i]))
		{
			text[i] = tolower(text[i]);
			for (int j = 0; j < shiftKey; j++) // shift i, shiftKey number of times
			{
				if (text[i] == 'z')
				{
					text[i] = 'a';
				}
				else
				{
					text[i]++;
				}
			}
		}
	}

	std::cout << text;

	std::cout << "DECRYPTED ::::::::::::::::::::::::::::::::::::::::::::::: \n\n";

	for (unsigned int i = 0; i<text.length(); i++)
	{
		if (isalpha(text[i]))
		{
			for (int j = 0; j< shiftKey; j++)
			{
				if (text[i] == 'a')
				{
					text[i] = 'z';
				}
				else
				{
					text[i]--;
				}
			}
		}
	}

	std::cout << text;

	system("pause");
	return 0;
}