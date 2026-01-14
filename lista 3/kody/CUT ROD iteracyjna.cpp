#include <iostream>
#include <climits>

using namespace std;

int EXT_CUT_ROD(int p[], int r[], int s[], int n)
{
    r[0]=0;

    //dla kazdej dlugosci szuka maksymalny zysk
    for(int i=1; i<=n; i++)
    {
        int q=INT_MIN;

        //sprawdzanie mozliwych pierwszch ciec
        for(int j=1; j<=i; j++)
        {
            if(q<p[j] + r[i-j])
            {
                q=p[j]+r[i-j];
                s[i]=j;
            }
        }
        r[i]=q;
    }
    return r[n];
}

//odzyskiwanie i wypisywanie rozwiazania
void PRINT_SOLUTION(int s[], int n)
{
    while(n>0)
    {
        cout << s[n];
        n=n-s[n];
        if(n>0) cout << " + ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    //tablica ceny
    int p[n+1];
    p[0]=0;

    // p=[]={2,2,7,6,5}

    for(int i=1; i<=n; i++)
    {
        cin >> p[i];
    }

    //tablica ciecia
    int s[n+1];
    //tablica zyski
    int r[n+1];

    for(int i=0; i<=n; i++)
    {
        s[i]=0;
    }

    cout << EXT_CUT_ROD(p,r,s,n) << endl;
    PRINT_SOLUTION(s, n);


    return 0;
}
