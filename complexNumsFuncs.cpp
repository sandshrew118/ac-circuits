#include"complexNums.h"

using namespace std;
//using namespace myComplex;

complex:: complex(){ re = im = 0; }
complex:: complex(double r, double i){ re = r; im = i; }

void complex:: printReIm() const { cout << re << " " << im << "i" << endl; }
double complex:: getRe() const { return re; }
double complex:: getIm() const { return im; }
double complex:: getMod() const { return (sqrt(re*re + im*im)); }
double complex:: getArg() const { return (atan(im / re)); }
complex complex:: compxConj() const {
	complex result(re, -im);
	return result;
}
complex complex:: operator +(const complex & rNum) const {
	complex result(re + rNum.re, im + rNum.im);
	return result;
}
complex complex:: operator -(const complex & rNum) const {
	complex result(re - rNum.re, im - rNum.im);
	return result;
}
complex complex:: operator *(const complex & rNum) const {
	complex result(re * rNum.re - im * rNum.im, re * rNum.im + im * rNum.re);
	return result;
}
complex complex:: operator /(double rNum){
	complex result(re / rNum, im / rNum);
	return result;
}
complex complex:: operator /(const complex & rNum){
	complex numerator(*this * rNum.compxConj());
	complex denominator(rNum * rNum.compxConj());
	if (denominator.im == 0){
		return numerator / denominator.re;
	}
	else{
		cout << "> ERROR denominator im = " << denominator.im << endl;
		terminate();
	}
}
complex complex:: operator()(const double a, const double b){ re = a; im = b; return *this; };
complex complex:: operator += (const complex Cnum){ *this = *this + Cnum; return *this; };

//Friend functions
complex operator / (const double scalar, const complex & mynum){
	return (mynum.compxConj() / (mynum.getRe() * mynum.getRe() + mynum.getIm() * mynum.getIm()));
}
// Function to overload << operator for complex numbers
ostream & operator << (ostream & os, const complex & z){
	if (z.getIm() >= 0){
		os << z.getRe() << " +" << z.getIm() << "i";
	}
	else{
		os << z.getRe() << " " << z.getIm() << "i";
	}
	return os;
}
istream & operator >> (istream & is, complex & z){
	//accepts forms: a +bi or a + bi
	string temp, unformIm, unformRe;
	getline(cin, temp);
	stringstream tempss(temp);
	tempss >> unformRe >> unformIm;
	z.re = stod(unformRe);

	//do cases of a + bi first
	if (unformIm == "+"){
		tempss >> unformIm;

		//This block of code is repeated once unformIm == bi
		string::iterator strit = unformIm.end() - 1;
		if (*strit == 'i'){
			unformIm.pop_back();
			cout << "assign to z.im = " << unformIm << endl;
			z.im = stod(unformIm);
		}
		else{
			cout << "ERROR with input. i should be the last character." << endl;
		}
	}
	else if (unformIm == "-"){
		tempss >> unformIm;

		string::iterator strit = unformIm.end() - 1;
		if (*strit == 'i'){
			unformIm.pop_back();
			cout << "assign to z.im = " << unformIm << endl;
			z.im = -1 * stod(unformIm);
		}
		else{
			cout << "ERROR with input. i should be the last character." << endl;
		}
	}
	else{
		//should be of form a +bi
		string::iterator strit = unformIm.end() - 1;
		if (*strit == 'i'){
			unformIm.pop_back();
			cout << "assign to z.im = " << unformIm << endl;
			z.im = stod(unformIm);
		}
		else{
			cout << "ERROR with input. i should be the last character." << endl;
		}
	}

	return is;
}

bool isThisNum(string mystring){
	bool digitCheck = false; //check there is at least one digit in the string.
	unsigned int countDot = 0;
	unsigned int i = 0;

	//check not empty
	if (mystring.size() == 0){ return false; }
	//check whether first char is a sign
	if (mystring[0] == '+' || mystring[0] == '-'){
		i++;
	}
	//at least one of the characters must be a digit.
	//make sure only one . is allowed in the number. This way .521 and 131. are both accepted as numbers.
	while (i < mystring.size()){
		if (mystring[i] == '.'){
			countDot++;
			if (countDot > 1){ return false; }
		}
		else if (!isdigit(mystring[i])){ return false; }
		else //must have been a number (slightly inefficient) to keep initialising.
		{
			digitCheck = true;
		}
		i++;
	}
	//if it got through string with max of one '.' and at least one char was a digit, its true.
	if (digitCheck == false){ return false; }
	else{ return true; }
}