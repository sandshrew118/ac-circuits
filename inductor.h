#ifndef inductor_h
#define inductor_h

#include "component.h"

class inductor : public component{
private:
	double inductance;
	bool idealCmpt;
public:
	virtual ~inductor(){ /*cout << "called ~inductor" << endl;*/ };
	inductor(double i);
	inductor(double ZRe, double Zim);
	string label() const;
	void calcImped(double f);
};

#endif