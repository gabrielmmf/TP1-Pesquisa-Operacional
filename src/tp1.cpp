#include <iostream>

using namespace std;

void Pivoteia(float *tableau[], int n, int m, int linha, int coluna)
{
    float d = 0;

    if (tableau[linha][coluna] == 0)
        return;

    for (int i = 0; i < n; i++)
    {
        if (tableau[i][coluna] != 0)
        {
            d = tableau[i][coluna] / tableau[linha][coluna];
            if (i == linha)
            {
                d = 1 / tableau[linha][coluna];
                for (int j = 0; j < m; j++)
                {
                    tableau[i][j] = tableau[i][j] * d;
                }
            }
            else
            {
                for (int j = 0; j < m; j++)
                {
                    if (tableau[linha][j] != 0)
                        tableau[i][j] = tableau[i][j] - tableau[linha][j] * d;
                }
            }
        }
    }
}

void *MontaAuxiliar(float *auxiliar[], float *tableau[], int n, int m, int *bases)
{

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
        bases[i] = m - 2 + i;
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
        Pivoteia(auxiliar, n, m + n - 1, i, m - 2 + i);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + m - 1; j++)
        {
            cout << auxiliar[i][j] << "   ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Base[" << i << "] = " << bases[i] << endl;
    }
}

void Positiva_B(float *tableau[], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        if (tableau[i][m - 1] < 0)
        {
            for (int j = 0; j < m; j++)
            {
                if (tableau[i][j] != 0)
                    tableau[i][j] = -tableau[i][j];
            }
        }
    }
}

void SimplexCanonica(float *tableau[], int n, int m, int *bases, int indice_min)
{
    float razao_min = -1;
    int i_min = -1;

    if (tableau[1][m - 1] / tableau[1][indice_min] >= 0)
    {
        razao_min = tableau[1][m - 1] / tableau[1][indice_min];
        i_min = 1;
    }

    for (int i = 1; i < n; i++)
    {
        if (tableau[i][m - 1] / tableau[i][indice_min] < razao_min || (tableau[i][m - 1] / tableau[i][indice_min] > 0 && razao_min < 0))
        {
            i_min = i;
            razao_min = tableau[i][m - 1] / tableau[i][indice_min];
        }
    }
    if(razao_min >=0){
        Pivoteia(tableau, n, m, i_min, indice_min);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << tableau[i][j] << "   ";
        }
        cout << endl;
    }
}

void Simplex(float *tableau[], int n, int m)
{
    float **auxiliar = new float *[n];
    int *bases = new int[n];
    Positiva_B(tableau, n, m);
    MontaAuxiliar(auxiliar, tableau, n, m, bases);

    int indice_min = n - 1;
    float val_min = auxiliar[0][indice_min];
    do
    {
        for (int i = n; i < m - 1; i++)
        {
            if (auxiliar[0][i] < val_min)
            {
                indice_min = i;
                val_min = auxiliar[0][indice_min];
            }
        }
        SimplexCanonica(auxiliar, n, m + n - 1, bases, indice_min);
    } while (val_min < 0);
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

    Simplex(tableau, n + 1, n + m + 1);
}