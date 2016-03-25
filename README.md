## Computing Year 3 - Algorithms & Datastructures 2 (CA1)

*This was an assignment given to students in year 3 of computing course at It-Tallaght (Dublin, Ireland)*

##TASKS

###Part A (60%) Compression

You are required to carry out the tasks below in order to develop an optimal Huffman Tree with
which to compress a file of ASCII text. You will be expected to make use of the template classes in
the STL.
You should aim to complete the first section of this problem (i.e. the steps 1 through 5 below). Once
you have completed tasks 1-5 sections complete the other sections 6 & 7.
The first 5 tasks will encode and decode the file into a string of 0's and 1's using a Huffman tree

1. Given a text file, determine the frequency of each character in the text (map of character
and frequency).
2. Build an optimal Huffman tree to represent these characters with these frequencies
(maintain a priority queue of trees, removing and joining trees until only one tree remains –
the final Huffman tree required) Hint: each Hoffman Tree should have a weight data
member, as well as a pointer to its root node.
3. Use the tree to map each character to the string of 0's and 1's needed to encode it (preorder
traversal of tree, store results in a map of character and string).
4. Use the map to encode the text to a string of 0's and 1's and write to an encoded file
5. Use the Huffman Tree to decode the text and write to another file.
Tasks 6 and 7 compress and un-compress the file:
6. To compress: break up the string of 0's and 1's into 8 bit chunks, and write the character
represented by each chunk to the compressed file.
7. Decode by replacing each character with the 8 bits needed to represent it.

###Part B (40%) Cryptography

You are required to carry out the tasks below:

1. Write a program that takes as input a text file containing a poem of your choice. Open the
text file and encrypt the contents using one of the two following ciphers.
 * a. Caesar cipher, a C++ implementation is give here http://rosettacode.org/wiki/Caesar_cipher#C.2B.2B
 * b. Rot-13 cipher, a C++ implementation is give here http://rosettacode.org/wiki/Rot-13#C.2B.2B
 * Here is a link to a poem you can n use if you can’t think of any http://www.poppyfields.net/filks/00288.html
2. Ask me for an encrypted file “secret.txt” and write a C++ that decrypts it. To help you in
this task here is a link to a frequency analysis of the English alphabet
http://www.richkni.co.uk/php/crypta/freq.php
