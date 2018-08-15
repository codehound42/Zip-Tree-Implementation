#include <random>
#include "zipTree.h"

// Global variables
Node *root;
std::default_random_engine generator; // Note: No seeding is done unless it is done elsewhere in the program before using this generator
std::geometric_distribution<int> distribution(0.5);

int randomRank()
{
	return distribution(generator);
}

void insertNode(Node &x)
{
	insertNode(x, randomRank());
}

void insertNode(Node &x, int r)
{
	int rank = x.rank = r;
	int key = x.key;
	Node *cur = root; // Note: Different from pseudocode, x.root
	Node *prev = cur;

	while (cur != NULL && (rank < cur->rank || (rank == cur->rank && key > cur->key)))
	{
		prev = cur;
		cur = (key < cur->key) ? cur->left : cur->right;
	}

	if (cur == root) root = &x;
	else if (key < prev->key) prev->left = &x;
	else prev->right = &x;

	if (cur == NULL)
	{
		x.left = x.right = NULL;
		return;
	}
	if (key < cur->key) x.right = cur; else x.left = cur;
	prev = &x;

	while (cur != NULL)
	{
		Node *fix = prev;
		if (cur->key < key)
		{
			do
			{
				prev = cur;
				cur = cur->right;
			}
			while (!(cur == NULL || cur->key > key));
		}
		else
		{
			do
			{
				prev = cur;
				cur = cur->left;
			}
			while (!(cur == NULL || cur->key < key));
		}
		if (fix->key > key || (fix == &x && prev->key > key))
		{
			fix->left = cur;
		}
		else
		{
			fix->right = cur;
		}
	}

}

void deleteNode(Node &x)
{
	int key = x.key;
	Node *cur = root;
	Node *prev = cur;

	while (key != cur->key)
	{
		prev = cur;
		cur = (key < cur->key) ? cur->left : cur->right;
	}
	Node *left = cur->left;
	Node *right = cur->right;

	if (left == NULL) cur = right;
	else if (right == NULL) cur = left;
	else if (left->rank >= right->rank) cur = left;
	else cur = right;

	if (root == &x) root = cur;
	else if (key < prev->key) prev->left = cur;
	else prev->right = cur;

	while (left != NULL && right != NULL)
	{
		if (left->rank >= right->rank)
		{
			do
			{
				prev = left;
				left = left->right;
			}
			while (!(left == NULL || left->rank < right->rank));
			prev->right = right;
		}
		else
		{
			do
			{
				prev = right;
				right = right->left;
			} while (!(right == NULL || left->rank >= right->rank));
			prev->left = left;
		}
	}
}

bool search(int k)
{
	Node *cur = root;

	while (cur != NULL && cur->key != k)
	{
		cur = (k < cur->key) ? cur->left : cur->right;
	}

	if (cur == NULL) return false;
	return true;
}

