#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;

int rule (int p, int ruleInt);
void intro ();
vector <bool> init_boolvector (int n);
void printcells (vector <bool>);
vector <bool> evo (vector<bool> cell, int ruleint);

int main () {
	srand (time (NULL));
	int n, T, input, ruleInt;
	intro ();
	cout << "Set the numbers of cells>";
	cin >> n;
	cout << "Set the total time of evolution> ";
	cin >> T;
	cout << "Set the rule [0...255]> ";
	cin >> ruleInt; 
	vector <bool> cell = init_boolvector (n);
	printcells (cell);
	cout << endl;
	for (int t = 1; t <= T; t++){
		cell = evo (cell, rule);
		printcells (cell);
		cout << endl;
	}
	return 0;
}
	



int rule (int p, int ruleInt){
	bool cifre [8]= {0, 0, 0, 0, 0, 0, 0, 0};
	int i = 0;

	while (ruleInt != 0){
		cifre [i] = ruleInt % 2;
		i++;
		ruleInt /= 2;
	}

	switch (p){
		case (0):
			return cifre [0];
		case (1):
			return cifre [1];
		case (2):
			return cifre [2];
		case (3):
			return cifre [3];
		case (4):
			return cifre [4];
		case (5):
			return cifre [5];
		case (6):
			return cifre [6];
		case (7):
			return cifre [7];
	}
	return -1;
}

void intro () {
	system ("clear");
	system ("date");
	cout << "Cellular Automata Simulator" << endl;
	cout << "Ver. 1.0" << endl;
	cout << "***************************" << endl;
}

vector <bool> init_boolvector (int n) {
	vector <bool> output;
	for (int i = 0; i < n; i ++) {
		output.push_back (rand () % 2);
	}
}

void printcells (vector <bool>) {
	for (int i = 0; i < cell.size (); i++){
		if (cell[i])
			cout << "██";
		else
			cout << "▒▒";
		}
}

vector <bool> evo (vector<bool> cell, int ruleint) {
	int n = cell.size ();
	for (int i = 0; i< n; i++){
		if (i == 0)
			input = cell [n - 1] * 4 + cell [i] * 2 + cell [i + 1];
		else if (i == n - 1)
			input = cell [i - 1] * 4 + cell [i] * 2 + cell [0];
		else
			input = cell [i - 1] * 4 + cell [i] * 2 + cell [i + 1];
		output.push_back (rule (input, ruleInt));		
	}
}
