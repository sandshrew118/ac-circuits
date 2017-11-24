#include"ACCircuits.h"

using namespace std;

int component::numNonIdeal(0);
complex component:: getImpedence(){ return impedence; };
double component::ImpedenceMag(){ return impedence.getMod(); };
double component:: getFreq(){ return freq; };
void component::setFreq(double f){ freq = f; };
double component::getPhaseDiff(){ return impedence.getArg(); };

resistor::resistor(double r){ resistance = r; impedence(resistance,0); idealCmpt = true; };
resistor::resistor(double ZRe, double ZIm){ impedence(ZRe, ZIm); resistance = ZRe; idealCmpt = false; numNonIdeal++; };
string resistor:: label()const{ return "R"; };
void resistor::calcImped(double f){ setFreq(f); if (idealCmpt == true){ impedence(resistance, 0); } else{ /* impedence set already */ } };
int getNI(){ resistor myres(0); return myres.numNonIdeal; } //must be friends with a class which can be instantiated.

capacitor::capacitor(double c){ capacitance = c; impedence(0, -1/capacitance) ; idealCmpt = true; };//For illustration when printing out component library, the impedence (freq dependent) will be shown with angular freq = 1;
capacitor::capacitor(double ZRe, double ZIm){ impedence(ZRe, ZIm); idealCmpt = false; numNonIdeal++; };
string capacitor::label()const{ return "C"; };
void capacitor::calcImped(double f){ setFreq(f); if (idealCmpt == true){ impedence(0.0, -1 / (2 * pi*freq * capacitance)); } else{ /* impedence set already */ } };

inductor::inductor(double i){ inductance = i; impedence(0, inductance); idealCmpt = true; }; //For illustration when printing out component library, the impedence (freq dependent) will be shown with angular freq = 1;
inductor::inductor(double ZRe, double ZIm){ impedence(ZRe, ZIm); idealCmpt = false; numNonIdeal++; };
string inductor::label()const{ return "L"; };
void inductor::calcImped(double f){ setFreq(f); if (idealCmpt == true){ impedence(0.0, 2 * pi*freq * inductance); } else{ /* impedence set already */ } };

parallelSet::parallelSet(){};
parallelSet:: parallelSet(vector <component*> series1, vector <component*> series2){
	vecSeries.push_back(series1); vecSeries.push_back(series2);
};
void parallelSet:: calcImped(double f){
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
ostream & operator << (ostream & os, const parallelSet& myPSet){
	os << "Pset label: " << myPSet.label() << endl;

	for (unsigned int i = 0; i < myPSet.vecSeries.size() - 1; i++){
		for (unsigned int j = 0; j < myPSet.vecSeries[i].size(); j++){
			os << "---[ " << myPSet.vecSeries[i][j]->label() << " (" << myPSet.vecSeries[i][j]->getImpedence().getMod() << ", " << myPSet.vecSeries[i][j]->getImpedence().getArg() / pi << " pi ) ]";
		}
		os << endl << "|" << endl << "|" << endl;

	}
	//on last series in the set do not print the parallel wires.
	int i = myPSet.vecSeries.size() - 1;
	for (unsigned int j = 0; j < myPSet.vecSeries[i].size(); j++){
		os << "---[ " << myPSet.vecSeries[i][j]->label() << " (" << myPSet.vecSeries[i][j]->getImpedence().getMod() << ", " << myPSet.vecSeries[i][j]->getImpedence().getArg() / pi << " pi ) ]";
	}
	return os;
};


circuit:: circuit(double f){ freq = f; impedence(0, 0); };
complex circuit:: getImpedence() const { return impedence; };
void circuit:: addComponent(component* cmpt_ptr){
	cmpt_S.push_back(cmpt_ptr);
	cmpt_S[cmpt_S.size() - 1]->calcImped(freq);
	impedence += cmpt_ptr->getImpedence();
};
double circuit::getF(){ return freq; }
ostream & operator << (ostream & os, const circuit & mycircuit){
	os << "Key: [ label ( Impedence.Mod, Impedence.Arg/pi ) ]" << endl;
	os << "Circuit impedence = " << "( " << mycircuit.getImpedence().getMod() << ", " << mycircuit.getImpedence().getArg() / pi << " pi )"  << endl;
	os << "+ |---";
	for (unsigned int i = 0; i < mycircuit.cmpt_S.size(); i++){
		os << "[ " << mycircuit.cmpt_S[i]->label() << " (" << mycircuit.cmpt_S[i]->getImpedence().getMod() << ", " << mycircuit.cmpt_S[i]->getImpedence().getArg() / pi << " pi ) ]" << "----";
	}
	os << "| -";
	return os;
};
