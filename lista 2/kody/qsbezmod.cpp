#include <iostream>
using namespace std ;

int porownania=0, przypisania=0;

void quicksort(long t[], int dol, int gora)
{
     porownania++;
     if(dol>=gora) return;

     int lewy, prawy, liczba;
     lewy=dol;
     prawy=gora;
     liczba = t[(lewy+prawy)/2]; //punkt odniesienia

     do
     {
           while (t[lewy]<liczba)
           {
               porownania++;
               lewy++; //szukamy od  lewej elementu wikeszego od punktu odniesienia
           }
           porownania++;

           while (t[prawy]>liczba)
           {
               porownania++;
                prawy--; //szukamy od prawej elementu mniejszego od punktu odniesienia
           }
           porownania++;

	   porownania++;
           if (lewy <= prawy)
           {
                swap(t[lewy], t[prawy]);
                przypisania+=3;
                lewy++;
                prawy--;
           } 

     } while (lewy <= prawy); //miniecie sie wskaznikow, wykonuje sie dopoki lewy jest mniejszy od prawy i jak lewy wiekszy to konczy petle
    porownania++;

     porownania++;
     if (dol<prawy)
     {
         quicksort(t,dol,prawy);
     } 

     porownania++;
     if (lewy<gora)
    {
        quicksort(t,lewy,gora);
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

