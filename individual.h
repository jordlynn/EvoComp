#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include "node.h"

class individual{
public:
	individual();
	~individual();
	double GetFitness()const;
	double GetSize();
	void Evaluate();
	void CalcSize();
	void Erase();
	void Generate(int depth);
	void Print();
	void CalcRMS();
	void CrossOver(individual *toMate);
	void Mutation();
	void EarseTree(node* root);
	node *rootNode;
	void Update();
	double fitness;
private:
	
	int depth;

	int size;
	int terms;
	int nonTerms;
	
};

#endif