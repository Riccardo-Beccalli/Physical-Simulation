//50 %
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

int evo (int);

int main ()
{
	srand (time (NULL));
	int T, W;
	double average;

	cout << "Inserisci il tampo di Simulazione T> ";
	cin >> T;

	cout << endl;

	cout << "Inserisci il numero di camminatori W> ";
	cin >> W;

	vector<int> x;
	for (int i = 0; i < W; i++)
	{
		x.push_back (0);
	}

	ofstream fout;
	fout.open ("rndwlk.dat");

	fout << 0;
	average = 0;
	for (int w = 0; w < W; w++)
	{
    		average += x[w];
		fout << "	" << x [w];
	}
	average /= W;
	fout << "	" << average << endl;

	for (int t = 1; t <= T; t++)
	{
		fout << t;
		average = 0;
    	for (int w = 0; w < W; w++)
    	{
			x [w] = evo (x [w]);
			average += x [w];
			fout << "	" << x [w];
		}
		average /= W;
		fout << "	" << average << endl;
	}

	fout.close ();

	fout.open ("plot.plt");
	fout << "p ";
	for (int i = 2; i <= W + 2; i++)
	{
		fout << "\'rndwlk.dat\' u 1:" << i << " ";
		if (i < W + 2)
			fout << "w d notitle, ";
		else
			fout << "w l notitle";
	}
	fout.close ();

	return 0;
}

int evo (int x)
{
	x += 2 * (rand () % 2) - 1;
	return x;
}