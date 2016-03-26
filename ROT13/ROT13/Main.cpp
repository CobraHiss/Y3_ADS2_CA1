#include <iostream>
#include <fstream>
#include <string>

/***************************************************************************************
*    Title: ROT13
*    Author: The Internet
*    Date: 26/03/2016
*    Code version: N/A
*    Availability: https://en.wikipedia.org/wiki/ROT13
***************************************************************************************/

int main() {

	std::cout << "ADS2 CA1 (ROT13 Cipher), X00114659, 26/03/2016" << std::endl << std::endl;

	std::string temp, text;
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

	system("pause");
	return 0;
}