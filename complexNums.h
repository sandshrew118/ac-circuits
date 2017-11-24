#ifndef complexNums_h
#define complexNum_h

#include<sstream>
#include<iostream>

using namespace std;

class complex{
	// Make function to overload operator<< a friend. Must be a friend because to print stuff we wont' be able to call if from the class.
	friend ostream & operator<<(ostream &os, const complex &z);
	friend istream & operator>>(istream &is, complex &z);
	friend complex operator / (const double scalar, const complex & mynum);

private:
	double re, im;
public:
	// Constructors & destructor
	complex();
	complex(double r, double i);
	~complex(){ /*cout << "complex destructor called\n";*/ }

	void printReIm() const; //Print. A limited alternative to overloading the ostream. The const after function means that member data cannot be modified.
	double getRe() const;
	double getIm() const;
	double getMod() const;
	double getArg() const;

	// Return complex conjugate. Do not want to modify the member data. If did modify data, perhaps less destructor calls, but would be difficult to read and perform z1 * z1.compCong()
	complex compxConj() const;
	// Overload + operator for addition. Extend functionality by making it a friend function so that we can left add a scalar (real or im).
	complex operator +(const complex & rNum) const;
	// Overload - operator for subtraction
	complex operator -(const complex & rNum) const;
	// Overload * operator for multiplication, z1*z2
	complex operator *(const complex & rNum) const;
	//Overload operator / for z1 / real num.
	complex operator /(double rNum);
	// Overload / operator for division, z1/z2. Make denominator a real number using complex conjugate
	complex operator /(const complex & rNum);
	complex operator()(const double a, const double b);
	complex operator += (const complex Cnum);
};

ostream & operator<<(ostream &os, const complex &z);
istream & operator>>(istream &is, complex &z);
complex operator / (const double scalar, const complex & mynum);
bool isThisNum(string mystring);//not even a friend function, just a function I want to use in main program.



#endif