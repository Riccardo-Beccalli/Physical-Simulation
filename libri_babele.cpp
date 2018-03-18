#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

int main () {
	ofstream fout;
	srand (time(NULL));
	system ("clear");
	fout.open ("libro.dat");
	int swap, t, caratteri;
	cout << "\nLibreria di babele, libro casuale con caratteri: c, i, a, o, e spazio.\n";
	cout << "Inserisci il numero di caratteri del tuo libro> "; cin >> t;
	cout << "\nQuanti caratteri vuoi nel tuo libro? "; cin >> caratteri;
	char car [caratteri];
	for (int i = 0; i < caratteri; i ++) {
		cout << "Inserisci il " << i + 1 << " carattere> "; cin >> car [i];
	}
	cout << endl;
	for (int i = 0; i < t; i ++) {
		swap = rand () % caratteri + 1;
		for (int j = 0; j < caratteri; j ++) {
			if (swap == j + 1) {
				cout << car [j];
				fout << car [j];
			}
		}
	}
	cout << endl;
	return 0;
}