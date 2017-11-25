#include "inductor.h"

inductor::inductor(double i){ inductance = i; impedence(0, inductance); idealCmpt = true; }; //For illustration when printing out component library, the impedence (freq dependent) will be shown with angular freq = 1;
inductor::inductor(double ZRe, double ZIm){ impedence(ZRe, ZIm); idealCmpt = false; numNonIdeal++; };
string inductor::label()const{ return "L"; };
void inductor::calcImped(double f){ setFreq(f); if (idealCmpt == true){ impedence(0.0, 2 * pi*freq * inductance); } else{ /* impedence set already */ } };
