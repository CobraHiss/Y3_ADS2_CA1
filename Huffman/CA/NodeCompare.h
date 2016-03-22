#pragma once
#include "Node.h"

// had to create this for priority queue comparison of nodes
// http://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator

class NodeCompare {

	friend class Huffman;

public:
	bool operator()(Node* n1, Node* n2);
};