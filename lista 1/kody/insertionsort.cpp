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

    for(int i=1; i<n; i++)
    {
          for (int j=i; j>0; j--)
          {
              porownania++;
              if (t[j]<t[j-1])
              {
                 int temp=t[j];
                 t[j]=t[j-1];
                 t[j-1]=temp;
                 przypisania+=3;
              } else break;
          }
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

    INSERTION(n, t);

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
