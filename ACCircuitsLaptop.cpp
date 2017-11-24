#include"ACCircuits.h" //note difference between system header files and our own. Copies in forward declarations at this point.
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<string>

using namespace std;

int main(){
	//output file used to save all the objects at the end.
	string library = "library.txt";
	ofstream libraryFile(library);
	if (libraryFile.good()){
		cout << library << " opened successfully" << endl;
	}
	else
	{
		cerr << library << " not opened successfully. Exiting." << endl;
	}

	cout << "AC CIRCUITS BUILDER" << endl << "-----------------------" << endl;

	cout << "First, make a library of components. This can be added to later." << endl;
	vector <component*> myCmpts; //this is the component library!
	vector <circuit*> myCircuits;
	vector <parallelSet*> myPSets;

	cout << "Add a component with input: 'label' value (another value if non-ideal component)." << endl << "'label' is R = resistor, C = capacitor, L = inductor" << endl << "One value corresponds to relevant quantity e.g. resistance for R. Two values corresponds to real and im parts of impedence. Input 'x' to exit." << endl;
	cout << "SI units are used: R [Ohms], C [Farads], L [Henrys], impedence Z [Ohms]" << endl;
	while (1){
		cout << "> ";
		string* input;
		try{
			input = new string[3];
		}
		catch (bad_alloc memFail){ cout << "Memory allocation failure." << endl; exit(1); }
		string lineIn;
		getline(cin, lineIn);
		stringstream ss(lineIn);
		//Exception handling: check that the ss is empty after extractions, and that the 2nd and 3rd arguements are number and number/empty.
		//Nested try blocks allow to isolate better which variable was the exception.
		try{
			bool badInput;
			ss >> input[0] >> input[1] >> input[2]; // label, value, (another value if user wanted non-ideal component)

			if (ss.rdbuf()->in_avail() != 0 || input[0].size() == 0){ badInput = true; throw badInput; } //checks the number of input arguements was ok.
			if (input[0] == "x"){
				if (!isThisNum(input[1]) && input[1].size() != 0){ throw input[1]; }
			}
			else{
				if (!isThisNum(input[1])){ throw input[1]; }
				else if (stod(input[1]) < 0){ throw input[1]; }
				//If got here, then input[1] is a positive number.
				try{
					if (!isThisNum(input[2]) && input[2].size() != 0){ throw input[2]; }
				}
				catch (const string & e){ cout << "arguement 2'" << e << "' not valid input." << endl; continue; }
			}
		}
		catch (const bool & e){ cout << "badInput == " << e << ". The number of input arguements was not valid." << endl; continue; }
		catch (const string & e){ cout <<  "arguement 1'" << e << "' not valid input." << endl; continue; }

		if (input[0] == "x"){
			cout << "Finished making component library." << endl;
			break;
		}else if (input[0] == "R"){
			myCmpts.resize(myCmpts.size() + 1); //make a new pointer in the vector.
			if (input[2].size() == 0){	myCmpts[myCmpts.size() - 1] = new resistor(stod(input[1])); }
			else{ myCmpts[myCmpts.size() - 1] = new resistor(stod(input[1]), stod(input[2])); }			
		}else if (input[0] == "C"){
			myCmpts.resize(myCmpts.size() + 1);
			if (input[2].size() == 0){	myCmpts[myCmpts.size() - 1] = new capacitor(stod(input[1])); }
			else{ myCmpts[myCmpts.size() - 1] = new capacitor(stod(input[1]), stod(input[2])); }
		}else if (input[0] == "L"){
			myCmpts.resize(myCmpts.size() + 1);
			if (input[2].size() == 0){ myCmpts[myCmpts.size() - 1] = new inductor(stod(input[1]));	}
			else{ myCmpts[myCmpts.size() - 1] = new inductor(stod(input[1]), stod(input[2])); 	}
		}
		else{
			cout << "Sorry, I didn't understand that component input." << endl;
		}
		delete[] input;
	}
	cout << "Your library has size = " << myCmpts.size() << endl << endl;

	cout << "Key:'index' 'label' 'value'." << endl;
	cout << "For illustration, 'value' shown is the impedence. For ideal components, the impedence (frequency dependent) has been shown with angular freq. = 1." << endl;
	for (unsigned int i = 0; i < myCmpts.size(); i++){
		cout.precision(5);
		cout << i << " " << myCmpts[i]->label() << " " << myCmpts[i]->getImpedence() << endl;
	}
	cout << endl;

	while (1){
		cout << "What would you like to do?" << endl;
		cout << "1. Add more components to component library." << endl;
		cout << "2. Make a new parallel set." << endl;
		cout << "3. Make a new circuit." << endl;
		cout << "4. Exit." << endl;
		cout << ">> ";
		string ans;
		getline(cin, ans);
		cout << endl;
		if (ans == "1"){
			vector <component*> myCmpts; //this is the component library!
			vector <circuit*> myCircuits;
			vector <parallelSet*> myPSets; //only functions seen in base class can be accessed by vector of base class pointers.

			cout << "Add a component with input: 'label' value (another value if non-ideal component)." << endl << "'label' is R = resistor, C = capacitor, L = inductor" << endl << "One value corresponds to relevant quantity e.g. resistance for R. Two values corresponds to real and im parts of impedence. Input 'x' to exit." << endl;
			cout << "SI units are used: R [Ohms], C [Farads], L [Henrys], impedence Z [Ohms]" << endl;

			while (1){
				cout << "> ";
				string* input = new string[3];
				string lineIn;
				getline(cin, lineIn);
				stringstream ss(lineIn);
				//Exception handling: check that the ss is empty after extractions, and that the 2nd and 3rd arguements are number and number/empty.
				//Nested try blocks allow to isolate better which variable was the exception.
				try{
					bool badInput;
					ss >> input[0] >> input[1] >> input[2]; // label, value, (another value if user wanted non-ideal component)

					if (ss.rdbuf()->in_avail() != 0 || input[0].size() == 0){ badInput = true; throw badInput; } //checks the number of input arguements was ok.
					if (input[0] == "x"){
						if (!isThisNum(input[1]) && input[1].size() != 0){ throw input[1]; }
					}
					else{
						if (!isThisNum(input[1])){ throw input[1]; }
						else if (stod(input[1]) < 0){ throw input[1]; }
						//If got here, then input[1] is a positive number.
						try{
							if (!isThisNum(input[2]) && input[2].size() != 0){ throw input[2]; }
						}
						catch (const string & e){ cout << "arguement 2'" << e << "' not valid input." << endl; continue; }
					}
				}
				catch (const bool & e){ cout << "badInput == " << e << ". The number of input arguements was not valid." << endl; continue; }
				catch (const string & e){ cout << "arguement 1'" << e << "' not valid input." << endl; continue; }

				if (input[0] == "x"){
					cout << "Finished making component library." << endl;
					break;
				}
				else if (input[0] == "R"){
					myCmpts.resize(myCmpts.size() + 1); //make a new pointer in the vector.
					if (input[2].size() == 0){ myCmpts[myCmpts.size() - 1] = new resistor(stod(input[1])); }
					else{ myCmpts[myCmpts.size() - 1] = new resistor(stod(input[1]), stod(input[2])); }
				}
				else if (input[0] == "C"){
					myCmpts.resize(myCmpts.size() + 1);
					if (input[2].size() == 0){ myCmpts[myCmpts.size() - 1] = new capacitor(stod(input[1])); }
					else{ myCmpts[myCmpts.size() - 1] = new capacitor(stod(input[1]), stod(input[2])); }
				}
				else if (input[0] == "L"){
					myCmpts.resize(myCmpts.size() + 1);
					if (input[2].size() == 0){ myCmpts[myCmpts.size() - 1] = new inductor(stod(input[1])); }
					else{ myCmpts[myCmpts.size() - 1] = new inductor(stod(input[1]), stod(input[2])); }
				}
				else{
					cout << "Sorry, I didn't understand that component input." << endl;
				}
				delete[] input;
			}
			cout << "Your library has size = " << myCmpts.size() << endl << endl;

			cout << "Key:'index' 'label' 'value'." << endl;
			cout << "For illustration, 'value' shown is the impedence. For ideal components, the impedence (frequency dependent) has been shown with angular freq. = 1." << endl;
			for (unsigned int i = 0; i < myCmpts.size(); i++){
				cout.precision(5);
				cout << i << " " << myCmpts[i]->label() << " " << myCmpts[i]->getImpedence() << endl;
			}
			cout << endl;

		}
		else if (ans == "2"){

			int num;
			while (1)
			{
				cout << "How many parallel series do you want in this set? (min 2) ";
				cin >> num;
				if (cin.fail() || num <= 1){
					cout << "That input was invalid." << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else{
					cin.ignore(1000, '\n'); //the \n (and any other characters after 1st whitespace) remains in the buffer after 1 extraction.
					break;
				}
			}
		
			myPSets.resize(myPSets.size() + 1);
			myPSets[myPSets.size() - 1] = new parallelSet;
			myPSets[myPSets.size() - 1]->setIndex(myPSets.size() - 1);

			cout << "Add a component with input: 'label' value (another value if non-ideal component)." << endl << "'label' is R = resistor, C = capacitor, L = inductor" << endl << "One value corresponds to relevant quantity e.g. resistance for R. Two values corresponds to real and im parts of impedence. Input 'x' to exit." << endl;
			cout << "SI units are used: R [Ohms], C [Farads], L [Henrys], impedence Z [Ohms]" << endl;
			for (int i = 0; i < num; i++){
				vector <component*> series;

				while (1){
					cout << "> ";
					string* input = new string[3];
					string lineIn;
					getline(cin, lineIn);
					stringstream ss(lineIn);
					try{
						bool badInput;
						ss >> input[0] >> input[1] >> input[2]; // label, value, (another value if user wanted non-ideal component)

						if (ss.rdbuf()->in_avail() != 0 || input[0].size() == 0){ badInput = true; throw badInput; } //checks the number of input arguements was ok.
						if (input[0] == "x"){
							if (!isThisNum(input[1]) && input[1].size() != 0){ throw input[1]; }
						}
						else{
							if (!isThisNum(input[1])){ throw input[1]; }
							else if (stod(input[1]) < 0){ throw input[1]; }
							//If got here, then input[1] is a positive number.
							try{
								if (!isThisNum(input[2]) && input[2].size() != 0){ throw input[2]; }
							}
							catch (const string & e){ cout << "arguement 2'" << e << "' not valid input." << endl; continue; }
						}
					}
					catch (const bool & e){ cout << "badInput == " << e << ". The number of input arguements was not valid." << endl; continue; }
					catch (const string & e){ cout << "arguement 1'" << e << "' not valid input." << endl; continue; }

					if (input[0] == "x"){
						cout << "Finished a series." << endl;
						break;
					}
					else if (input[0] == "R"){
						series.resize(series.size() + 1); //make a new pointer in the vector.
						if (input[2].size() == 0){ series[series.size() - 1] = new resistor(stod(input[1]));}
						else{ series[series.size() - 1] = new resistor(stod(input[1]), stod(input[2]));}
					}
					else if (input[0] == "C"){
						series.resize(series.size() + 1);
						if (input[2].size() == 0){ series[series.size() - 1] = new capacitor(stod(input[1])); }
						else{ series[series.size() - 1] = new capacitor(stod(input[1]), stod(input[2])); }
					}
					else if (input[0] == "L"){
						series.resize(series.size() + 1);
						if (input[2].size() == 0){ series[series.size() - 1] = new inductor(stod(input[1])); }
						else{ series[series.size() - 1] = new inductor(stod(input[1]), stod(input[2])); }
					}
					else{
						cout << "Sorry, I didn't understand that component input." << endl;
					}
					delete[] input;
				}
				myPSets[myPSets.size() - 1]->addSeries(series);
			}
			cout << endl;
			cout << "For illustration, value shown for in each component is impedence. For ideal components, the impedence (frequency dependent) has been shown with angular freq. = 1." << endl;
			cout << *(myPSets[myPSets.size() - 1]) << endl << endl;

		}
		else if (ans == "3"){
			
			double frequency;
			while (1){
				cout << "Frequency of the circuit: ";
				cin >> frequency;
				if (cin.fail() || frequency < 0){
					cout << "That input was invalid." << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else{
					cin.ignore(1000, '\n'); //the \n (and any other characters after 1st whitespace) remains in the buffer after 1 extraction.
					break;
				}
			}
			myCircuits.resize(myCircuits.size() + 1);
			myCircuits[myCircuits.size() - 1] = new circuit(frequency);

			cout << "Now add components to circuit from library using index (min. 0). Note: components will be added in series. The components may be R, C, L, or parallel sets. Add a parallel set by typing 'P index'. Input 'x' to finish." << endl;
			while (1){
				cout << "'index' : ";
				string lineinput, paraCheck, val;
				getline(cin, lineinput);
				stringstream ss(lineinput);
				ss >> paraCheck >> val;
				if (lineinput == "x"){
					cout << "Finished making a circuit." << endl << endl;
					break;
				}
				else if (isThisNum(lineinput) == 1 && stod(lineinput) >= 0 ){
					if (stod(lineinput) >= myCmpts.size()){ cout << "index out of cmpt library range" << endl; continue; }
					myCircuits[myCircuits.size() - 1]->addComponent(myCmpts[abs(stoi(lineinput))]);
				}
				else if (paraCheck == "P" && isThisNum(val) == 1 || stod(val) >= 0){
					if (stod(val) >= myPSets.size()){ cout << "index out of Pset library range" << endl; continue; }
					myCircuits[myCircuits.size() - 1]->addComponent(myPSets[abs(stoi(val))]);
				}
				else{
					cout << "Input invalid." << endl;
				}

			}
			cout << "Circuit label: " << myCircuits.size() - 1 << endl;
			cout << *(myCircuits[myCircuits.size() - 1]) << endl << endl;
		}
		else if (ans == "4"){
			cout << "Exiting..." << endl;
			break;
		}
		else{
			cout << "That input is invalid." << endl;
		}
	}
	
	cout << "Libraries have been saved in library.txt" << endl;

	libraryFile << "Number of non-ideal components used (static variable used) = " << getNI() << endl;

	libraryFile << "Component Library" << endl << "----------------------" << endl;
	libraryFile << "Your library has size = " << myCmpts.size() << endl << endl;
	libraryFile << "Key:'index' 'label' 'value'." << endl;
	libraryFile << "For illustration, 'value' shown is the impedence. For ideal components, the impedence (frequency dependent) has been shown with angular freq. = 1." << endl;
	for (unsigned int i = 0; i < myCmpts.size(); i++){
		libraryFile.precision(5);
		libraryFile << i << " " << myCmpts[i]->label() << " " << myCmpts[i]->getImpedence() << endl;
	}
	libraryFile << endl;

	libraryFile << "Parallel Sets" << endl << "----------------------" << endl;
	libraryFile << "For illustration, 'value' shown is the impedence. For ideal components, the impedence (frequency dependent) has been shown with angular freq. = 1." << endl;
	for (unsigned int i = 0; i < myPSets.size(); i++){
		libraryFile.precision(5);
		libraryFile << *myPSets[i] << endl;
	}

	libraryFile << "Circuits" << endl << "----------------------" << endl;
	for (unsigned int i = 0; i < myCircuits.size(); i++){
		libraryFile << "Circuit " << i << endl;
		libraryFile << "Freq = " << myCircuits[i]->getF() << endl;
		libraryFile << *myCircuits[i] << endl << endl;

	}

	//delete everything which used "new"!
	for (unsigned int i = 0; i < myCmpts.size(); i++){
		delete myCmpts[i];
	}
	for (unsigned int i = 0; i < myCircuits.size(); i++){
		delete myCircuits[i];
	}
	for (unsigned int i = 0; i < myPSets.size(); i++){
		delete myPSets[i];
	}

	return 0;
}