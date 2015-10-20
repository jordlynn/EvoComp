#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <fstream>
#include <string>
#include "individual.h"
#include "math.cpp"
#define DOM 200.0
#define subI 10

using namespace std;

individual::~individual(){
	rootNode = NULL;
	fitness = -1;
}

individual::individual(){
	rootNode = new node;
	depth = 0;
	size = 0;
	terms = 0;
	nonTerms = 0;
	fitness = 0.0;
}

void individual::Generate(int treeDepth){
	rootNode = new node;
	depth = 0;
	rootNode->GenerateNode(0, treeDepth, NULL, 1);
	depth = rootNode->MaxDepth(rootNode);
}
 
void individual::Print(){
	rootNode->PrintTree();
	cout << endl;
}

void individual::Evaluate(){
	double tmp;
	fitness=0.0;
	double arry[subI];
	double expected;
	int indexer= 0;
	string tempCharacter;
	cout.precision(15);
	ifstream fIn ("GPProjectData.csv");
	getline(fIn, tempCharacter);
	for(int i=0; i < DOM; i++){
		while(indexer < 11){
			getline(fIn, tempCharacter, ',');
			tmp = stod(tempCharacter);
			if(indexer < 10){
				arry[indexer] = tmp;
			}
			else if(indexer == 10){
				expected = tmp;
			}
			indexer++;
		}
		indexer = 0;
		fitness = (expected - rootNode->Eval(arry));
		fitness = pow(fitness, 2);
	}

	fitness = fitness/DOM;
	fitness = (double)(sqrt(fitness));
	fIn.close();
}

double individual::GetFitness()const{
	return fitness;
}

int individual::GetDepth(){
	return depth;
}

void individual::CrossOver(individual *toMate){
	node *nodetmpParent;
	node *node2tmpParent;
	unique_ptr <individual>holder (new individual);
	unique_ptr <individual> holder2 (new individual);

	// Intialize and find info for holders.
	holder2->rootNode->Copy(rootNode, NULL);
	holder->rootNode->Copy(toMate->rootNode, NULL);
	holder->depth = holder->rootNode->MaxDepth(holder->rootNode);
	holder2->depth = holder2->rootNode->MaxDepth(holder2->rootNode);

	// Two random points in the two trees.
	node *nodePoint = holder->rootNode->RandomCross(holder->rootNode, rand()%1+holder->depth);
	node *nodePointTwo = holder2->rootNode->RandomCross(holder2->rootNode, rand()%1+holder2->depth);

	nodetmpParent = nodePoint->parent;
	node2tmpParent = nodePointTwo->parent;

	if(nodetmpParent->branch[0] == nodePoint)
		nodetmpParent->branch[0] = nodePointTwo;
	else
		nodetmpParent->branch[1] = nodePointTwo;
	nodePointTwo->parent = nodetmpParent;

	if(node2tmpParent->branch[0] == nodePointTwo)
		node2tmpParent->branch[0] = nodePoint;
	else
		node2tmpParent->branch[1] = nodePoint;
	nodePoint->parent = node2tmpParent;

	holder->Mutation();
	holder2->Mutation();

	holder2->Evaluate();
	holder->Evaluate();


	// If the offspring arent' better delete them.
	if(holder->GetFitness() < toMate->GetFitness())
		toMate->rootNode = holder->rootNode;

	if(holder2->GetFitness() < GetFitness())
		rootNode = holder2->rootNode;

	nodePointTwo = NULL;
	nodePoint = NULL;
	node2tmpParent = NULL;
	nodetmpParent = NULL;

}

void individual::EarseTree(node* root){
	if(root->branch[0] !=NULL) EarseTree(root->branch[0] );
	if(root->branch[1] !=NULL) EarseTree(root->branch[1]);
	delete root;
}


void individual::Mutation(){
	rootNode->Mutate(rootNode);
}