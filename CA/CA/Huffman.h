#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <map>

class Huffman {

private:
	std::string inputText;
	std::map<char, int> charMap;
	void createCharFreqMap();
public:
	Huffman(std::string textIn);
};


#endif