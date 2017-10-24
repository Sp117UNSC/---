// Trees.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

template <class Item>
class Node{

private:

	void add_son(Item val) {
		Node *n = new Node(val);

		if (val < value) {
			left = n;
		}
		else if (val >= value) {
			right = n;
		}

		n->parent = this;

		//FIXME!
		n->insert_balancing();
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

	//Red-Black balancing

	void insert_balancing(int c = 0) {

		if (c != 5) {
			if (parent == nullptr) {
				c = 1;
			}
			else if (parent->color == 'b') {
				c = 2;
			}
			else if (uncle() != nullptr) {
				if (uncle()->color == 'r') {
					c = 3;
				}
				else {
					c = 4;
				}
			}
		}

		switch (c) {

		case 1:
			color = 'b';
			break;

		case 2:
			return;

		case 3:
			parent->color = 'b';
			uncle()->color = 'b';
			grandpa()->color = 'r';
			grandpa()->insert_balancing();
			break;

		case 4:

			if ((this == parent->right) & (parent == grandpa()->left)) {
				parent->rot_l();
				left->insert_balancing(5);
			}
			else if ((this == parent->left) & (parent == grandpa()->right)) {
				parent->rot_r();
				right->insert_balancing(5);
			}
			else {
				insert_balancing(5);
			}
			break;

		case 5:
			parent->color = 'b';
			grandpa()->color = 'r';

			if ((this == parent->left) & (parent == grandpa()->left)) {
				grandpa()->rot_r();
			}
			else {
				grandpa()->rot_l();
			}
		}
	}

	void rot_l() {
		Node* b = right;

		b->parent = parent;
		if (parent != 0) {
			prnt_side() = b;
		}

		right = b->left;
		if (right != nullptr) {
			right->parent = this;
		}

		parent = b;
		b->left = this;
	}

	void rot_r() {
		Node* a = left;

		a->parent = parent;
		if (parent != 0) {
			prnt_side() = a;
		}

		left = a->right;
		if (left != nullptr) {
			left->parent = this;
		}

		parent = a;
		a->right = this;
	}

	Node* grandpa() {
		if ((parent != nullptr) & (parent->parent != nullptr)) {
			return parent->parent;
		}
		else {
			return nullptr;
		}
	}

	Node* uncle() {
		if (grandpa() == nullptr) {
			return nullptr;
		}

		if (grandpa()->left == parent) {
			return grandpa()->right;
		}
		else {
			return grandpa()->left;
		}
	}

public:

	Item value;
	Node* parent;
	Node* left;
	Node* right;
	char color;


	Node() {}

	Node(Item in_val, char clr = 'r', Node* prnt = nullptr, Node* l_son = nullptr, Node* r_son = nullptr) {
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

	bool add(Item val, bool unic = 1) {

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

	Node* find(Item val, bool print = 0) {

		Node* res = nullptr;
		if (val == value) {
			if (print) {
				print_node();
			}
			res = this;
		}
		else if ((left != nullptr) & (val < value)) {
			res = left->find(val, print);
		}
		else if ((right != nullptr) & (val > value)) {
			res = right->find(val, print);
		}
		else if (res == nullptr)
			if (print) {
				cout << "\nNo such node\n";
			}
		return res;
	}

	bool del(Item val) {
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
		cout << "color= " << color << '\n';
    }
};

//void cmds(Node*);
//void help();

int main() {
	/*Node<void> *tree = new Node<void>();


	cout << "type \"help\" to see the list of commands\n";

	cmds(tree);*/

	Node<string> *tree = new Node<string>("Mazafaka");
	tree->add("Nuts!");
	tree->add("Bravo");
	tree->add("Sierra");
	tree->add("Never before!");
	tree->del("Nuts");
	tree->print();

	delete tree;

	return 0;
}

//void cmds(Node* tree) {
//	string c;
//
//	bool print_mode = true;
//	bool cmd_print = true;
//
//	while (c != "exit") {
//
//		if ((print_mode) & (tree != nullptr) & cmd_print) {
//			tree->print();
//			cout << "\n";
//		}
//
//		cmd_print = true;
//
//		cout << "\n";
//		getline(cin, c);
//		while (c.back() == ' ') {
//			c.erase(c.end()-1);
//		}
//
//		if (c.find("add nodes") == 0) {
//			getline(cin, c);
//			if (c.back() != ' ') {
//				c.append(" ");
//			}
//			while (c.begin() != c.end()) {
//				string s = c.substr(0, c.find(' ')+1);
//				c.erase(0, c.find(' ')+1);
//				if (tree != nullptr) {
//					tree->add(stoi(s));
//				}
//				else {
//					tree = new Node(stoi(s),'b');
//				}
//
//				while (tree->parent != nullptr) {
//					tree = tree->parent;
//				}
//			}
//		}
//		else if (c.find("add ") == 0) {
//			bool success;
//			if (tree == nullptr) {
//				tree = new Node(stoi(c.substr(c.rfind(" ") + 1)), 'b');
//				success = true;
//			}
//			else {
//				success = tree->add(stoi(c.substr(c.rfind(" ") + 1)));
//			}
//			if (!success) {
//				cmd_print = false;
//			}
//			
//			while (tree->parent != nullptr) {
//				tree = tree->parent;
//			}
//
//		}
//		else if ((c.find("find ") == 0) & (tree != nullptr)) {
//			tree->find(stoi(c.substr(c.rfind(" ") + 1)), 1);
//			cmd_print = false;
//		}
//		else if ((c.find("del subtree ") == 0) & (tree != nullptr)) {
//			Node *n = tree->find(stoi(c.substr(c.rfind(" ") + 1)));
//			delete n;
//			if (n == tree) {
//				tree = nullptr;
//			}
//		}
//		else if ((c.find("del tree") == 0) & (tree != nullptr)) {
//			delete tree;
//			tree = nullptr;
//		}
//		else if ((c.find("del ") == 0) & (tree != nullptr)) {
//			bool success;
//			success = tree->del(stoi(c.substr(c.rfind(" ") + 1)));
//			if (!success) {
//				cmd_print = false;
//			}
//		}
//		else if (c.find("print mode ") == 0) {
//			print_mode = stoi(c.substr(c.rfind(" ") + 1));
//			cmd_print = false;
//		}
//		else if (c.find("print mode") == 0) {
//			cout << "\nprint mode " << print_mode << '\n';
//			cmd_print = false;
//		}
//		else if ((c.find("print") == 0) & (tree != nullptr)) {
//			cout << '\n';
//			tree->print();
//			cmd_print = false;
//		}
//		else if (c.find("help") == 0) {
//			cout << '\n';
//			help();
//			cmd_print = false;
//		}
//		else {
//			cout << "\nWrong command\n";
//			cmd_print = false;
//		}
//
//	}
//
//}
//void help() {
//	cout << "\nadd [val]         - adds a node with value [val] to the tree,\n";
//	cout << "                    or creates new tree if tree is empty\n";
//	cout << "\nadd nodes         - adds array of values separated py spaces to tree\n";
//	cout << "\ndel [val]         - deletes node with the value [val]\n";
//	cout << "\ndel subtree [val] - deltes node vith the value [val] and all its subtrees\n";
//	cout << "\ndel tree          - deletes whole tree\n";
//	cout << "\nprint             - prints tree\n";
//	cout << "\nprint mode [val]  - displays(or sets, when [val] is given) print_mode parameter,\n";
//	cout << "                    which enables tree pritnting after each change\n";
//	cout << "\nhelp              - shows the list of commans\n";
//}
