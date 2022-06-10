#include <iostream>

using namespace std;

struct Node {
	int data;

	Node* left;
	Node* right;
};

class BinarySearchTree {
public:
	Node* root;

	BinarySearchTree() {
		root = nullptr;
	}

	Node* InsertNode(Node* n, const int d) {
		//if root is null, insert the first value
		if (n == nullptr) {
			n = new Node();

			n->data = d;
			n->left = nullptr;
			n->right = nullptr;
		}
		else {
			//if node is not null, go to the appropriate node: left or right.
			if (d < n->data) {
				n->left = InsertNode(n->left, d);
			}
			else {
				n->right = InsertNode(n->right, d);
			}
		}

		return n;
	}

	//this is a recursive function
	void TraversalInOrder(Node* node) {
		if (node != nullptr) {
			//1. go left
			TraversalInOrder(node->left);
			//2. process Current Node
			cout << node->data << " ";
			//go right
			TraversalInOrder(node->right);
		}

		return;
	}


	//this is a recursive function
	void TraversalPostOrder(Node* node) {
		if (node != nullptr) {
			//1. go left
			TraversalPostOrder(node->left);
			//2. go right
			TraversalPostOrder(node->right);
			//3. process the current node
			cout << node->data << " ";
		}

	}

	//this is a recursive function for PreOrderTraversal
	void TraversalPreOrder(Node* node) {
		if (node != nullptr) {
			//1. process the node
			cout << node->data << " ";
			//2. go to left
			TraversalPreOrder(node->left);
			//3. go to right
			TraversalPreOrder(node->right);
		}
	}


	//this is a recursive function for search a key
	Node* SearchKey(Node* root, int key) {

		if (root == nullptr || root->data == key) return root;

		if (root->data > key) {
			//go left
			root = SearchKey(root->left, key);
		}
		else {
			// go right
			root = SearchKey(root->right, key);
		}

		return root;
	}

	//Delete a node
	Node* DeleteKey(Node* root, int key) {
		
		if (root == NULL) return root;
		if (key < root->key)
			root->left = deleteNode(root->left, key);
		else if (key > root->key)
			root->right = deleteNode(root->right, key);
		else 
		{
			if (root->left == NULL) {
				struct node* temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL) {
				struct node* temp = root->left;
				free(root);
				return temp;
			}
			struct node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
		return root;
	}

	//SUCCESSOR
	Node* Successor(Node* root, int key) {
		
		if (!root) return nullptr;
		root = root->right;
		while (root->left) root = root->left;
		return root;
	}

	//PREDECESSOR
	Node* Predecessor(Node* root, int key) {
		
		if (!root) return nullptr;
		root = root->left;
		while (root->right) root = root->right;
		return root;
	}


	//Minimum
	Node* Minumum(Node* root) {
		
		struct node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
		{
			current = current->left;
		}
		return(current);
	}

	//Maximum
	Node* Maximum(Node* root) {
		
		struct node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->right != NULL)
		{
			current = current->right;
		}
		return(current);
	}
};
