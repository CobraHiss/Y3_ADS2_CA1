#include "Huffman.h"
#include <iostream>

Huffman::Huffman(std::string textIn)
	: inputText(textIn)
{
	createCharFreqMap();
	populateQueue();
	buildTree();
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
	std::cout << "- Character Frequency Map Created\n";
}

void Huffman::populateQueue() {

	std::map<char, int>::iterator itr;
	for (itr = charMap.begin(); itr != charMap.end(); itr++) {
		pQ.emplace(new Node(itr->first, itr->second)); // push new anonymous node into the priority queue
	}
	std::cout << "- Nodes(Char, Frequency) Created & Pushed to Priority Queue\n";
}

void Huffman::buildTree() {

	while (pQ.size() > 1) {
		Node* leftSub = new Node(pQ.top()); // store the top node from the PQ
		pQ.pop(); // pop off the top node from the PQ (the one above)
		Node* rightSub = new Node(pQ.top()); // the same (binary tree, so has to be done twice)
		pQ.pop();
		pQ.emplace(new Node(leftSub, rightSub)); // push new node (tree), and add up the frequency
	}
	root = pQ.top(); // ref the last node as the root
	pQ.pop(); // pop off the tree from the priority queue

	std::cout << "- Frequency Tree Built. Frequency Of Root Node: " << root->freq << std::endl;
}