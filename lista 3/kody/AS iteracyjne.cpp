#include <iostream>
#include <climits>

using namespace std;

//zwraca liczbe wybranych zajec
int ACTIVITY_SELECTOR(int s[], int f[], int n)
{
    //zaczynamy od 1 wiec nie potrzebujemy f[0]=int_min i s[0]=0
    int wynik = 1; //liczba wybranych zajec
    int k=1; //ostatnie wybrane zajecie

    for(int m=2; m<=n; m++)
    {
        if(s[m]>=f[k])
        {
            wynik++;
            k=m;
        }
    }
    return wynik;
}


int main()
{
    int n; //liczba dostepnych zajec
    cin >> n;

    int s[n+1]; //poczatek zajec
    int f[n+1]; //koniec zajec

    //podawanie startu i koniec danego zajêcia
    for(int i=1; i<=n; i++)
    {
        cin >> s[i] >> f[i];
    }

    //sortowanie po czasie zakoñczenia
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            if(f[j] < f[i])
            {
                swap(s[i], s[j]);
                swap(f[i], f[j]);
            }
        }
    }

    cout << ACTIVITY_SELECTOR(s, f, n) << endl;

    return 0;
}
