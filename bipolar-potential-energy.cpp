#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

int main () {
	int n;
	double r1, r2, a, u, xmax, ymax;

	srand (time (NULL));

	cout << "Inserisci il numero di punti per lato della griglia\n> ";
	cin >> n;
	cout << "Inserisci la x massima\n> ";
	cin >> xmax;
	cout << "Inserisci la y massima\n> ";
	cin >> ymax;
	cout << "Inserisci la distanza delle cariche\n> ";
	cin >> a;

	ofstream fout;
	fout.open ("en-pot-bip.dat");

	for (double x = -xmax; x <= xmax; x += xmax / n)
	{
		for (double y = -ymax; y <= ymax; y += ymax / n)
		{

			r1 = sqrt (pow (y, 2) + pow (- a - x, 2));
			r2 = sqrt (pow (y, 2) + pow (a - x, 2));

			u = 1 / r1 + 1 / r2;

			u *= 1000;

			fout << x << setw (20) << y << setw (20) << u << endl;
		}
		fout << endl;
	}

	fout.close ();

	return 0;
}