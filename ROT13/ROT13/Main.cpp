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
/***************************************************************************************
*    Title: ROT13 implementation
*    Author: Sir_Blake_, Corbin
*    Date: 26/03/2016
*    Code version: N/A
*    Availability: http://codereview.stackexchange.com/questions/14569/rot13-implementation
***************************************************************************************/
/***************************************************************************************
*    Title: [C++] ROT-13 string encoder tutorial (beginner to intermediate)
*    Author: Noble
*    Date: 26/03/2016
*    Code version: N/A
*    Availability: https://facepunch.com/showthread.php?t=1094693
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

	std::cout << "\nCIPHERTEXT ::::::::::::::::::::::::::::::::::::::::::::::\n\n";

	for (unsigned int i = 0; i != text.length(); i++) {

		if (text[i] >= 'a' && text[i] <= 'm') {
			text[i] = text[i] + 13;
		}
		else if (text[i] >= 'n' && text[i] <= 'z') {
			text[i] = text[i] - 13;
		}
		else if (text[i] >= 'A' && text[i] <= 'M') {
			text[i] = text[i] + 13;
		}
		else if (text[i] >= 'N' && text[i] <= 'Z') {
			text[i] = text[i] - 13;
		}
	}

	std::cout << text;

	std::cout << "DECRYPTED ::::::::::::::::::::::::::::::::::::::::::::::: \n\n";

	// ROT13 is an inverse cipher (2x13), so to decrypt it, the exact same algorithm is applied

	for (unsigned int i = 0; i != text.length(); i++) {

		if (text[i] >= 'a' && text[i] <= 'm') {
			text[i] = text[i] + 13;
		}
		else if (text[i] >= 'n' && text[i] <= 'z') {
			text[i] = text[i] - 13;
		}
		else if (text[i] >= 'A' && text[i] <= 'M') {
			text[i] = text[i] + 13;
		}
		else if (text[i] >= 'N' && text[i] <= 'Z') {
			text[i] = text[i] - 13;
		}
	}

	std::cout << text;

	system("pause");
	return 0;
}