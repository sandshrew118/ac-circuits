#ifndef component_h
#define component_h 

using namespace std;
#include"complexNums.h"

const double pi = 3.14159;

//Abstract base class
class component{
protected:
	double freq;
	complex impedence;
	static int numNonIdeal;
public:
	virtual ~component(){ /*cout << "called ~component" << endl;*/ };
	double getFreq();
	void setFreq(double f);
	complex getImpedence();
	double ImpedenceMag();
	double getPhaseDiff();
	virtual string label() const = 0; //pure virtual
	virtual void calcImped(double f) = 0;
};

#endif