#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Node.h"
#include "NodeCompare.h"
#include <string>
#include <queue>
#include <deque>
#include <map>

class Huffman {

private:
	std::string inputText;
	std::map<char, int> charMap; // character frequency map
	std::map<char, std::string> charToBitMap; // for storing chars and corresponding codes from the tree
	void createCharFreqMap();
	void populateQueue();
	void buildTree();
	void createCharToBitMap(Node* nodePtr, std::string letterBits);
	void encodeHuffmanToFile();
	void decodeHuffmanFromFile();
	void testMap();
	std::priority_queue<Node, std::vector<Node*>, NodeCompare> pQ;	// http://stackoverflow.com/questions/15646780/priority-queue-of-nodes
	Node* root = nullptr;											// http://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
public:
	Huffman(std::string textIn);
};

#endif