#pragma once
#ifndef NODE_H
#define NODE_H

class Node {

	friend class Huffman;

private:
	char letter;
	int freq = 0;
	Node *left = nullptr, *right = nullptr;
public:
	Node();
	Node(char letterIn, int freqIn);
//	Node(const Node& n);
	Node(Node *n);
	Node(Node *ln, Node* rn);
};

#endif