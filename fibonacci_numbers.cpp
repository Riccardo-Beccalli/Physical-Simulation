#include <iostream>
#include <iomanip>
#include "my_library.cpp"
using namespace std;
# define L 5

int main() {
	int a, swap1 = 0, swap2 = 1, i = 1, b = 1;
	cout << "I numeri di Fibonacci cosa hanno di speciale, inserisci il massimo> "; cin >> a;
	do{
		cout << i << setw (L) << b << "^" << setw (L) << float (i / swap2)<< setw (L);
		if (isprime(i))
		 	cout << "primo";
		cout << endl;
		b ++;
		swap2 = i; 
		i += swap1;
		swap1 = i;
	} while( i <= a);
	return 0;
}
