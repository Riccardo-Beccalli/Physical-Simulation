#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

double intensity (double d, double D, double lambda, double y);
void introduction ();

int main (int argc, char** argv)
{
	double d, D, lambda, frequenza;
	double YMAX, DELTA;

	introduction ();

	cout << "Enter the the wavelength of light lambda\n> ";
	cin >> lambda;
	lambda *= pow (10, -9);
	cout << "Enter the slit separation d\n> ";
	cin >> d;
	d *= pow (10, -9);
	cout << "Enter the distance between the slit and screen D\n> ";
	cin >> D;
	D;
	cout << "Enter the size of the screen\n> ";
	cin >> YMAX;
	//cout << "DELTA\n> ";
	//cin >> DELTA;
	DELTA = 0.0001;

	double IMAX = intensity (d, D, lambda, 0);

	ofstream fout;
	fout.open ("interference.dat");
	for (double y = -YMAX; y < YMAX; y += DELTA)
	{
		fout << setw (25) << y << setw (25) << YMAX / 10 << setw (25) << intensity (d, D, lambda, y)/IMAX << endl;
		fout << setw (25) << y << setw (25) << -YMAX / 10 << setw (25) << intensity (d, D, lambda, y)/IMAX << endl;
		fout << endl;
	}	
	fout.close ();

	ofstream fout2;
	fout2.open ("make-interference.plt");
	fout2 << "set view map" << endl;
	fout2 << "set pm3d" << endl;
	fout2 << "sp 'interference.dat' u 1:2:3" << endl;
	fout2.close ();

	system ("gnuplot make-interference.plt -p");

	return 0;
}

void introduction ()
{
	cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
	cout << "║     Physics                                                   ║" << endl;
	cout << "╠═══════════════════════════════════════════════════════════════╣" << endl;
	cout << "║     Young's interference experiments                          ║" << endl;
	cout << "╠═══════════════════════════════════════════════════════════════╣" << endl;
	cout << "║     Author: Riccardo Emanuele Beccalli                        ║" << endl;
	cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
	cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
	cout << "║     Please insert the parameters                              ║" << endl;
	cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
}

double intensity (double d, double D, double lambda, double y)
{
	return pow (
		cos ((2 * M_PI * sqrt (pow (D, 2) + pow (y + d / 2, 2)) / lambda)) + cos ((2 * M_PI * sqrt (pow (D, 2) + pow (y - d / 2, 2)) / lambda)), 2) + pow (sin ((2 * M_PI * sqrt (pow (D, 2) + pow (y + d / 2, 2)) / lambda)) + sin ((2 * M_PI * sqrt (pow (D, 2) + pow (y - d / 2, 2)) / lambda)), 2);
}