#ifndef ACCircuits_h
#define ACCircuits_h 

#include"capacitor.h"
#include"resistor.h"
#include"inductor.h"
#include"parallelset.h"
#include"circuit.h"

ostream & operator << (ostream & os, const circuit & mycircuit);
ostream & operator << (ostream & os, const parallelSet& myPSet);

#endif
