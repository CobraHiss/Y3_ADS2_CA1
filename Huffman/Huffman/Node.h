#pragma once
#ifndef NODE_H
#define NODE_H

class Node {

	friend class Huffman;
	friend class NodeCompare;

private:
	char letter = '\0'; // NULL char - http://stackoverflow.com/questions/18410234/how-does-one-represent-the-empty-char
	int freq = 0;
	Node *left = nullptr, *right = nullptr;
public:
	Node();
	Node(char letterIn, int freqIn);
	Node(Node *n);
	Node(Node *ln, Node* rn);
};

#endif