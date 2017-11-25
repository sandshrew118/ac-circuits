#include"ACCircuits.h"

using namespace std;

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
