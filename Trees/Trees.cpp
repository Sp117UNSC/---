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
		prnt_side() = nullptr;
	}

	bool add(int val, bool unic = 1) {

		if ((left != nullptr) & (val < value)) {
			left->add(val);
		}
		else if ((right != nullptr) & (val > value)) {
			right->add(val);
		}
		else if ((val == value) & unic) {
			cout << "\nNode already exists\n";
			return false;
		}
		else {
			add_son(val);
			return true;
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
			if (print) {
				cout << "\nNo such node\n";
			}
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
				right->parent = this;
				right = m->right;
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

	bool del(int val) {
		Node* n = find(val, 1);

		if (n == nullptr) {
			return false;
		}
		else {
			n->del();
			return true;
		}
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

void cmds(Node*);
void help();

int main() {
	Node *tree = new Node(6);
	
	int a[5] = {9, 8, 11, 10, 12};

	for (int i = 0; i < 5; i++)
	{
		tree->add(a[i]);
	}

	cout << "Type \"help\" to see the list of commands\n";

	cmds(tree);

	delete tree;

	return 0;
}

void cmds(Node* tree) {
	string c;

	bool print_mode = true;
	bool cmd_print = true;

	while (c != "exit") {

		if ((print_mode) & (tree != nullptr) & cmd_print) {
			tree->print();
			cout << "\n";
		}

		cmd_print = true;

		cout << "\n";
		getline(cin, c);
		while (c.back() == ' ') {
			c.erase(c.end()-1);
		}

		if (c.find("add ") == 0) {
			bool success;
			if (tree == nullptr) {
				tree = new Node(stoi(c.substr(c.rfind(" ") + 1)));
			}
			else {
				success = tree->add(stoi(c.substr(c.rfind(" ") + 1)));
			}
			if (!success) {
				cmd_print = false;
			}
		}
		else if ((c.find("find ") == 0) & (tree != nullptr)) {
			tree->find(stoi(c.substr(c.rfind(" ") + 1)), 1);
			cmd_print = false;
		}
		else if ((c.find("del subtree ") == 0) & (tree != nullptr)) {
			Node *n = tree->find(stoi(c.substr(c.rfind(" ") + 1)));
			delete n;
			if (n == tree) {
				tree = nullptr;
			}
		}
		else if ((c.find("del tree") == 0) & (tree != nullptr)) {
			delete tree;
			tree = nullptr;
		}
		else if ((c.find("del ") == 0) & (tree != nullptr)) {
			bool success;
			success = tree->del(stoi(c.substr(c.rfind(" ") + 1)));
			if (!success) {
				cmd_print = false;
			}
		}
		else if (c.find("print mode ") == 0) {
			print_mode = stoi(c.substr(c.rfind(" ") + 1));
			cmd_print = false;
		}
		else if (c.find("print mode") == 0) {
			cout << "\nprint mode " << print_mode << '\n';
			cmd_print = false;
		}
		else if ((c.find("print") == 0) & (tree != nullptr)) {
			cout << '\n';
			tree->print();
			cmd_print = false;
		}
		else if (c.find("help") == 0) {
			cout << '\n';
			help();
			cmd_print = false;
		}
		else {
			cout << "\nWrong command\n";
			cmd_print = false;
		}

	}

}
void help() {
	cout << "\nadd [val]         - adds a node with value [val] to the tree,\n";
	cout << "                    or creates new tree if tree is emty\n";
	cout << "\ndel [val]         - deletes node with the value [val]\n";
	cout << "\ndel subtree [val] - deltes node vith the value [val] and all his subtrees\n";
	cout << "\ndel tree          - deletes whole tree\n";
	cout << "\nprint             - prints tree\n";
	cout << "\nprint mode [val]  - displays(sets when [val] is given) print_mode parameter,\n";
	cout << "                    which enables tree pritnting after each change\n";
	cout << "\nhelp              - shows the list of commans\n";
}