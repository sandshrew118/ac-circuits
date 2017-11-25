#ifndef parallelset_h
#define parallelset_h

#include<vector>

#include "component.h"

//definition: a component which encapsulates the parallel elements within a circuit.
class parallelSet : public component{
private:
	vector < vector <component *> > vecSeries; //vector of series. vector <component*> is a series.
	int index; //index in main pSet vector. Use for labels.
public:
	virtual ~parallelSet(){};
	parallelSet();
	parallelSet(vector <component*> series1, vector <component*> series2);// make constructor with arbitrary number of series ??
	//Cannot linearly add up the impedence of a parallel if new components were to be added to the parallel set. Safer to calculate it every time.
	void calcImped(double f);
	string label() const;
	void addSeries(vector <component*> series);
	//delete a series ??
	void setIndex(int);
	int getIndex();
	friend ostream & operator << (ostream & os, const parallelSet& myPSet);

};

#endif