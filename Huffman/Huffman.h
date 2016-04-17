#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Node.h"
#include "NodeCompare.h"
#include <string>
#include <queue>
#include <map>

class Huffman {

private:
	std::string inputText;
	std::string huffmanCode; // used in more than one function, so made its scope from function to class wide
	int padding; // this for padding the huffman code with 0s to make up equal sized chunks of 8 bits
	std::map<char, int> charMap; // character frequency map
	std::map<char, std::string> charToBitMap; // for storing chars and corresponding huffman codes from the tree
	void createCharFreqMap();
	void populateQueue();
	void buildTree();
	void createCharToBitMap(Node* nodePtr, std::string letterBits);
	void encodeHuffmanToFile();
	void decodeHuffmanFromFile();
	void compressHuffmanToFile();
	void decompressHuffmanFromFile();
	std::string huffmanDecoder(std::string huffmanCodeIn); // moved decoder to its own function for reuse
	std::string readFile(std::string fileNameIn);
	void writeFile(std::string textIn, std::string fileNameIn);
	void summary();
	std::priority_queue<Node, std::vector<Node*>, NodeCompare> pQ;	// http://stackoverflow.com/questions/15646780/priority-queue-of-nodes
	Node* root = nullptr; // the tree "hangs" off of this root		// http://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
public:
	Huffman(std::string textIn);
};

#endif