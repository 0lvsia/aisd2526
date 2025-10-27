#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long int porownania=0;
long long int przypisania=0;

void INSERTION(int n, int t[])
{

    for(int i=0; i<n-1; i=i+2)
    {

        //sortowanie pary
    porownania++;
    if(t[i]>t[i+1])
    {
        swap(t[i], t[i+1]);
        przypisania+=3;
    }

        //para w dobre miejsce
    int a=t[i], b=t[i+1];
    przypisania+=2;
    int j=i-1;

    while(j>=0)
    {
        porownania++;
        if(t[j]>b)
        {
        t[j+2]=t[j];
        przypisania++;
        j--;
        } else break;
    }
    t[j+2]=b;
    przypisania++;

    while(j>=0)
    {
        porownania++;
        if(t[j]>a)
        {
        t[j+1]=t[j];
        przypisania++;
        j--;
        } else break;
    }
    t[j+1]=a;
    przypisania++;

    }

        //jezeli tablica nieparzysta
    if(n%2==1)
    {
        int ostatni=t[n-1];
        przypisania++;
        int j=n-2;
        while(j>=0)
        {
            porownania++;
            if(t[j]>ostatni)
            {
            t[j+1]=t[j];
            przypisania++;
            j--;
            } else break;
        }
        t[j+1]=ostatni;
        przypisania++;
    }
}

// wielkoœæ tablicy i incjalizowanie jej dla tablic 10k+
/*
const int n = 5000000;
int t[n];
*/

int main()
{

    //kod uzywany do wpisywania recznie elemntow tablicy o malych rozmiarach
    /*
    int n=0;
    cin >> n;
    int t[n];

    for(int i=0; i<n; i++)
    {

        cin >> t[i];
    }
    */

    //kod uzywany do wpisywania elementow tablicy o wiekszych rozmiarach niz 10k+
    /*
    std::srand(std::time(nullptr));
    for(int i = 0; i < n; i++)
    {
        t[i] = std::rand() % 500000;
    }
    */

    auto start = high_resolution_clock::now(); //start liczenia czasu

    INSERTION(n, t);

    auto end = high_resolution_clock::now();//koniec liczenia czasu
    auto czas = duration_cast<microseconds>(end - start);


    //kod uzywany do wyswietlania tablicy i wynikow
    /*
    cout << "posortowana tablica " <<endl;
    for(int i=0; i<n; i++)
    {
        cout << t[i] << " ";
    }
    cout << "porownania " << porownania << endl;
    cout << "przypisania " << przypisania << endl;
    */

    //kod uzywany do zapisania wynikow z tablic duzych do pliku
    fstream plik1;
    plik1.open("wyniki.txt",ios::out | ios::app);
    plik1 << czas.count() << " " << endl;
    plik1 << porownania << endl;
    plik1 << przypisania << endl;
    plik1.close();

    return 0;
}

