#include "NodeCompare.h"

bool NodeCompare::operator()(Node* n1, Node* n2) {
	return (n1->freq > n2->freq ? 1 : 0);
}