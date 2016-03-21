#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Node.h"
#include <string>
#include <queue>
#include <deque>
#include <map>

class Huffman {

private:
	std::string inputText;
	std::map<char, int> charMap; // character frequency map
	void createCharFreqMap();
	void populateQueue();
	void buildTree();
	std::priority_queue<Node*, std::vector<Node*>> pQ; // http://stackoverflow.com/questions/15646780/priority-queue-of-nodes
	Node* root = nullptr;
public:
	Huffman(std::string textIn);
};


#endif