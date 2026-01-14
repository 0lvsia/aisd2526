#include <iostream>
#include <climits>

using namespace std;

//zwraca liczbe wybranych zajec
int RECURSIVE_ACTIVITY_SELECTOR(int s[], int f[], int k, int n)
{
    int m=k+1;

    //szuka pierwszego zajecia ktore nie koliduje
    while(m<=n && s[m]<f[k])
    {
        m++;
    }

    //jesli znalezlismy zajecie
    if(m<=n)
    {
        return 1+ RECURSIVE_ACTIVITY_SELECTOR(s,f,m,n);
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
            if(f[j] < f[i])
            {
                swap(s[i], s[j]);
                swap(f[i], f[j]);
            }
        }
    }

    cout << RECURSIVE_ACTIVITY_SELECTOR(s, f, 0, n) << endl;

    return 0;
}
