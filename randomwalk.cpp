//random walk
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main () {
	system ("clear");
	system ("date");
	srand (time(NULL));
	int n, a, b;
	cout << "\t\"RaNdOm WaLk\"" << endl;
	cout << "Inserisci il numero di passi\n> ";
	cin >> n;
	ofstream fout;
	fout.open ("rand_walk.dat");
	a = 0;
	for (int i = 0; i < n; i ++) {
		b = rand () % 2;
		if (b)
			a ++;
		else 
			a --;
		fout << i << setw (25) << a << endl;
	}
	fout.close ();
	return 0;
}