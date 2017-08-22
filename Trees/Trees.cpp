// Trees.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class Node
{

public:
	int value;
	Node* parent;
	Node* left;
	Node* right;
	char color;


	Node() {}

	Node(int in_val, Node* prnt = nullptr, Node* l_son = nullptr, Node* r_son = nullptr, char clr = 'r') {
		value = in_val;
		parent = prnt;
		right = r_son;
		left = l_son;
		color = clr;
	};

	~Node() {
		if (left != nullptr) {
			left->~Node();
		}
		
		if (right != nullptr) {
			right->~Node();
		}
	}

	void add(int val, bool unic = 1) {

		if ((left != nullptr) & (val < value)) {
			left->add(val);
		}
		else if ((right != nullptr) & (val > value)) {
			right->add(val);
		}
		else if ((val == value) & unic) {
			cout << "Node already exists";
			return;
		}
		else {
			add_son(val);
		}
	}

	void add_son(int val) {
		Node *n = new Node(val, parent);

		if (val < value) {
			left = n;
		}
		else if (val >= value) {
			right = n;
		}

		n->parent = this;
	}

	Node* find(int val, bool print = 0) {

		if (val == value) {
			if (print){
				print_node();
			}
			return this;
		}
		else if ((left != nullptr) & (val < value)) {
			left->find(val, print);
		}

		else if ((right != nullptr) & (val > value)) {
			right->find(val, print);
		}
		else {
			cout << "\nNo such node\n";
			return nullptr;
		}
	}

	Node*& prnt_side() {
		
		if (parent != nullptr) {
			if (parent->left == this) {
				return parent->left;
			}
			else {
				return parent->right;
			}
		}
	}

	Node* son_side() {
		if ((left == nullptr) ^ (right == nullptr)) {
			if (left != nullptr) {
				return left;
			}
			else {
				return right;
			}
		}
	} 

	void rot_l() {
		Node* b = right;

		b->parent = parent;
		prnt_side() = b;

		right = b->left;
		right->parent = this;

		parent = b;
		b->left = this;
	}

	void rot_r() {
		Node* a = left;

		a->parent = parent;
		prnt_side() = a;

		left = a->right;
		left->parent = this;

		parent = a;
		a->right = this;
	}

	void del() {
	
		if ((left == nullptr) & (right == nullptr)) {
			if (parent != nullptr) {
				prnt_side() = nullptr;
			}
			delete this;
		}
		else if ((left != nullptr) & (right != nullptr)) {
			Node* m = right;
			if (right->left == nullptr) {
				value = m->value;
				right = m->right;
				right->parent = this;
				delete m;
			}
			else {
				Node* x = m->left;
				value = x->value;
				x->del();
			}
		}
		else {
			prnt_side() = son_side();
			son_side()->parent = parent;
			delete this;
		}
	}

	void del(Node* n) {
		n->del();
	}

	void del(int val) {
		Node* n = find(val);

		if (n == nullptr) {
			return;
		}

		n->del();
	}

	void print() {

		print_node();

		if (left != nullptr) {
			left->print();
		}

		if (right != nullptr) {
			right->print();
		}
	}

    void print_node() {
        if (parent != nullptr) {
            cout << "\nparent val= "<< parent->value << '\n';
            if (parent->left == this) {
                cout << "side = left";
            }
            else {
                cout << "side = right";
            }
        }
		cout << "\nvalue= " << value << '\n';
    }
};


int main() {
	//Node *tree = new Node(6);
	//
	//int a[5] = { 9, 8, 11, 10, 12};

	//for (int i = 0; i < 5; i++)
	//{
	//	tree->add(a[i]);
	//}

	//tree->print();

	//tree->find(9)->rot_l();

	//tree->print();

	//delete tree;

	string c;

	while (strcmp(c,'exit') {
		cin >> c;

	}

	return 0;
}