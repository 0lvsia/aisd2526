#include <iostream>

using namespace std;

int PD_ACTIVITY_SELECTOR(int s[], int f[], int n)
{
    //dp-przechowuje rozwiazania podproblemow
    int dp[n];
    dp[0]=1; //pierwsze zjaecie zawsze wybieramy

    //od najmniejszych do najwiekszych problemow

    for(int i=1; i<n; i++)
    {
        int nie=-1;

        //szuka od konca bo f posortwane
        for(int j=i-1; j>=0; j--)
        {
            if(f[j]<= s[i])
            {
                nie=j;
                break;
            }
        }


    //wlaczanie biezacego zajecia
    int wybieram=1;
    if(nie!=-1)
    {
        wybieram+=dp[nie];
    }

    //nie wlaczanie biezacego zajecia
    int niewybieram=dp[i-1];

    //wybiera i zpamaietuje lepsza opcje
    if(wybieram>niewybieram)
    {
        dp[i]=wybieram;
    } else
    {
        dp[i]=niewybieram;
    }

    }
    return dp[n-1];
}


int main()
{
    int n; //liczba dostepnych zajec
    cin >> n;

    int s[n]; //poczatek zajec
    int f[n]; //koniec zajec

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

    cout << PD_ACTIVITY_SELECTOR(s, f, n) << endl;

    return 0;
}
