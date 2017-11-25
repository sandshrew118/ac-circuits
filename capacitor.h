#ifndef capacitor_h
#define capacitor_h

#include "component.h"

class capacitor : public component{
private:
	double capacitance;
	bool idealCmpt;
public:
	virtual ~capacitor(){ /*cout << "called ~capacitor" << endl; */ };
	capacitor(double c);
	capacitor(double ZRe, double Zim);
	string label() const;
	void calcImped(double f);
};

#endif