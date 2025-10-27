#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long int porownania=0;
long long int przypisania=0;

long long int heap_size=0; //rozmiar kopca
long long int n=0;

//indeks lewego dziecka w kopcu
int LEFT(int i)
{
    return 2*i+1;
}
//indeks prawego dziecka w kopcu
int RIGHT(int i)
{
    return 2*i+2;
}

//ogarnia wlasnosc kopca w dol od wezla i
//dla kopca maksymanego gdzie rodzic jest wiekszy lub rowny dzieciom
void HEAPIFY(int t[], int i)
{
    int l=LEFT(i); //lewe dziecko
    int r=RIGHT(i); //prawe dziecko
    int largest=i; //najwiekszy element

    //sprawdzanie czy lewe dziecko jest wieksze od rodzica
     porownania++;
    if(l<heap_size)
    {
        porownania++;
        if(t[l]>t[i])
        {
            largest=l; //ze lewe wieksze
        }

    }else
    {
        largest=i; //ze rodzic wiekszy
    }

    //sprawdzanie czy prawe dziecko jest wieksze od rodzica
     porownania++;
    if(r<heap_size)
    {
        porownania++;
        if(t[r]>t[largest])
        {
            largest=r;
        }

    }

    //jezeli rodzic nie jest najwiekszy zamienia go z najwiekszym dzieckiem
    porownania++;
    if(i!=largest)
    {
        swap(t[i], t[largest]);
        przypisania+=3;
        HEAPIFY(t, largest); //rekurencyjnie naprawia dalej w dol
    }
}

//buduje kopiec maksymalny z nieuporzadkowanej tablicy
void BUILD_HEAP(int t[])
{
    heap_size=n;
    for(int i=n/2-1; i>=0; i--)
    {
        HEAPIFY(t, i);
    }
}

//glowne sortowanie;
//buduje kopiec maksymalny, zamienia maksymalny element z ostatnim w kopcu
// zmniejsza rozmiar kopca, przywraca wlasnosci kopca dla korzenia
void HEAP_SORT(int t[])
{
    BUILD_HEAP(t); //kopiec maksymalny
    for(int i=n-1; i>=1; i--)
    {
        swap(t[0], t[i-1]);
        przypisania+=3;
        heap_size=heap_size-1;
        HEAPIFY(t, 0);
    }
}

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

    HEAP_SORT(t);

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

    delete[] t;
    return 0;
}

