#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long int porownania=0;
long long int przypisania=0;


void MERGE(int t[], int p, int s, int s2, int k)
{
    int n1=s-p+1; //dlugosc lewej czesci
    int n2=s2-s;   //dlugosc srodkowej czesci
    int n3=k-s2; //dlugosc prawej czesci

    // int L[n1+1], S[n2+1], R[n3+1]; to dla tablic o elementach do 1mln

    // to dynamiczna alokacja dla tablic 1mln powyzej
    int* L = new int[n1+1];
    int* S = new int[n2+1];
    int* R = new int[n3+1];

    L[n1]=9999999;
    S[n2]=9999999;
    R[n3]=9999999;
    przypisania+=3;

    //kopiowanie danych z lewej czesci t[p...s] do L
    for(int i=0; i<n1; i++)
    {
        L[i]=t[p+i];
        przypisania+=1;
    }

    //kopiowanie danych z srodkowej czesci do t2[s+1....s2] do S
    for(int j=0; j<n2; j++)
    {
        S[j]=t[s+1+j];
        przypisania+=1;
    }

    //kopiowanie danych z prawej czesci do t2[s2+1....k] do R
    for(int g=0; g<n3; g++)
    {
        R[g]=t[s2+1+g];
        przypisania+=1;
    }

    int i=0, j=0, g=0;

    //scala trzy tablice
    for(int l=p; l<=k; l++)
    {
        porownania+=3;
        if(L[i]<=S[j] && L[i]<=R[g])
        {
            t[l]=L[i];
            i=i+1;
        }else if(S[j]<=L[i] && S[j]<=R[g])
        {
                t[l]=S[j];
                j=j+1;
        }else
        {
            t[l]=R[g];
            g++;
        }
        przypisania+=1;

    }

    //zwalnia pamiec
    delete[] L;
    delete[] S;
    delete[] R;
}


void MERGESORT(int t[], int p, int k)
{
    int s=0, s2=0, trzy=0;
    if(p<k)
    {
        trzy=(k-p+1)/3;
        s=p+trzy-1;
        s2=s+trzy;

        //zabezpieczenia przed ujemnymi indeksami dla wtedy gyd malo elementow tablicy
        if (s < p) s = p;
        if (s2 <= s) s2 = s + 1;
        if (s2 > k) s2 = k;

        MERGESORT(t, p, s);
        MERGESORT(t, s+1, s2);
        MERGESORT(t, s2+1, k);

        MERGE(t, p, s, s2, k);
    }

}

// wielkoœæ tablicy i incjalizowanie jej dla tablic 10k+ elementów
/*
const int n = 1000000;
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
        t[i] = std::rand() % 1000000;
    }
    */


    auto start = high_resolution_clock::now(); //start liczenia czasu

    MERGESORT(t, 0, n-1);

    auto end = high_resolution_clock::now(); //koniec liczenia czasu
    auto czas = duration_cast<microseconds>(end - start);

     //kod uzywany do zapisania wynikow dzialania alogrytmu do pliku
    fstream plik1;
    plik1.open("wyniki.txt",ios::out | ios::app);
    plik1 << czas.count() << " " << endl;
    plik1 << porownania << endl;
    plik1 << przypisania << endl;
    plik1.close();

    //wypisywanie porownan i przypisan, latwiej zauwazyc czy program dziala prawidlowo
    cout << porownania << endl;
    cout << przypisania << endl;




    return 0;
}
