#include <iostream>
#include <climits>

using namespace std;

//zwraca liczbe wybranych zajec
int MOD_ACTIVITY_SELECTOR(int s[], int f[], int k, int n)
{
    //szukamy zajecia ktore nie kczy to jeoliduje z ostatnim wybranym
    int indeks=-1;
    int czas = INT_MAX;

    for(int i=k+1; i<=n; i++)
    {
        //czy zajecie zaczyna sie po zakonczeniu ostatniego wybranego
        if(s[i]>=f[k])
        {
            //czy zajecie konczy sie wczesniej niz dotychczasowe wybrane
            if(f[i] < czas)
            {
                czas=f[i];
                indeks=i;
            }
        }
    }

    if(indeks!=-1)
    {
        return 1+MOD_ACTIVITY_SELECTOR(s,f,indeks,n);
    }

    return 0;

}


int main()
{
    int n; //liczba dostepnych zajec
    cin >> n;

    int s[n+1]; //poczatek zajec
    int f[n+1]; //koniec zajec

    f[0]=INT_MIN;
    s[0]=0;

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
            if(s[j] < s[i])
            {
                swap(s[i], s[j]);
                swap(f[i], f[j]);
            }
        }
    }

    cout << MOD_ACTIVITY_SELECTOR(s, f, 0, n) << endl;

    return 0;
}
