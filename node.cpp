#define MAX_OPER 4;
#define MIN_OPER 1;
#define add 0
#define sub 1
#define mult 2
#define divi 3
#define coeff 4
#define term 5
#define subI 3

#include "node.h"
#include <random>
#include <iostream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

// Random number generator
uniform_real_distribution<double> unif(0,10);
default_random_engine re;

node::node(){
	value = 0;
	type = -1;
	branch[0] = NULL;
	branch[1] = NULL;
	parent = NULL;
	XsubI = -1;
}

void node::GenerateNode(int depth, int max, node *p, int currentCount){
	parent = p; // pointer to parent node.


	if(depth >= max){
		type = rand()%2+4;
		if(type == coeff){
			value = unif(re);

			//cout << "gave: " << value << endl;
		}
		else if(type == term){
			XsubI = rand()%subI;
			value = 0.0;
		}else{
			//cout << "unknown case!" << endl;
		}
		branch[0] = NULL;
		branch[1] = NULL;
	}else if(depth >= 1){
		type =rand()%6;
		//cout << "assigned: " << type << endl;
		switch(type){
			case add:
			case sub:
			case mult:
			case divi:
				for(int i=0; i < 2; i++){
					branch[i] = new node;
					branch[i]->GenerateNode(depth+1, max, this, currentCount);
				}
				break;
			case coeff:
				value = unif(re);
				branch[0] = NULL;
				branch[1] = NULL;
				//cout << "gave: " << value << endl;
				break;
			case term:
				XsubI = rand()%subI;
				value = 0.0;
				branch[0] = NULL;
				branch[1] = NULL;
				currentCount++;
				//cout << "created x" << endl;
				break;
			default:
				cout << "unknown case!" << endl;
		}
	}else if(depth <= 0){
		type =rand()%4;
		//cout << "assigned: " << type << endl;
		switch(type){
			case add:
			case sub:
			case mult:
			case divi:
				for(int i=0; i < 2; i++){
					branch[i] = new node;
					branch[i]->GenerateNode(depth+1, max, this, currentCount);
				}
				break;
			default:
				cout << "unknown case!" << endl;

		}
	}
	//cout << "this node: " << depth << " type: " << type << endl;
}

int node::MaxDepth(node *node){
	if(node == NULL)
		return 0;
	else{
		int lDepth = MaxDepth(node->branch[0]);
		int rDepth = MaxDepth(node->branch[1]);

		if(lDepth > rDepth)
			return (lDepth);
		else return (rDepth+1);
	}
}

void node::PrintTree(){
	
	switch(type){
		case add:
			cout << "(";
			branch[0]->PrintTree();
			cout << " + ";
			branch[1]->PrintTree();
			cout << ")";
			break;
		case sub:
			cout << "(";
			branch[0]->PrintTree();
			cout << " - ";
			branch[1]->PrintTree();
			cout << ")";
			break;
		case mult:
			cout << "(";
			branch[0]->PrintTree();
			cout << " * ";
			branch[1]->PrintTree();
			cout << ")";
			break;
		case divi:
			cout << "(";
			branch[0]->PrintTree();
			cout << " / ";
			branch[1]->PrintTree();
			cout << ")";
			break;
		case coeff:
			cout << value;
			break;
		case term:
			cout << "x";
			cout << XsubI;
			break;
		default:
			cout << "Unkown Operator!" << endl;

	}
}

double node::Eval(double Xi[subI]){
	double left, right;
	switch(type){
		case add:
			left=branch[0]->Eval(Xi);
			right=branch[1]->Eval(Xi);
			return(left+right);
			break;
		case sub:
			left=branch[0]->Eval(Xi);
			right=branch[1]->Eval(Xi);
			return(left-right);
			break;
		case mult:
			left=branch[0]->Eval(Xi);
			right=branch[1]->Eval(Xi);
			return(left*right);
			break;
		case divi:
			left=branch[0]->Eval(Xi);
			right=branch[1]->Eval(Xi);
			if(right == 0)
				return 1;
			else
				return(left/right);
			break;
		case coeff:
			return value;
			break;
		case term:
			return Xi[XsubI];
			break;
		default:
			cout << "Unkown in EVAL" << endl;
	}
}


void node::Copy(node *original, node *p){
	type = original->type;
	parent = p;

	if(type < coeff){ // If the type isn't a constant or terminal
		for(int i=0; i < ARITY; i++){
			if(original->branch[i] != NULL){
				branch[i] = new node;
				branch[i]->Copy(original->branch[i], this);
			}else{
				branch[i]= NULL;
			}
		}
	}else if(type == coeff){ // integer
		value = original->value;
		branch[0] = NULL;
		branch[1] = NULL; 
	}else if(type == term){ // Variable
		XsubI = original->XsubI;
		branch[0] = NULL;
		branch[1] = NULL;
	}else{
		cout << "unkown type! - Error in Copy()" << endl;
	}
}



void node::Mutate(node *mutant){
	if(rand()%100 < 10){
		if(type < 4)
			type = rand()%4;
		else{
			type = rand()% 2+4;
			if(type == 4)
				value = rand()%10;
			else
				XsubI = rand()%subI;
		}
	}
	if(mutant->branch[0] != NULL)
		Mutate(mutant->branch[0]);
	if(mutant->branch[1] != NULL)
		Mutate(mutant->branch[1]);
}

node* node::RandomCross(node *root, int depth){
	node *brachToSwap = root;
	
	for(int i = depth; i > 0; i--){
		if(brachToSwap->branch[0] != NULL && brachToSwap->branch[1] != NULL){
			brachToSwap = branch[rand()%2];
		}
		else if(brachToSwap->branch[0] != NULL){
			brachToSwap = branch[0];
		}else if(brachToSwap->branch[1] != NULL){
			brachToSwap = branch[1];
		}
	}

	return brachToSwap;
}
