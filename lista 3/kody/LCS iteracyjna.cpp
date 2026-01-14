#include <iostream>

using namespace std;

int LCS (string X, string Y, int** c, char** b)
{
    int m=X.length();
    int n=Y.length();

    //zerowanie c; lcs zp ustym ciagiem = 0
    for(int i=1; i<=m; i++)
    {
        c[i][0]=0;
    }

    for(int j=1; j<=n; j++)
    {
        c[0][j]=0;
    }

    c[0][0]=0;

    for(int i=1; i<=m; i++)
    {
        for (int j=1; j<=n; j++)
        {
            //znaki sie zgadzaja
            if(X[i-1]==Y[j-1])
            {
                //dlugosc lcs rosnie o 1
                c[i][j] = c[i-1][j-1]+1;
                b[i][j] = '\\';
            } else
            //znaki sie roznia
            if(c[i-1][j]>= c[i][j-1])
            {
                //wieksza wartosc jest z gory
                c[i][j]=c[i-1][j];
                b[i][j] = '^';
            } else
            {
                //wieksza wartosc jest z lewo
                c[i][j] = c[i][j-1];
                b[i][j] = '<';
            }
        }
    }

    return c[m][n];
}

void PRINT_SOLUTION(char** b, string X, int i, int j)
{
    if(i > 0 && j > 0)
    {
        if(b[i][j] == '\\')
        {
            PRINT_SOLUTION(b, X, i-1, j-1);
            cout << X[i-1];
        }
        else
        if(b[i][j] == '^')
        {
            PRINT_SOLUTION(b, X, i-1, j);
        }
        else
        {
            PRINT_SOLUTION(b, X, i, j-1);
        }
    }
}


int main()
{
    string X, Y;

    cin >> X >> Y;

    int m=X.length();
    int n=Y.length();

    //dynamiczne tablicy c i b
    // c przechowuje dlugosci najdluzszego wspolnego podciagu
    // b przechowuje kierunki
    int** c = new int*[m+1];
    char** b = new char*[m+1];

    for(int i=0; i<=m; i++)
    {
        c[i]=new int[n+1];
        b[i]=new char[n+1];
    }

    cout << LCS(X,Y,c,b) << endl;
    PRINT_SOLUTION(b, X,m,n);

    //zwalnia pamiec
    for(int i = 0; i <= m; i++)
    {
        delete[] c[i];
        delete[] b[i];
    }
    delete[] c;
    delete[] b;

    return 0;
}
