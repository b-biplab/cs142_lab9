#include<iostream>
#include "Queue.h"
using namespace std;

template<class T>
class BinarySearchTree {
	/*
	 * All important stuff happens here
	 * Methods:
	 */

	class Node {
		/*
		 * Class for nodes of the binary search tree.
		 * Contains a data storage unit and links to its
		 * parent and children.
		 */
		public:
			T data;
			Node* parent;
			Node* right;
			Node* left;
	
			Node() {
				data = T(NULL);
				parent = right = left = NULL;
			}
	};
	// temporary:
	public:

	// Address of the root node of the tree
	Node* root;
	int n;

	/* 
	 * Private member functions to do shady stuff:
	 * 	Node* find(T, Node*);
	 */

	Node* getNode(T key, Node* p) {
		if (p == NULL) {
			return NULL;
		}

		if (p->data == key) {
			return p;
		} else if (p->data > key) {
			getNode(key, p->left);
		} else {
			getNode(key, p->right);
		}
	}


	public:
		// Constructor
		BinarySearchTree() {
			root = NULL;
			n = 0;
		}

		/*
		 * Supported methods:
		 *	Node* getRoot();
		 *	T max(Node*)
		 *	T min(Node*)
		 *	bool search(T, Node*);
		 *	bool insert(T, Node*);
		 *	bool remove(T);
		 */

		Node* getRoot() {
			return root;
		}

		Node* max(Node* p) {
			if (p->right == NULL)
				return p;

			max(p->right);
		}

		Node* min(Node* p) {
			if (p->left == NULL)
				return p;

			min(p->left);
		}

		bool search(T key, Node* p) {
			if (p == NULL)
				return false;

			if (p->data == key) {
				return true;
			} else if (p->data < key) {
				search(key, p->right);
			} else {
				search(key, p->left);
			}
		}

		bool insert(T key, Node*& r, Node* p) {
			if (r == NULL) {
				Node* new_node = new Node;
				new_node->data = key;
				r = new_node;
				r->parent = p;
				return true;
			}

			if (r->data == key) {
				return false;
			} else if (r->data < key) {
				insert(key, r->right, r);
			} else {
				insert(key, r->left, r);
			}
		}

		void splice(Node*& u) {
			/*
			 * Has absolutely no checks built in.
			 * Use at your own risk.
			 */

			Node* s = NULL;
			Node* p = NULL;

			if (u->right != NULL) {
				s = u->right;
			} else {
				s = u->left;
			}

			if (u == root) {
				root = s;
				p = NULL;
			} else {
				cout << u->parent << endl;
				p = u->parent;
				cout << "not working" << endl;
				if (p->left == u) {
					cout << "yes" << endl;
					p->left = s;
				} else {
					cout << "splicing" << endl;
					p->right = s;
				}
			}

			if (s != NULL) {
				s->parent = p;
			}

			delete u;
		}

		bool remove(T key) {
			Node* u = getNode(key, root);

			if (u->left == NULL || u->right == NULL) {
				splice(u);
				delete u;
			} else {
				Node* v = min(u->right);
				u->data = v->data;
				splice(v);
				delete v;
			}

			return true;
		}

		void display(Node* p) {
			if (p == NULL)
				return;

			display(p->left);
			cout << p->data << endl;
			display(p->right);
		}

		int count(Node* r) {
			if (r == NULL) {
				return 0;
			} else {
				return 1 + count(r->right) + count(r->left);
			}
		}

		void rangeSearch(T k1, T k2, Node* r) {
			if (r == NULL)
				return;

			if (r->data > k1)
				rangeSearch(k1, k2, r->left);

			if (r->data < k2)
				rangeSearch(k1, k2, r->right);

			if (k1 <= r->data && r->data <= k2)
				cout << r->data << endl;

		}

		int countInRange(T k1, T k2, Node* r) {
			if (r == NULL)
				return 0;

			if (k1 <= r->data && r->data <= k2) {
				return 	1 +
						countInRange(k1, k2, r->left) +
						countInRange(k1, k2, r->right);
			} else if (r->data < k1) {
				return countInRange(k1, k2, r->right);
			} else {
				return countInRange(k1, k2, r->left);
			}
		}
};


int main() {
	BinarySearchTree<int> bst;
	for (int i=0; i<15; ++i)
		bst.insert(rand()%100, bst.root, NULL);
	
	bst.display(bst.root);
	cout << endl;
	bst.rangeSearch(0,40,bst.root);
	cout << "foo " << bst.countInRange(0,40,bst.root);

	return 0;
}
