#include <iostream>
using namespace std ;

int porownania=0, przypisania=0;

void quicksort(long t[], int dol, int gora)
{
     if(dol>=gora) return;

     //spr czy pierwszy punkt odniesienia jest mniejszy od drugiego jak nei to zamienia
     porownania++;
     if(t[dol]>t[gora])
     {
         swap(t[dol], t[gora]);
         przypisania+=3;
     }

     long liczba1=t[dol]; //mniejszy punkt odniesienia pierwszy element
     long liczba2=t[gora]; //wiekszy punkt odniesienia ostatni element

     int lewy=dol+1; //wskaznik na poczatek po liczba1
     int prawy=gora-1; //wskaznik na koniec przed liczba2
     int i=lewy; //wskaznik aktualnie przetwarzany element

     //glowna petla dzielenia na 3 czesci
    while(i<=prawy)
    {
        porownania++;

        // tutaj ze element jest mniejszy od lewego liczba1
        porownania++;
        if(t[i]<liczba1)
        {
            swap(t[i], t[lewy]);
            przypisania +=3;
            lewy++;
        }
        else //tutaj ze elemetn wiekszy od prawego liczba 2
        {
            porownania++;
            if(t[i]>liczba2)
            {
                porownania++;
                while(t[prawy]>liczba2 && i<prawy)
                {
                    porownania++;
                    prawy--;
                }
                porownania++;

                swap (t[i], t[prawy]);
                przypisania+=3;
                prawy--;

                porownania++;
                if(t[i]<liczba1)
                {
                    swap(t[i], t[lewy]);
                    przypisania+=3;
                    lewy++;
                }
            }
            //jak jest miedzy liczba 1 liczba 2 to nic nie robimy z nim

        }
        i++;
        porownania++;
    }


    lewy--;
    prawy++;

    //tu daje punkty odniesienia na wlasciwe pozycje w srokdu tablicy
    swap(t[dol], t[lewy]); przypisania+=3;
    swap(t[gora], t[prawy]); przypisania+=3;

    //teraz tablica git posorotwane; lewa mniejsze od l1; srodek miedzy l1 i l2; prawa wieksze od l2

    //mniejsze od 1 punktu odniesienia
    porownania++;
    if(dol<lewy-1)
    {
        quicksort(t, dol, lewy-1);
    }

    // miedzy punktami odniesienia
    porownania++;
    if(lewy+1<prawy-1)
    {
        quicksort(t, lewy+1, prawy-1);
    }

    // wikesze od 2 punktu odniesienia
    porownania++;
    if(prawy+1<gora)
    {
        quicksort(t, prawy+1, gora);
    }


}

int main()
{
    int n;
    cin >> n;

    long t[n];

    for(int i=0; i<n; i++)
    {
            cin >> t[i];
    }

    quicksort(t,0,n-1);

    for(int i = 0; i<n; i++)
	cout << t[i] << " ";
	cout << endl;

	cout << porownania << endl;
	cout << przypisania << endl;




    return 0;
}

