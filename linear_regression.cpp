#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

double round (double, int);
int cifraSig (double);

int main (int argc, char* argv [])	//argv è un array dimensionato ad argc di puntatori sotto forma di stringhe
{
	if (argc != 3)			//se non ci sono tre elementi nell'array stoppa il programma
	{
		cout << "ATTENZIONE! La sintassi corretta è:\n     " << argv [0] /*argv [0] = ./nomeprogramma*/ << " file_di_dati numero_di_random_points" << endl;
		return -1; 		//stoppa il programma
	}

	ifstream fin;
	fin.open (argv [1]);

	if (!fin.is_open ())
	{
		cout << "ATTENZIONE! Il file " << argv [1] << " non esiste" << endl;
		return -2;
	}

	srand (time (NULL));		//inizializziamo il seme
	
	double x, y;			//valori che useremo in modo temporaneo

	vector <vector<double> > data;	//data e' un grande vettore con un numero di componenti pari al numero di dati, ciascuna componente con due celle.....data [i][0] e' la x di un certo dato, data [i][1] invece e' la y
	
	//vettore di input per le coordinate x e y del singolo dato
	vector<double> input;
	input.push_back (0);
	input.push_back (0);

	//lettura dei dati
	fin.open (argv [1]);
	while (!fin.eof ())	//qui dentro si passa da una variabile del file ad x ed y, poi al vettore di due celle input e solo infine il vettore input viene pushbackato in data; alla fine del file (fin.eof()) data avra' lo stesso numero di componenti a due celle dei dati nel file
	{
		fin >> x;
		input [0] = x;
		fin >> y;
		input [1] = y;
		data.push_back (input);
	}
	fin.close ();

	//determinazione dei limiti della finestra in cui cercare i parametri
	vector<double> A, B;
	double Btemp;
	for (int i = 0; i < data.size (); i++)
	{
		for (int j = 0; j < data.size (); j++)
		{
			if ((i != j) and (data [i] [0] != data [j] [0]))	//Questo if per evitare di dividere per zero
			{
				Btemp = (data [i] [1] - data [j] [1]) / (data [i] [0] - data [j] [0]);
				B.push_back (Btemp);	//in A e B ho tutti i valori di a e b di tutti i segmenti che collegano i punti
				A.push_back (data [j] [1] - Btemp * data [j] [0]);
			}

		}			
	}

	double Bavg = 0, Aavg = 0, Avar = 0, Bvar = 0;
	for (int i = 0; i < B.size (); i++)
	{
		Aavg += A [i];
		Bavg += B [i];
	}
	Aavg /= A.size ();
	Bavg /= B.size ();	//da riga 71 a 78 sommo tutti gli a e b dei vettori A e B e poi faccio la media

	for (int i = 0; i < B.size (); i++)
	{
		Avar += pow (A [i] - Aavg, 2);
		Bvar += pow (B [i] - Bavg, 2);
	}
	Avar = sqrt(Avar / A.size ());	//Calcolo l'errore su a e b di tutti i segmenti
	Bvar = sqrt(Bvar / B.size ());

	double AMIN, AMAX, BMIN, BMAX;
	AMIN = Aavg - 2 * Avar;	//Amin amax bmin bmax sono aavg (la media) più o meno l'erroe (avar)
	AMAX = Aavg + 2 * Avar;
	BMIN = Bavg - 2 * Bvar;
	BMAX = Bavg + 2 * Bvar;

	//esecuzione del fit
	double a, b, Delta, aBest, bBest, DeltaBest;	//a e b sono i parametri, delta è la funzione da minimizzare, aBest, bBest e DeltaBest sono i target a cui puntiamo, DeltaBest è il delta minore e aBest e bBest sono gli a e i b relativi al DeltaBest
	int N = atoi (argv [2]);	//N è il numero di numeri casuali da generare che l'utente aveva precedentemente messo
	//possiamo utilizzare una griglia molto fitta o sparare tanti numeri casuali
	ofstream fout;
	fout.open ("reg_3D.dat");
	for (int i = 0; i < N; i++)
	{
		a = AMIN + ((double) rand () / RAND_MAX) * (AMAX - AMIN);	//metodo di generazione casuale tra un numero massimo ed un numero minimo...esi sono proprio amin e amax
		b = BMIN + ((double) rand () / RAND_MAX) * (BMAX - BMIN);
		Delta = 0;

		for (int j = 0; j < data.size (); j++)	//Scorro tutti i dati di data 
		{
			Delta += pow (data [j] [1] - a - b * data [j] [0], 2);	//aggiungo a delta per poi dividere a riga 110
		}
		Delta /= (data.size () - 2); //trovo sul libro la stima di delta che qui faccio tra la riga 106 e 110

		if (i == 0)
		{
			aBest = a;
			bBest = b;
			DeltaBest = Delta;	//solo il primo ciclo faccio queste cose
		}
		else
		{
			if (Delta < DeltaBest)	//solo se delta è minore di deltabest lo sostituisco
			{
				aBest = a;
				bBest = b;
				DeltaBest = Delta;
			}
		}

		fout << a << setw (15) << b << setw (15) << Delta << endl;	//stampo ogni volta in reg_3d.dat a, b e delta appena calcolati
	}
	fout.close ();

	//Stima degli errori
	double aError, bError, Q, temp;		//q si chiama delta nel file del libro
	//calcolo di Q
	temp = 0;
	for (int i = 0; i < data.size (); i++)
	{
		temp += data [i] [0] * data [i] [0];
	}
	double temp2 = temp;
	Q = data.size () * temp;

	temp = 0;
	for (int i = 0; i < data.size (); i++)
	{
		temp += data [i] [0];
	}
	Q += - pow (temp, 2);

	//calcolo degli errori
	aError = sqrt (DeltaBest) * sqrt (temp2 / Q);		//trovo sul libro le stime degli errori che qui si calcolano
	bError = sqrt (DeltaBest) * sqrt (data.size () / Q);

	int aCifre = cifraSig (aError), bCifre = cifraSig (bError);		//arrotondare gli errori e a e b
	aError = round (aError, aCifre);
	bError = round (bError, bCifre);

	aBest = round (aBest, aCifre);
	bBest = round (bBest, bCifre);

	cout << "La nostra miglior stima della retta che meglio rappresenta i dati è: " << endl << "y = " << aBest << " + " << bBest << " * x" << endl;
	cout << "Sigma = " << sqrt (DeltaBest) << endl;
	cout << "aError = " << aError << endl;
	cout << "bError = " << bError << endl;

	fout.open ("data_reg.dat");
	for (int i = 0; i < data.size (); i++)
	{
		fout << data [i] [0] << setw (15) << data [i] [1] << setw (15) << aBest + bBest * data [i] [0] << endl;
	}
	fout.close ();
	
	return 0;
}

double round (double input, int cifre)
{
	input *= pow (10, cifre);
	if (!(input - int (input) < .5))
	{
		input += 1;
	}
	return (double) int (input) / pow (10, cifre);
}

int cifraSig (double input)
{
	int counter = 0;
	if (input < 1)
	{
		do
		{
			input *= 10;
			counter++;
		} while (input < 1);
	}
	else
	{
		do
		{
			input /= 10;
			counter--;
		} while (input > 1);
		counter++;
	}
	return counter;
}

//connetto tutti i punti con un segmento, ogni punto sarà collegato con tutti  gli altri. Avrò N * (N - 1) / 2 segmenti, del quale calcolo la inclinazione. Sommo tutte le inclinazioni e faccio la media.