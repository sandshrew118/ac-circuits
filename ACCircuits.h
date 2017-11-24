#ifndef ACCircuits_h
#define ACCircuits_h 

#include"complexNums.h"
#include<vector>

using namespace std;
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

class parallelSet: public component{
private:
	vector < vector <component *> > vecSeries; //vector of series. vector <component*> is a series.
	int index; //index in main pSet vector. Use for labels.
public:
	virtual ~parallelSet(){};
	parallelSet();
	parallelSet(vector <component*> series1, vector <component*> series2);// make constructor with arbitrary number of series ??
	//Cannot linearly add up the impedence of a parallel if new components were to be added to the parallel set. Safer to calculate it every time.
	void calcImped(double f);
	string label() const;
	void addSeries(vector <component*> series);
	//delete a series ??
	void setIndex(int);
	int getIndex();
	friend ostream & operator << (ostream & os, const parallelSet& myPSet);

};

class circuit{
private:
	double freq;
	complex impedence;
	vector <component*> cmpt_S;
public:
	~circuit(){ /*cout << "called ~circuit" << endl;*/ };
	circuit(double f);

	void addComponent(component* cmpt_ptr);
	complex getImpedence() const;
	double getF();
	friend ostream & operator << (ostream &, const circuit &);

};

ostream & operator << (ostream & os, const circuit & mycircuit);
ostream & operator << (ostream & os, const parallelSet& myPSet);
int getNI();

#endif
