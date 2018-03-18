#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int random (int min, int max) {
	return min + rand () % (max - min);
}

int main () {
	system ("clear");
	int t, n, n2;
	cout << "Quanto lungo deve essere il libro?" << endl;
	cin >> n;
	cout << "Quante lettere possono comporlo?" << endl;
	cin >> n2;

	char lettere [n2];
	for (int i= 0;i < n2; i++){
		cout << i+1 << "° | ";
		cin >> lettere [i];
	}

	ofstream fout;
	fout.open ("book.dat");
	for (int i= 0;i < n; i++){
		t = random (0,n2);
		fout << lettere [t];
	}

	fout.close ();
	system ("less book.dat");
	return 0;
}