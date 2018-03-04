#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

void wait (double);
void draw (int, int);
void redraw (int, int);

int main ()
{
	srand (time (NULL));
	ifstream input;
	system ("tput lines > lines.txt");
	input.open ("lines.txt");
	int lines;
	input >> lines;
	input.close ();
	
	system ("tput cols > cols.txt");
	input.open ("cols.txt");
	int cols;
	input >> cols;
	input.close ();

	int x = 0;
	draw (x, cols);

	while (true)
	{
		wait ((double) 1 / 12);
		x += 2 * (rand () % 2) - 1;
		redraw (x, cols);
	}
	return 0;
}

void wait (double sec)
{
	clock_t now = clock ();
	while (clock () - now < sec * CLOCKS_PER_SEC)
	{
	}
}

void draw (int x, int cols)
{
	for (int c = 1; c < cols / 2 + x; c++)
		cout << "▒";
	cout << "█";
	for (int c = cols / 2 + x + 2; c <= cols; c++)
		cout << "▒";
	cout << flush;
}

void redraw (int x, int cols)
{
	cout << "\r";
	for (int c = 1; c < cols / 2 + x; c++)
		cout << "▒";
	cout << "█";
	for (int c = cols / 2 + x + 2; c <= cols; c++)
		cout << "▒";
	cout << flush;
}