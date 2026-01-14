#include <iostream>
#include <limits> //dla INT_MIN zeby miec mozliwe najmniejsza zamiast jakichs -10000000

using namespace std;

int NAIVE_CUT_ROD(int p[], int n)
{
    if(n==0) return 0;

    int q = INT_MIN;

    for(int i=1; i<=n; i++)
    {
        q =max(q, p[i]+NAIVE_CUT_ROD(p, n-i));
    }
    return q;
}

int main()
{
    int n;
    cin >> n;

    int p[n+1];
    p[0]=0;

    // p=[]={2,2,7,6,5}

    for(int i=1; i<=n; i++)
    {
        cin >> p[i];
    }

    cout << NAIVE_CUT_ROD(p, n);


    return 0;
}
