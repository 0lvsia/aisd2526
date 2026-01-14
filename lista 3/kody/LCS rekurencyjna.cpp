#include <iostream>

using namespace std;

int LCS_RECURSIVE (string X, string Y, int** c, char** b, int i, int j)
{
    //warunek bazowy pusty ciag
    if(i==0 || j==0) return 0;

    //spamietywanie, jesli juz obliczone to zwraca wynik
    if(c[i][j]!=-1)
    {
        return c[i][j];
    }

    int result;

    if (X[i-1] == Y[j-1])
    {
        result = LCS_RECURSIVE(X, Y, c, b, i-1, j-1) + 1;
        b[i][j] = '\\';
    }
    else
    {
        // oblciza dwie mozliwosci
        int up = LCS_RECURSIVE(X, Y, c, b, i-1, j);
        int left = LCS_RECURSIVE(X, Y, c, b, i, j-1);

        // wybiera lepsza
        if (up >= left)
        {
            result = up;
            b[i][j] = '^';
        } else
        {
            result = left;
            b[i][j] = '<';
        }
    }

    //pamietanie wyniku
    c[i][j] = result;
    return result;

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

    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
        {
            c[i][j]=-1;
        }
    }

    for(int i=0; i<=m; i++)
    {
        c[i][0]=0;
    }
    for(int j=0; j<=n; j++)
    {
        c[0][j]=0;
    }

    cout << LCS_RECURSIVE(X,Y,c,b, m, n) << endl;
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
