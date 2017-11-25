#include "resistor.h"

using namespace std;

resistor::resistor(double r){ resistance = r; impedence(resistance, 0); idealCmpt = true; };
resistor::resistor(double ZRe, double ZIm){ impedence(ZRe, ZIm); resistance = ZRe; idealCmpt = false; numNonIdeal++; };
string resistor::label()const{ return "R"; };
void resistor::calcImped(double f){ setFreq(f); if (idealCmpt == true){ impedence(resistance, 0); } else{ /* impedence set already */ } };
int getNI(){ resistor myres(0); return myres.numNonIdeal; } //must be friends with a class which can be instantiated.