#ifndef circuit_h
#define circuit_h

#include "component.h"
#include <vector>

//definition: here a circuit is simply defined as a series of components. All parallel components are taken care of within parallelSets.
class circuit{
private:
	double freq;
	complex impedence;
	vector <component*> cmpt_S;
public:
	~circuit(){ /*cout << "called ~circuit" << endl;*/ };
	circuit(double f);

	void addComponent(component* cmpt_ptr);
	complex getImpedence() const;
	double getF();
	friend ostream & operator << (ostream &, const circuit &);

};

#endif