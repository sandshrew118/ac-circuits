#include "circuit.h"

circuit::circuit(double f){ freq = f; impedence(0, 0); };
complex circuit::getImpedence() const { return impedence; };
void circuit::addComponent(component* cmpt_ptr){
	cmpt_S.push_back(cmpt_ptr);
	cmpt_S[cmpt_S.size() - 1]->calcImped(freq);
	impedence += cmpt_ptr->getImpedence();
};
double circuit::getF(){ return freq; }