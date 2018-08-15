#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "zipTree.h"

// Testing of zip tree operations based on figure 1 in the paper Zip Trees by Tarjan and Levy, 2018
// Ranks will be identical to the ones in figure 1, so the tree will be build deterministically
// Note that the testing is not very extensive
TEST_CASE("Testing of insertion, deletion, search in zip trees")
{
	// Build initial tree
	Node D = {};
	D.key = 3;
	insertNode(D, 2);
	Node F = {};
	F.key = 5;
	insertNode(F, 4);
	Node G = {};
	G.key = 6;
	insertNode(G, 0);
	Node H = {};
	H.key = 7;
	insertNode(H, 2);
	Node J = {};
	J.key = 9;
	insertNode(J, 0);
	Node L = {};
	L.key = 11;
	insertNode(L, 1);
	Node M = {};
	M.key = 12;
	insertNode(M, 2);
	Node S = {};
	S.key = 18;
	insertNode(S, 4);
	Node X = {};
	X.key = 23;
	insertNode(X, 2);

	// Define node with key K (value 10)
	Node K = {};
	K.key = 10;

	// Test selected parts of tree
	REQUIRE(root->key == F.key);
	REQUIRE(F.rank == 4);
	REQUIRE(F.left->key == D.key);
	REQUIRE(F.right->key == S.key);
	REQUIRE(S.left->key == H.key);

	// Test search
	REQUIRE(search(M.key));
	REQUIRE(!search(K.key));

	// Insert node K
	insertNode(K, 3);

	// Test K correctly placed in tree (check K correct child of parent node and paths P and Q (refer to paper) correct)
	REQUIRE(search(K.key));
	REQUIRE(S.left->key == K.key);
	REQUIRE(K.left->key == H.key);
	REQUIRE(K.right->key == M.key);
	REQUIRE(H.right->key == J.key);
	REQUIRE(M.left->key == L.key);

	// Delete node K
	deleteNode(K);

	// Test K deleted correctly (K no longer in the tree and path R (refer to paper) correct)
	REQUIRE(!search(K.key));
	REQUIRE(S.left->key == H.key);
	REQUIRE(H.right->key == M.key);
	REQUIRE(M.left->key == L.key);
	REQUIRE(L.left->key == J.key);

}
