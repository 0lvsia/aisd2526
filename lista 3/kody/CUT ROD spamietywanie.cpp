#include <iostream>
#include <climits>

using namespace std;

MEMORIZED_CUT_ROD(int p[], int r[], int s[], int n)
{
    if (r[n]>=0) return r[n];

    int q;

    if(n==0)
    {
        q=0;
        s[0]=0;
    } else
    {
        q=INT_MIN;
        for(int i=1; i<=n; i++)
        {
            int current =p[i]+MEMORIZED_CUT_ROD(p, r, s, n-i);
            if(current >q )
            {
                q=current;
                s[n]=i; //zapamietuje optymalne ciecie
            }
        }
    }
    r[n]=q;
    return q;
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
        r[i]=INT_MIN;
        s[i]=0;
    }

    cout << MEMORIZED_CUT_ROD(p,r,s,n) << endl;
    PRINT_SOLUTION(s, n);


    return 0;
}
