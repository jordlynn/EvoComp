#ifndef NODE_H
#define NODE_H
#define ARITY 2


class node{
private:
	
	int XsubI;
	

public:
	node();
	double value;
	int type; // Stores which operator or if a const which one.
	node *branch[ARITY];
	node *parent;
	void GenerateNode(int depth, int max, node*, int currentCount);
	double Eval(double Xi[]);
	void PrintTree();
	void Copy(node *original, node *p);
	node* RandomCross(node *root, int depth);
	void Mutate(node *mutant);
	int MaxDepth(node *node);
};


#endif