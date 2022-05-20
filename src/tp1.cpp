#include <iostream>

using namespace std;

void Pivoteia(float *tableau[], int n, int m, int linha, int coluna)
{

    for (int i = 0; i < n; i++)
    {
        
    }
}

float *SimplexAuxiliar(float *tableau[], int n, int m)
{
    float **auxiliar = new float *[n];
    for (int i = 0; i < n; i++)
        auxiliar[i] = new float[m + n - 1];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + m - 1; j++)
        {
            auxiliar[i][j] = 0;
        }
    }

    for (int j = m - 1; j < m - 2 + n; j++)
        auxiliar[0][j] = 1;

    for (int i = 1; i < n; i++)
    {
        auxiliar[i][m - 2 + i] = 1;
        for (int j = 0; j < m - 1; j++)
        {
            auxiliar[i][j] = tableau[i][j];
        }
        auxiliar[i][m - 2 + n] = tableau[i][m - 1];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + m - 1; j++)
        {
            cout << auxiliar[i][j] << "   ";
        }
        cout << endl;
    }

    for (int i = 1; i < n; i++)
    {
        cout << "pivoteando " << auxiliar[i][m - 2 + i] << endl;
        Pivoteia(auxiliar, n, m + n - 1, i, m - 2 + i);
    }
}

void Simplex(float *tableau[], int *baseViavel, int n, int m)
{
    SimplexAuxiliar(tableau, n, m);
}

int main()
{
    int n = 0;
    int m = 0;
    cin >> n;
    cin >> m;

    float **tableau = new float *[n + 1];
    for (int i = 0; i < n + 1; i++)
        tableau[i] = new float[n + m + 1];

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + m + 1; j++)
        {
            tableau[i][j] = 0;
        }
    }

    for (int i = 0; i < n + 1; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> tableau[i][j + n];
                tableau[i][j + n] = -tableau[i][j + n];
            }
        }
        else
        {
            for (int j = 0; j < m + 1; j++)
            {
                cin >> tableau[i][j + n];
                tableau[i][i - 1] = 1;
            }
        }
    }

    /*for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + m + 1; j++)
        {
            cout << tableau[i][j] << "   ";
        }
        cout << endl;
    }*/

    int *baseViavel = new int[n + m + 1];
    for (int i = 0; i < n + m + 1; i++)
    {
        baseViavel[i] = -1;
    }

    Simplex(tableau, baseViavel, n + 1, n + m + 1);
}