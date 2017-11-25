#include "component.h"

using namespace std;

int component::numNonIdeal(0);
complex component::getImpedence(){ return impedence; };
double component::ImpedenceMag(){ return impedence.getMod(); };
double component::getFreq(){ return freq; };
void component::setFreq(double f){ freq = f; };
double component::getPhaseDiff(){ return impedence.getArg(); };