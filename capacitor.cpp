#include "capacitor.h"

using namespace std;

capacitor::capacitor(double c){ capacitance = c; impedence(0, -1 / capacitance); idealCmpt = true; };//For illustration when printing out component library, the impedence (freq dependent) will be shown with angular freq = 1;
capacitor::capacitor(double ZRe, double ZIm){ impedence(ZRe, ZIm); idealCmpt = false; numNonIdeal++; };
string capacitor::label()const{ return "C"; };
void capacitor::calcImped(double f){ setFreq(f); if (idealCmpt == true){ impedence(0.0, -1 / (2 * pi*freq * capacitance)); } else{ /* impedence set already */ } };
