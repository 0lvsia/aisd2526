#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long int porownania=0;
long long int przypisania=0;

// laczy dwie posortowane czesci tablicy t[p...s] i s[s+1....k] w jedna calosc
void MERGE(int t[], int p, int s, int k)
{
    int n1=s-p+1; //dlugosc lewej czesci
    int n2=k-s;   //dlugosc prawej czesci
    int* L = new int[n1+1];
    int* R = new int[n2+1];
    L[n1]=9999999;
    R[n2]=9999999;
    przypisania+=2;

    //kopiowanie danych z lewej czesci t[p...s] do L
    for(int i=0; i<n1; i++)
    {
        L[i]=t[p+i];
        przypisania+=1;
    }

    //kopiowanie danych z prawej czesci t[s+1....k] do R
    for(int j=0; j<n2; j++)
    {
        R[j]=t[s+1+j];
        przypisania+=1;
    }

    int i=0, j=0;

    //przechodzi przez cala tablice; porownuje elementy L i R i ustawwia po kolei od mniejszego do duzego
    for(int l=p; l<=k; l++)
    {
        porownania+=1;
        if(L[i]<=R[j])
        {
            t[l]=L[i];
            i=i+1;
        }else
        {
            t[l]=R[j];
            j=j+1;
        }
        przypisania+=1;
    }

    delete[] L;
    delete[] R;
}


void MERGESORT(int t[], int p, int k)
{
    int s=0;
    if(p<k)
    {
        s=(p+k)/2; //srodek
        MERGESORT(t, p, s); //sortuje lewa czesc od p do s
        MERGESORT(t, s+1, k); //sortuje prawa czesc od s+1 do k
        MERGE(t, p, s, k); //laczy posortowane czesci
    }

}

const int n = 100000000;
int t[n]; //tu uzywane jezeli dla giga tbalic

int main()
{
    /*
    int n=0;
    cin >> n;
    int t[n];

    for(int i=0; i<n; i++)-
    {
        cin >> t[i];
    }
    */


   std::srand(std::time(nullptr));
    for(int i = 0; i < n; i++)
    {
        t[i] = std::rand() % 100000000;
    }


    auto start = high_resolution_clock::now();

    MERGESORT(t, 0, n-1);

    auto end = high_resolution_clock::now();
    auto czas = duration_cast<microseconds>(end - start);

    fstream plik1;
    plik1.open("wyniki.txt",ios::out | ios::app);
    plik1 << czas.count() << " " << endl;
    plik1 << porownania << endl;
    plik1 << przypisania << endl;
    plik1.close();


    cout << "porownania " << porownania << endl;
    cout << "przypisania " << przypisania << endl;



    return 0;
}
