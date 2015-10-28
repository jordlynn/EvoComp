#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include "individual.h"
#define POP 50
#define GENERATIONS 200
#define TOURNYSIZE 12 // Make sure this is even!
using namespace std;

// Proto
void Tournament(individual population[POP]);
void PrintBest(individual ApexIndividual);
void AntiSelect(individual population[POP], individual *tributes[TOURNYSIZE]);

int main(){
	ofstream fOut ("data.csv");
	ofstream nOde ("node.csv");
	srand(time(NULL));
	individual population[POP];
	double tmp;
	int best;
	double tmpDepth = 0;

	for(int i= 0; i < POP; i++){
		population[i].Generate(rand()%3+4);
	}

	for(int j=0; j < GENERATIONS; j++){
		for(int k=0; k < POP; k++){
			population[k].Evaluate();
			fOut << population[k].GetFitness() << ", ";
			tmpDepth += population[k].GetDepth();
		}
		fOut << endl;
		tmpDepth = tmpDepth / POP;
		nOde << tmpDepth << endl;
		Tournament(population);
		if(j%100 == 0)cout << j << endl;
	}
	tmp = population[0].GetFitness();
	for(int k=0; k < POP; k++){
		if(tmp > population[k].GetFitness()){
			tmp = population[k].GetFitness();
			best = k;
		}
	}

	population[best].Print();


	fOut.close();
	nOde.close();
	return 0;
}

void Tournament(individual population[POP]){
	individual *tributes[TOURNYSIZE];
	int index[TOURNYSIZE];
	int* found;
	bool iterate = false;

	for(int l=0; l < TOURNYSIZE; l++)
		index[l] = -1; // Initialize array

	// Now fill copetitor positions.
	for(int i=0; i < TOURNYSIZE; i++){
		do{
			iterate = false;
			index[i] = rand()%POP;
			for(int j=0; j < i; j++){
				if(index[i] == index[j])
					iterate = true;
			}
		}while(iterate);
		tributes[i] = &population[index[i]];
		iterate = true;
	}

	// Now sort the tributes array!
	sort(begin(tributes), end(tributes), [](individual* a, individual* b) { return a->GetFitness() < b->GetFitness(); });

	for(int k=0; k < (TOURNYSIZE/2); k++)
		tributes[k]->CrossOver(tributes[k++]);

	//AntiSelect(population, tributes);
}

void AntiSelect(individual population[POP], individual *tributes[TOURNYSIZE]){
	individual *terribleIndividuaIndex [POP];
	double tmp = population[0].GetFitness();

	for(int i=0; i < POP; i++){
		terribleIndividuaIndex[i] = &population[i];
	}

	sort(begin(terribleIndividuaIndex), end(terribleIndividuaIndex), [](individual* a, individual* b) { return a->GetFitness() > b->GetFitness(); });
	// We now have an ordered list from worst to best of the population.
	

	for(int k=0; k < TOURNYSIZE; k++){
		for(int l=0; l < POP; l++){
		if(terribleIndividuaIndex[l]->GetFitness() > tributes[k]->GetFitness()){
			terribleIndividuaIndex[l]->rootNode = tributes[k]->rootNode;
			terribleIndividuaIndex[l]->Evaluate();
			break;
		}
	}
	}

}

