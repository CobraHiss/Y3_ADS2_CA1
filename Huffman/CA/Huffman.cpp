#include "Huffman.h"
#include <iostream>
#include <fstream>

/***************************************************************************************
*    Title: An In-Depth Look At Huffman Encoding
*    Author: KYA
*    Date: 21/03/2016
*    Code version: N/A
*    Availability: http://www.dreamincode.net/forums/blog/324/entry-3150-an-in-depth-look-at-huffman-encoding/
***************************************************************************************/

Huffman::Huffman(std::string textIn)
	: inputText(textIn)
{
	createCharFreqMap();
	populateQueue();
	buildTree();
	createCharToBitMap(root, "");
	testMap();
	encodeHuffmanToFile();
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

	///////////////////////////////////////////////////// JUST A TEST - REMOVE FROM FINAL
	std::map<char, int>::iterator charMapItr;
	for (charMapItr = charMap.begin(); charMapItr != charMap.end(); charMapItr++) {
		std::cout << charMapItr->first;
		std::cout << charMapItr->second << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////////////////
	std::cout << "- Character Frequency Map Created\n";
}

void Huffman::populateQueue() {

	std::map<char, int>::iterator itr;
	for (itr = charMap.begin(); itr != charMap.end(); itr++) {
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
	std::cout<<newNode->freq;
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
			std::cout<<nodePtr->freq << " ";
			createCharToBitMap(nodePtr->left, letterBits + '0'); // at every traversal add a bit (left = 0, right = 1)
			createCharToBitMap(nodePtr->right, letterBits + '1');
		}
		else {
			charToBitMap.insert(std::pair<char, std::string>(nodePtr->letter, letterBits));
		}
	}
}

///////////////////////////////////////////////////// JUST A TEST - REMOVE FROM FINAL
void Huffman::testMap() {

	std::map<char, std::string>::iterator i;
	for (i = charToBitMap.begin(); i != charToBitMap.end(); i++) {
		std::cout << i->first << " ";
		std::cout << i->second << std::endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////

void Huffman::encodeHuffmanToFile() {

	std::ofstream fileToWrite;
	fileToWrite.open("CharCodes.txt");

	for (int i = 0; i < inputText.size(); i++) {
		fileToWrite << charToBitMap.find(inputText[i])->second; // finds the letter, then fetches its second (code)
	}
	fileToWrite.close();
}

void Huffman::decodeHuffmanFromFile() {

	std::string text;
	std::ifstream inputTextFile("CharCodes.txt");

	if (inputTextFile.is_open()) {
		while (inputTextFile) {
			std::getline(inputTextFile, text);
		}
	}
	inputTextFile.close();
}
