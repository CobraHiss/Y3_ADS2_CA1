#include "Node.h"

Node::Node() {}

Node::Node(char letterIn, int freqIn)
	: letter(letterIn), freq(freqIn)
{}

Node::Node(Node* n) {

	letter = n->letter;
	freq = n->freq;
	if (n->left != nullptr) {
		left = n->left;
	}
	if (n->right != nullptr) {
		right = n->right;
	}
}

Node::Node(Node* ln, Node* rn) {

	freq = ln->freq + rn->freq;
	left = ln;
	right = rn;
}