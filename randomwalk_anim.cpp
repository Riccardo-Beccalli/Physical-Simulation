/*
 *	randomwalk_anim
 */

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
	int LINES;
	input >> LINES;
	input.close ();
	
	system ("tput cols > cols.txt");
	input.open ("cols.txt");
	int COLS;
	input >> COLS;
	input.close ();

	//system ("clear");
	int x = 0;
	draw (x, COLS);

	while (true)
	{
		wait ((double) 1 / 12);
		x += 2 * (rand () % 2) - 1;
		redraw (x, COLS);
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

void draw (int x, int COLS)
{
	for (int c = 1; c < COLS / 2 + x; c++)
	{
		cout << "▒";
	}
	cout << "█";
	for (int c = COLS / 2 + x + 2; c <= COLS; c++)
	{
		cout << "▒";
	}
	cout << flush;
}

void redraw (int x, int COLS)
{
	cout << "\r";
	for (int c = 1; c < COLS / 2 + x; c++)
	{
		cout << "▒";
	}
	cout << "█";
	for (int c = COLS / 2 + x + 2; c <= COLS; c++)
	{
		cout << "▒";
	}
	cout << flush;
}