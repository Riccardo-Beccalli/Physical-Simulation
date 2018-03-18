#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iomanip>


using namespace std;

int bconverter (int in; int nb){
	int op, p = 1;
		while (input != 0){
			op += (in%nb)*p;
			in /= nb;
			p *= 10;
		}
	return op;
}

int random (int min, int max) {
	return min + rand () % (max - min);
}

int main () {
	system ("clear");
	sysstem ("date");
	srand (time (NULL));

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

	long int nl = 1;
	for (int i = 0; i< n; i++)
		nl *= n2;
	cout << "\n verranno generati " << nl << " libri" << endl;
	
	for (int i = 0; i < nl; i++)
		cout << setw (5) << i << setw (5) << bconverter(i,n2) << endl;

	/*ofstream fout;
	fout.open ("book.dat");

	for (int i= 0;i < n; i++){
		t = random (0,n2);
		fout << lettere [t];
	}

	fout.close ();
	system ("less book.dat");*/
	return 0;
}