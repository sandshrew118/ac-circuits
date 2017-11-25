#include "parallelset.h"

parallelSet::parallelSet(){};
parallelSet::parallelSet(vector <component*> series1, vector <component*> series2){
	vecSeries.push_back(series1); vecSeries.push_back(series2);
};
void parallelSet::calcImped(double f){
	setFreq(f);
	complex invZ(0, 0); //inverese of the total Z. invZ = 1/z1 + 1/z2 +...
	for (unsigned int i = 0; i < vecSeries.size(); i++){
		complex seriesZ(0, 0);
		for (unsigned int j = 0; j < vecSeries[i].size(); j++){
			vecSeries[i][j]->calcImped(freq);
			seriesZ += vecSeries[i][j]->getImpedence();
		}
		invZ += 1 / seriesZ;
	}
	impedence = 1 / invZ;
};
string parallelSet::label() const { stringstream ss; ss << "P" << index; return ss.str(); };
void parallelSet::addSeries(vector <component*> series){
	vecSeries.push_back(series);
};
void parallelSet::setIndex(int a){ index = a; }
int parallelSet::getIndex(){ return index; }