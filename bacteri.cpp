#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

double evo (double x) {
	if (x < .25)
		return 3 * x;
	else if ((x >= .25) and (x < .75))
		return 1 - x;
	return 3 * x - 2;
}

int main () {
	srand (time(NULL));
	system ("clear");
	system ("date");
	double  x, x0;
	double n, np;
	cout << "inserici il periodo di simulazione [giorni]" << endl;
	cin >> n;
	cout << "inserisci il numero dei punti" << endl;
	cin >> np;
	ofstream fout;
	fout.open  ("bact_kx_1.dat");
	for (int i = 0 ; i < np; i++) {
		x0 = x;
		x = (double) rand()/RAND_MAX;
			for (int i = 0; i < n ; i++)
				x = evo (x);
		//fout << i << setw (20) << x << endl;	
		fout << x0 << setw (20) << x << endl;
	}
	fout.close ();
	return 0;
}