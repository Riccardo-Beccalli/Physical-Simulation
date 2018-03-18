#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main () {
	srand (time (NULL));
	system ("clear");
	system ("date");
	int n, cicli, riempimento, a = 0, counter;
	cout << "Inserisci la grandezza\n> ";
	cin >> n;
	cout << "Inserisci il numero di cicli\n> ";
	cin >> cicli;
	cout << "Inserisci 1 se vuoi riempire la sequenza manualmente o 0 se random\n> ";
	cin >> riempimento;
	bool celle [n + 2][n + 2];
	if (riempimento == 0)
		for (int i = 0; i < n + 2; i ++)
			for (int y = 0; y < n + 2; y ++)
				celle [i][y] = rand () % 2;
	else
		for (int i = 0; i < n + 2; i ++)
			for (int y = 0; y < n + 2; y ++) {
				cout << i << ":" << y;
				cin >> celle [i][y];
			}
	for (int i = 0; i < n; i ++) {
		cout << endl;
		for (int y = 0; y < n; y ++) {
			if (celle [i][y] == 1)
				cout << "11";
				//cout << "██";
			else
				cout << "00";
				//cout << "▒▒";
		}
	}
	do {
		for (int i = 1; i <= n; i ++) {
			for (int y = 1; y <= n; y ++) {
				counter = 0;
				if (celle [i - 1][y - 1] == 1)
					counter ++;
				if (celle [i - 1][y] == 1)
					counter ++;
				if (celle [i - 1][y + 1] == 1)
					counter ++;
				if (celle [i][y - 1] == 1)
					counter ++;
				if (celle [i][y + 1] == 1)
					counter ++;
				if (celle [i + 1][y - 1] == 1)
					counter ++;
				if (celle [i + 1][y] == 1)
					counter ++;
				if (celle [i + 1][y + 1] == 1)
					counter ++;
				if (celle [i][i] == 0)
					if (counter == 3)
						celle [i][y] = 1;
				if (celle [i][i] == 1)
					if (counter < 2)
						celle [i][y] = 0;
					else if (counter >= 3)
						celle [i][y] = 0;
			}
		} 
		system ("clear");
		for (int i = 0; i < n; i ++) {
			cout << endl;
			for (int y = 0; y < n; y ++) {
				if (celle [i][y] == 1)
					cout << "11";
					//cout << "██";
				else
					cout << "00";
					//cout << "▒▒";
			}
		}
		a ++;
	} while (a < cicli);
	return 0;
}