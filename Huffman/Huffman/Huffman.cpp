#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <iomanip> // std::setw
#include <sstream>
#include <bitset>

/***************************************************************************************
*    Title: An In-Depth Look At Huffman Encoding
*    Author: KYA
*    Date: 21/03/2016
*    Code version: N/A
*    Availability: http://www.dreamincode.net/forums/blog/324/entry-3150-an-in-depth-look-at-huffman-encoding/
***************************************************************************************/
// Lecture notes, specifically huffman.ppt used for guidance
// Also Google... lots and lots of Google and StackOverflow

Huffman::Huffman(std::string textIn)
	: inputText(textIn)
{
	createCharFreqMap();
	populateQueue();
	buildTree();
	createCharToBitMap(root, "");
	encodeHuffmanToFile();
	decodeHuffmanFromFile();
	compressHuffmanToFile();
	decompressHuffmanFromFile();
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

	std::cout << "- Character Frequency Map Created\n\n";
	// output the map
	std::cout << std::right << std::setw(15) << "Character";
	std::cout << " | Frequency" << std::endl;
	for (std::map<char, int>::iterator charMapItr = charMap.begin(); charMapItr != charMap.end(); charMapItr++) {
		std::cout << std::right << std::setw(11) << charMapItr->first << std::right << std::setw(12) << charMapItr->second << std::endl;
	}
	std::cout << std::endl;
}

void Huffman::populateQueue() {

	for (std::map<char, int>::iterator itr = charMap.begin(); itr != charMap.end(); itr++) {
		pQ.emplace(new Node(itr->first, itr->second)); // push new anonymous node into the priority queue
	}
	std::cout << "- Nodes(Char, Frequency) Created & Pushed to Priority Queue\n\n";
}

// build the huffman tree
void Huffman::buildTree() {

	while (pQ.size() != 1) {
		Node* leftSub = new Node(pQ.top()); // store the top node from the PQ
		pQ.pop(); // pop off the top node from the PQ (the one above)
		Node* rightSub = new Node(pQ.top()); // the same (binary tree, so has to be done twice)
		pQ.pop();
		Node* newNode = new Node(leftSub, rightSub);
		pQ.emplace(newNode); // push new node (tree), and add up the frequency (populated in PQ based on frequency)
	}
	root = pQ.top(); // ref(set) the last node as the root
	pQ.pop(); // pop off the tree from the priority queue

	std::cout << "- Frequency Tree Built. Verified at www.algorasim.com\n\n";
	std::cout << std::right << std::setw(6) << " " << "Frequency Of Root Node: " << root->freq << "\n\n";
}

// pre-order traversal of the tree (reach leaf nodes and store the letter and the bit code in the map)
void Huffman::createCharToBitMap(Node* nodePtr, std::string letterBits) {

	if (!nodePtr) { // if root is NULL (has nothing)
		std::cout << "No Tree";
	}
	else {
		if (nodePtr->letter == NULL) { // if there is no letter present in the node (i.e. branches, only frequency here)
//std::cout<<nodePtr->freq << " ";
			createCharToBitMap(nodePtr->left, letterBits + '0'); // at every traversal add a bit (left = 0, right = 1)
			createCharToBitMap(nodePtr->right, letterBits + '1');
		}
		else {
			charToBitMap.insert(std::pair<char, std::string>(nodePtr->letter, letterBits));
		}
	}
}

void Huffman::encodeHuffmanToFile() {

	// This should be in the createCharToBitMap() method, but since it's called recursively, the output is split. I'll just chuck it in here
	std::cout << "- Character to Huffman Code Map Created\n\n";
	// output the map
	std::cout << std::right << std::setw(15) << "Character";
	std::cout << " | BitCode" << std::endl;

	for (std::map<char, std::string>::iterator itr = charToBitMap.begin(); itr != charToBitMap.end(); itr++) {
		std::cout << std::right << std::setw(11) << " "; // this is just to pad the space on the left hand side
		std::cout << std::left << std::setw(11) << itr->first << std::setw(50) << itr->second << std::endl;
	}
	std::cout << std::endl;

	// take the input text (the original from main), loop through it, find respective Huffman code in the map and add to the string
	for (int i = 0; i < inputText.size(); i++) {
		huffmanCode += charToBitMap.find(inputText[i])->second;
	}
	// write the Huffman codes to file
	writeFile(huffmanCode, "CharCodes.txt");

	std::cout << "- Huffman Encoded Characters Written To File\n\n";
	std::cout << std::right << std::setw(6) << " " << "(Size:" << huffmanCode.size() << ")\n";

	// loop just to break up the output into chunks of 30
	for (unsigned int i = 0; i < huffmanCode.length(); i+=30) {
		std::cout << std::right << std::setw(6) << " " << huffmanCode.substr(i, 30) << std::endl;
	}
	std::cout << std::endl;
}

void Huffman::decodeHuffmanFromFile() {

	huffmanCode = readFile("CharCodes.txt"); // put file contents into the string
	std::string decodedHuffman = huffmanDecoder(huffmanCode); // decode Huffman code into a string
	std::cout << "- Huffman Encoded Characters Decoded From File. Saved To A New File\n\n";

	// write out the decoded message to file
	writeFile(decodedHuffman, "DecodedHuffman.txt");

	// output the code
	std::cout << std::right << std::setw(6) << " " << decodedHuffman << "\n\n";
}

void Huffman::compressHuffmanToFile() {

	std::cout << "- Huffman Code Compressed To ASCII. Saved To A New File\n\n"; // shhh.. not yet really. But it's going to happen below.

	// pad the huffman code to create chunks of equal size (8-bits) - Reason... CPU reads min of a byte (8-bits)
	while (huffmanCode.size() % 8 != 0) {
		huffmanCode.append("0");
		padding++;
	}

	std::string compressedCode;
	std::stringstream sstream(huffmanCode);
	std::bitset<8> byte;

	bool innerControl = true; // I got none.
	int i = 0; // this and the inner while loop is for the output of bit codes in 8 bit chunks

	std::cout << std::right << std::setw(15) << "Character";
	std::cout << " | ASCII Code" << std::endl;
	
	while (sstream) { // this would add incorrect character at the end w/o the additional padding. Could've used .good() as well
		sstream >> byte;
		char c = char(byte.to_ulong());
		compressedCode += c;
		std::cout << std::right << std::setw(11) << " "; // this is just to pad the space on the left hand side
		std::cout << c;
		while (innerControl) {
			std::cout << std::setw(15) << huffmanCode.substr(i, 8) << std::endl;
			i += 8;
			innerControl = false;
		}
		innerControl = true;
	}

	compressedCode.pop_back(); // this is to cut off the extra NUL (\0) at the end (Tip for whoever comes by this CA - Notepad++ points out NULs in text files)

	// write out the compressed code to file
	writeFile(compressedCode, "CompressedHuffman.txt");

	std::cout << std::right << std::setw(6) << " " << "Output To File: " << compressedCode << "\n\n";
}

void Huffman::decompressHuffmanFromFile() {

	std::cout << "- Compressed ASCII Huffman Code Decompressed and Decoded From File\n\n";

	// read file contents into a string
	std::string input = readFile("CompressedHuffman.txt");

	std::bitset<8> byte; // http://www.cplusplus.com/reference/bitset/bitset/
	std::string decompressedHuffman;

	for (int i = 0; i < input.size(); i++) {
		byte = input[i];
		// std::cout << byte; // wow, this worked like magic, MAGIC!
		decompressedHuffman += byte.to_string(); // convert byte bitset to string and append to the left string
	}
	std::cout << std::right << std::setw(6) << " " << "DECOMPRESSED (Size w Padding: " <<  decompressedHuffman.size() << ", Size w/o Padding: " << (decompressedHuffman.size()-padding) << ")\n";
	for (unsigned int i = 0; i < decompressedHuffman.length(); i += 30) {
		std::cout << std::right << std::setw(6) << " " << decompressedHuffman.substr(i, 30) << std::endl;
	}

	std::cout << "\n";
	std::cout << std::right << std::setw(6) << " " << "DECODED\n";
	std::cout << std::right << std::setw(6) << " " << huffmanDecoder(decompressedHuffman) << "\n\n"; // pass the decompressed Huffman code to the function which decodes and returns it as a string, then output it
}

// Huffman code decoder
std::string Huffman::huffmanDecoder(std::string huffmanCodeIn) {

	std::string decodedHuffman = ""; // to store the decoded text
	Node* nodePtr = root;
	for (int i = 0; i != huffmanCodeIn.size() - padding; i++)
	{
		if (huffmanCodeIn[i] == '0') { // if 0, go left
			nodePtr = nodePtr->left;
		}
		else { // else, it can only be 1, which means go right
			nodePtr = nodePtr->right;
		}
		if (nodePtr->left == nullptr && nodePtr->right == nullptr) // if we reach leaf node
		{
			decodedHuffman += nodePtr->letter; // append the letter in that leaf node to the string
			nodePtr = root; // reset node pointer to root
		}
	}
	return decodedHuffman;
}

std::string Huffman::readFile(std::string fileNameIn) {

	std::string input;
	std::ifstream inputFile(fileNameIn);

	if (inputFile.is_open()) {
		while (inputFile) {
			std::getline(inputFile, input);
		}
	}
	else {
		std::cout << "File Not Found";
		system("pause");
	}
	inputFile.close();

	return input;
}

void Huffman::writeFile(std::string textIn, std::string fileNameIn) {

	std::ofstream outputFile;
	outputFile.open(fileNameIn);
	outputFile << textIn;
	outputFile.close();
}
