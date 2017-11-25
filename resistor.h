#ifndef resistor_h
#define resistor_h

#include "component.h"

using namespace std;

class resistor : public component{
private:
	double resistance;
	bool idealCmpt;
public:
	virtual ~resistor(){ /*cout << "called ~resistor" << endl;*/ };
	resistor(double r);
	resistor(double ZRe, double Zim);
	string label() const;
	void calcImped(double f);

	friend int getNI();// to access numNonIdeal, but must be in a class which can be instantiated.
};

int getNI();

#endif