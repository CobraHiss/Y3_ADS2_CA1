#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <iomanip> // std::setw

/***************************************************************************************
*    Title: An In-Depth Look At Huffman Encoding
*    Author: KYA
*    Date: 21/03/2016
*    Code version: N/A
*    Availability: http://www.dreamincode.net/forums/blog/324/entry-3150-an-in-depth-look-at-huffman-encoding/
***************************************************************************************/
// Lecture notes, specifically huffman.ppt used for guidance
// Also Google... lots and lots of Google

Huffman::Huffman(std::string textIn)
	: inputText(textIn)
{
	createCharFreqMap();
	populateQueue();
	buildTree();
	createCharToBitMap(root, "");
	encodeHuffmanToFile();
	decodeHuffmanFromFile();
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
	std::cout << "- Nodes(Char, Frequency) Created & Pushed to Priority Queue\n";
}

// build the huffman tree
void Huffman::buildTree() {

	while (pQ.size() != 1) {
		Node* leftSub = new Node(pQ.top()); // store the top node from the PQ
//std::cout<< leftSub->freq; // delete just a test of order
		pQ.pop(); // pop off the top node from the PQ (the one above)
		Node* rightSub = new Node(pQ.top()); // the same (binary tree, so has to be done twice)
//std::cout << rightSub->freq; // delete just a test
		pQ.pop();
		Node* newNode = new Node(leftSub, rightSub);
//	std::cout<<newNode->freq;
		pQ.emplace(newNode); // push new node (tree), and add up the frequency (populated in PQ based on frequency)
	}
	root = pQ.top(); // ref(set) the last node as the root
	pQ.pop(); // pop off the tree from the priority queue

	std::cout << "- Frequency Tree Built. Frequency Of Root Node: " << root->freq << std::endl;
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

	// output file
	std::string huffmanCode;
	std::ofstream fileToWrite;
	fileToWrite.open("CharCodes.txt");

	for (int i = 0; i < inputText.size(); i++) {
		fileToWrite << charToBitMap.find(inputText[i])->second; // finds the letter (from inputText) in the map, then fetches its second (code)
		huffmanCode += charToBitMap.find(inputText[i])->second; // could've just output the string from decodeHuffmanFromFile(), but doing this to stay organised
	}
	fileToWrite.close();

	std::cout << "- Huffman Encoded Characters Written To File\n\n";

	// loop just to break up the output into chunks of 20
	for (unsigned int i = 0; i < huffmanCode.length(); i+=30) {
		std::cout << std::right << std::setw(6) << " " << huffmanCode.substr(i, 30) << std::endl;
	}
	std::cout << std::endl;
}

void Huffman::decodeHuffmanFromFile() {

	// put file contents into a string
	std::string huffmanCode;
	std::ifstream inputCharCodes("CharCodes.txt");

	if (inputCharCodes.is_open()) {
		while (inputCharCodes) {
			std::getline(inputCharCodes, huffmanCode);
		}
	}
	else {
		"File Not Found";
	}
	inputCharCodes.close();

	// decode Huffman code
	std::string decodedHuffman = ""; // to store the decoded text
	Node* nodePtr = root;
	for (int i = 0; i != huffmanCode.size(); i++)
	{
		if (huffmanCode[i] == '0') { // if 0, go left
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
	std::cout << "- Huffman Encoded Characters Decoded From File. Written To A New File\n\n";

	// write out the decoded message to file
	std::ofstream fileToWrite;
	fileToWrite.open("DecodedHuffman.txt");
	fileToWrite << decodedHuffman;
	fileToWrite.close();

	// output the code
	std::cout << std::right << std::setw(6) << " " << decodedHuffman << "\n\n";
}