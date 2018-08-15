#pragma once

// Node in a zip tree
struct Node
{
	int rank;
	int key;
	Node *left;
	Node *right;
};

extern Node *root;

int randomRank();

// Assumes node x does not already exists in the tree
void insertNode(Node &x);

// Allows for specifying a custom rank for the node x to be inserted.
// Useful for testing purposes
void insertNode(Node &x, int r);

// Assumes node x exists in the tree
void deleteNode(Node &x);

// Returns true iff a node with the given key exists in the zip tree
bool search(int k);
