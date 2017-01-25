#include<iostream>
using namespace std;

class node{
public:
	node();
	node(int value);
	~node();
	friend void gothrough(node *p);

private:
	node *left, *right; // the left child and the right child pointer
	int number; // record the node's number
	int is_threadl, is_threadr; //the flag to record whether the pointer is a thread or not

	friend class op_tree_totum;//you could access all valuables in class op_tree_totum
};

//ctor
node::node(){
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//ctor
node::node(int value){
	number = value;
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//dtor
node::~node(){

}

class op_tree_totum{

public:
	op_tree_totum();
	~op_tree_totum();
	void insertion(int s);
	void deletion(int s);
	void inorder_run();
	void reverseorder_run();
	int size();

private:
	node *root, *head, *tail;
	int num;//caculate how many nodes in the totum
};

//ctor
op_tree_totum::op_tree_totum(){
	head = new node();
	tail = new node();
	head->right = tail; //initialize the head node to connect to the tail node
	tail->left = head;
	root = NULL;
	num = 0;
}

//dtor
op_tree_totum::~op_tree_totum(){
	node *p = root;
	if(p!=NULL)	gothrough(p);
	num = 0;
	if (head != NULL)delete head;
	if (tail != NULL)delete tail;
} void gothrough(node *p){
	if (p->is_threadl==0 && p->left!= NULL) gothrough(p->left);
	if (p->is_threadr==0 && p->right!= NULL) gothrough(p->right);
	delete p;
}

void op_tree_totum::insertion(int s){
	//TODO: fill in the code to do the insertion of the node with number s
	// insert root
    if(root == NULL){
        root = new node(s);
        root->right = tail;
        tail->left = root;
        root->left = head;
        head->right = root;
        ++num;
        return;
    }
    // search for a place to put a new node
    node *parent = root;
    while(1){
        if(parent->number == s) return; // s is already in the Tree;
        if(parent->number > s && parent->is_threadl == 0) parent = parent->left; // s should be put in the left subtree
        else if(parent->number < s && parent->is_threadr == 0) parent = parent->right; // s should be put in the right subtree
        else break;
    }
    // add new node
    ++num;
    if(parent->number > s){ // left child
        node *now = new node(s);
        now->left = parent->left;
        now->right = parent;
        parent->left = now;
        parent->is_threadl = 0;
        if(head->right == parent) head->right = now;
    } else { // right child
        node *now = new node(s);
        now->left = parent;
        now->right = parent->right;
        parent->right = now;
        parent->is_threadr = 0;
        if(tail->left == parent) tail->left = now;
    }
}

void op_tree_totum::deletion(int s){
	//TODO: fill in the code to do the deletion of the node with number s
    node *now = root; // the node needed to be deleted
    if(size() == 1){ // only root
        head->right = tail;
        tail->left = head;
        root = NULL;
        delete now;
        --num;
        return;
    }
    while(1){ // find s in the tree
        if(now->number > s && now->is_threadl == 0) now = now->left;
        else if(now->number < s && now->is_threadr == 0) now = now->right;
        else break;
    }
    if(now->number != s) return; // if s isn't in the Tree
    // push down s to the leaf and prepare to delete s
    while(now->is_threadl == 0 || now->is_threadr == 0){ // now has child
        // find the predecessor or successor node and swap them
        node *next = now;
        if(now->is_threadl == 0){ // now has left child, find the predecessor node
            next = now->left;
            while(next->is_threadr == 0) next = next->right;
        } else { // now has right child, find the successor node
            next = now->right;
            while(next->is_threadl == 0) next = next->left;
        }
        now->number = next->number; // swap two nodes
        now = next;
    }
    // now has no child
    if(now->right != tail && now->right->left == now){ // now is the left child of now's parent
        node *parent = now->right;
        parent->left = now->left;
        parent->is_threadl = 1;
        if(head->right == now) head->right = parent;
    } else if(now->left != head){ // now is the right child of now's parent
        node *parent = now->left;
        parent->right = now->right;
        parent->is_threadr = 1;
        if(tail->left == now) tail->left = parent;
    }
    delete now;
    --num;
}

void op_tree_totum::inorder_run(){
	//TODO: travel the tree from the head node to the tail node and output the values
	//You should NOT use stack or recurtion
    node *now = head->right;
    while(now != tail){
        cout << now->number << ' ';
        // find successor
        if(now->is_threadr == 0){
            now = now->right;
            while(now->is_threadl == 0) now = now->left;
        } else {
            now = now->right;
        }
    }
}

void op_tree_totum::reverseorder_run(){
	//TODO: travel the tree from the tail node to the head node and output the values
	//You should NOT use stack or recurtion
    node *now = tail->left;
    while(now != head){
        cout << now->number << ' ';
        // find predecessor
        if(now->is_threadl == 0){
            now = now->left;
            while(now->is_threadr == 0) now = now->right;
        } else {
            now = now->left;
        }
    }
}

int op_tree_totum::size(){
	return num;
}
