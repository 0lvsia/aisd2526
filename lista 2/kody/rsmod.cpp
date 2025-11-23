#include <iostream>

using namespace std;

int porownania=0, przypisania=0;

// d to podstawa systemu liczbowego
// e to wykladnik okreslajacy ktora liczbe sortujemy
int* zliczanie(int t[], int n, int d, int e, bool ostatniacyfra)
{

    int zakres=d;
    if(ostatniacyfra)
    {
        zakres=2*d;
    }



    //tabela zliczajaca wystapienia danej liczby
    int* c = new int[d];
    for (int i=0; i<d; i++)
    {
        c[i]=0;
        przypisania++;
    }

    //zliczanie wystapien kazdej liczby
    for(int i=0; i<n; i++)
    {
        int cyfra = (t[i]/e)%d;

        //dla ostatniej cyfry przesuniecie dla liczb ujemnych
        if(ostatniacyfra && t[i]<0)
        {
            cyfra+=d;
        }


        c[cyfra]++; //to ziwkesza licznik danej cyfry
        przypisania++;
        porownania++;
    }

    //przeksztalca liczniki na pozycje koncowe
    for(int i=1; i<d; i++)
    {
        c[i]=c[i]+c[i-1];
        przypisania++;
        porownania++;
    }

    //tablica wynikowa
    int * b = new int[n];

    //iteracja od konca
    for(int i=n-1; i>=0; i--)
    {
        int cyfra = (t[i]/e)%d;

        //dla ostatniej cyfry przesuniecie dla liczb ujemnych
        if(ostatniacyfra && t[i]<0)
        {
            cyfra+=d;
        }

        b[c[cyfra]-1]=t[i]; // element na wlasciwej pozycji
        c[cyfra]--; //zmniejsza licznik dla danej cyfry
        przypisania+=2;
        porownania++;
    }

    delete[] c;
    return b;

}


void radix(int t[], int n, int d)
{
    //szuka maksymalnej i minimalnej wartosci tablicy
    int maks=t[0];
    int mins=t[0];
    for(int i=1; i<n; i++)
    {
        if(t[i]>maks)
        {
            maks=t[i];
            przypisania++;
        }
        if(t[i]<mins)
        {
            mins=t[i];
            przypisania++;
        }
        porownania+=2;
    }

    //jesli sa ujemne to dodatkowo przesuwa
    if(mins<0)
    {
        int przesuniecie = -mins;
        for(int i=0; i<n; i++)
        {
            t[i]+=przesuniecie;
            przypisania++;
        }
        maks+=przesuniecie;
    }


    //sortuje cyfra po cyfrze
    // e= 1, d, d^2, d^3 itp
    // dziala dopoki maks/e>0 czyli dopoki cyfry sa jeszcze do srotowania
    for(int e=1; maks/e>0; e=e*d)
    {
        bool ostatniacyfra = (maks/(e*d)==0);

        //sortowanie wzgledem aktualnej cyfry
        int * posortowana = zliczanie(t, n, d, e, ostatniacyfra);

        //kopiuje wynik do oryginalnej tablicy
        for(int i=0; i<n; i++)
        {
            t[i]=posortowana[i];
            przypisania++;
            porownania++;
        }

        delete[] posortowana;
    }

    //cofa przesuniecie jesli byly ujemne
    if(mins<0)
    {
        int przesuniecie = -mins;
        for(int i=0; i<n; i++)
        {
            t[i]-=przesuniecie;
            przypisania++;
        }
    }


}


int main()
{
    int n;
    cout << "ile elementow " << endl;
    cin >> n;

    int d;
    cout << "podstawa " << endl;
    cin >> d;


    int* t = new int[n];

    for(int i=0; i<n; i++)
    {
            cin >> t[i];
    }


    radix(t, n, d);

    for(int i = 0; i<n; i++)
	cout << t[i] << " ";
	cout << endl;

	cout << porownania << endl;
	cout << przypisania << endl;



    delete[] t;
    return 0;
}
