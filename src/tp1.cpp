#include <iostream>
#include <iomanip>

using namespace std;

void ImprimeTableau(float *tableau[], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(6) << tableau[i][j] << "  ";
        }
        cout << endl;
    }
}

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

int EncontraMenorRazao(float *tableau[], int n, int m, int coluna)
{
    int indice_b = m - 1;
    float val_min = -1;
    int indice_min = -1;
    for (int i = 1; i < n; i++)
    {
        if(tableau[i][coluna]>0){
            if (val_min < 0 or tableau[i][indice_b]/tableau[i][coluna] < val_min){
                val_min = tableau[i][indice_b]/tableau[i][coluna];
                indice_min = i;
            }
        }
    }
    return indice_min;
}

void MontaAux(float *auxiliar[], float *tableau[], int n, int m)
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
        for (int j = 0; j < m - 1; j++)
        {
            auxiliar[i][j] = tableau[i][j];
        }
        auxiliar[i][m - 2 + n] = tableau[i][m - 1];
    }

    for (int i = 1; i < n; i++)
    {
        Pivoteia(auxiliar, n, m + n - 1, i, m - 2 + i);
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

void SimplexCanonica(float *tableau[], int n, int m)
{
    int indice_min;
    int i = 1;
    for (int j = n - 1; j < m - 2; j++)
    {
        if (tableau[0][j] < 0)
        {
            indice_min = EncontraMenorRazao(tableau, n, m, j);
            Pivoteia(tableau, n, m, EncontraMenorRazao(tableau, n, m, j), j);
            cout << "Pivoteamento " << i << endl;
            ImprimeTableau(tableau, n, m);
            j = n-1;
            i++;
        }
    }
}

void Simplex(float *tableau[], int n, int m)
{
    float **auxiliar = new float *[n];
    int n_auxiliar = n;
    int m_auxiliar = m + n - 1;
    cout << "tableau inicial: " << endl;
    ImprimeTableau(tableau, n, m);
    Positiva_B(tableau, n, m);
    cout << "tableau b positivo: " << endl;
    ImprimeTableau(tableau, n, m);
    cout << "auxiliar pivoteada: " << endl;
    MontaAux(auxiliar, tableau, n, m);
    ImprimeTableau(auxiliar, n_auxiliar, m_auxiliar);
    SimplexCanonica(auxiliar, n_auxiliar, m_auxiliar);
    if(auxiliar[0][m_auxiliar-1] < 0){
        cout << "inviavel" << endl;
        for (int i = 0; i<n-1; i++){
            cout << auxiliar[0][i] << " ";
        }
        cout << endl;
        return;
    }
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