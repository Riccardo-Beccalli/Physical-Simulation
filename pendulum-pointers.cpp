#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

#define W 20
#define G 9.81

void introduction ();
void evolution (double *x, double *v, double *data, ofstream *ptrfout);
void write (double *data, ofstream *ptrfout2);
void choice (double *data, double *v);

int main ()
{
	int scelta;

	int N = 50;

	double *x = (double *) calloc (N, sizeof (double));
	double *v = (double *) calloc (N, sizeof (double));
	v [0] = 5;

	double *data = (double *) calloc (7, sizeof (double));
	data [0] = 10;
	data [1] = 1;
	data [2] = .1;
	data [3] = 1;
	data [4] = 200;
	data [5] = .05;
	data [6] = N;

	/*double A = 10, L = 1;
	double K = .1, M = 1;
	double T = 200, Delta = .05;*/

	ofstream fout;
	fout.open ("data.dat");
	ofstream *ptrfout;
	ptrfout = &fout;

	ofstream fout2;
	fout2.open ("fare2.plt");
	ofstream *ptrfout2;
	ptrfout2 = &fout2;

	system ("clear");

error:
	introduction ();
	cin >> scelta;

	if (scelta == 0)
	{
		system ("clear");
		cout << "You chose the simulation with fixed parameters!" << endl;
		cout << "How many pendulums do you want in the simulation?"
		cout << "You will now be able to see the positions of the respective pendulums as function of the time!" << endl;
	}
	else if (scelta == 1)
	{
		system ("clear");
		choice (data, v);
	}
	else
	{
		system ("clear");
		cout << "!!!WARNING!!! Choice not contemplated, you have to choose [0] or [1]!" << endl;
		goto error;
	}

	evolution (x, v, data, ptrfout);
	write (data, ptrfout2);
	sleep (1);
	system ("gnuplot fare2.plt -p");

	fout.close ();
	fout2.close ();
	return 0;
}

void introduction ()
{
	cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
	cout << "║     Physics                                                   ║" << endl;
	cout << "╠═══════════════════════════════════════════════════════════════╣" << endl;
	cout << "║     Pendulums connected by a spring                           ║" << endl;
	cout << "╠═══════════════════════════════════════════════════════════════╣" << endl;
	cout << "║     Author: Riccardo Beccalli                                 ║" << endl;
	cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
	cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
	cout << "║     Choose the kind of simulation you want!                   ║" << endl;
	cout << "╠═══════════════════════════════════════════════════════════════╣" << endl;
	cout << "║     [0] = Simulation with fixed parameters                    ║" << endl;
	cout << "║     [1] = Simulation with user-selected parameters            ║" << endl;
	cout << "╚═══════════════════════════════════════════════════════════════╝" << endl << endl;
	cout << "\n> ";
}

void evolution (double *x, double *v, double *data, ofstream *ptrfout)
{
	double A = data [0], L = data [1];
	double K = data [2], M = data [3];
	double T = data [4], Delta = data [5], N = data [6];
	*ptrfout << setw (W) << 0;
	for (int i = 0; i < N; i ++)
		*ptrfout << setw (W) << x [i] + i * A << setw (W) << v [i];
	*ptrfout << endl;

	for (double t = Delta; t <= T; t += Delta)
	{
		for (int i = 0; i < N; i ++)
			if (i == 0)
				v [i] += (- (G/L) * x [i] - K/M * (x [i] - x [i + 1])) * Delta;
			else if (i == N - 1)
				v [i] += (- (G/L) * x [i] - K/M * (x [i] - x [i - 1])) * Delta;
			else
				v [i] += (- (G/L) * x [i] - K/M * (x [i] - x [i - 1]) - K/M * (x [i] - x [i + 1])) * Delta;
		for (int i = 0; i < N; i ++)
			x [i] += v [i] * Delta;

		*ptrfout << setw (W) << t;
		for (int i = 0; i < N; i ++)
			*ptrfout << setw (W) << x [i] + i * A << setw (W) << v [i];
		*ptrfout << endl;
	}
}

void write (double *data, ofstream *ptrfout2)
{
	*ptrfout2 << "p 'data.dat'";
	for (int i = 0; i < data [6]; i++)
		*ptrfout2 << (i == 0 ? "" : "''") << " u 1:" << 2 * (i + 1) << " w l title ''" << (i == data [6] - 1 ? "" : ",");
	*ptrfout2 << endl;
}

void choice (double *data, double *v)
{
	cout << "You have chosen the simulation with the parameters chosen by the user!" << endl;
	cout << "Enter the initial speed v [m/s] of the first pendulum\n> "; cin >> v [0];
	cout << "Enter simulation time T [s]\n> "; cin >> data [4];
	cout << "Enter the mass m [kg] of the pendulums\n> "; cin >> data [3];
	cout << "Enter the length l [m] of the wire\n> "; cin >> data [1];
	cout << "You will now be able to see the positions of the respective pendulums as function of the time!" << endl;
}
