#include "Huffman.h"
#include <iostream>

Huffman::Huffman(std::string textIn)
	: inputText(textIn)
{
	createCharFreqMap();
}

void Huffman::createCharFreqMap() {

	for (unsigned int i = 0; i < inputText.length(); i++) {
		
		if (charMap.find(inputText[i]) == charMap.end()) { // if the current character is not found (end reached)
			charMap.insert(std::pair<char, int>(inputText[i], 1)); // insert a new pair char and the starter value 1
		}
		else {
			charMap.find(inputText[i])->second++; // if the character is found, ++ frequency (the weight)
		}
	}

	// JUST A TEST - REMOVE FROM FINAL
	std::map<char, int>::iterator charMapItr;
	for (charMapItr = charMap.begin(); charMapItr != charMap.end(); charMapItr++) {
		std::cout << charMapItr->first;
		std::cout << charMapItr->second << std::endl;
	}
	std::cout << "Character Frequency Map Created\n";
}