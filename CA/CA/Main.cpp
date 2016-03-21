#include <iostream>
#include <fstream>
#include <string>
#include "Huffman.h"

int main() {

	std::cout << "ADS2 CA1 (Huffman Compression), X00114659, 21/03/2016" << std::endl << std::endl;

	std::string text;
	std::ifstream inputTextFile("Text.txt");

	if (inputTextFile.is_open()) {
		while (inputTextFile) { // implicit inputTextFile.good(), same as .eof
			std::getline(inputTextFile, text);
		}
	}
	inputTextFile.close();

	std::cout << "Input Text:" << "\n" << text << "\n\n"; // Preview

	//Huffman h;

	system("pause");
	return 0;
}