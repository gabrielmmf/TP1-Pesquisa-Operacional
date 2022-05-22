#include <iostream>
#include <iomanip>

using namespace std;

void ImprimeTableau(double *tableau[], int n, int m)
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

void Pivoteia(double *tableau[], int n, int m, int linha, int coluna)
{
    double d = 0;

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

int EncontraMenorRazao(double *tableau[], int n, int m, int coluna)
{
    int indice_b = m - 1;
    double val_min = -1;
    int indice_min = -1;
    for (int i = 1; i < n; i++)
    {
        if (tableau[i][coluna] > 0)
        {
            if (val_min < 0 or tableau[i][indice_b] / tableau[i][coluna] < val_min)
            {
                val_min = tableau[i][indice_b] / tableau[i][coluna];
                indice_min = i;
            }
        }
    }
    cout << "Menor razão encontrada: " << tableau[indice_min][indice_b] << "/" << tableau[indice_min][coluna] << endl;
    return indice_min;
}

void MontaAux(double *auxiliar[], double *tableau[], int n, int m)
{

    for (int i = 0; i < n; i++)
        auxiliar[i] = new double[m + n - 1];

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

void adicionaFolga(double *auxiliar[], double *tableau[], int n, int m)
{

    for (int i = 0; i < n; i++)
        auxiliar[i] = new double[m + n - 1];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + m - 1; j++)
        {
            auxiliar[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        auxiliar[i][m - 2 + i] = 1;
        for (int j = 0; j < m - 1; j++)
        {
            auxiliar[i][j] = tableau[i][j];
        }
        auxiliar[i][m - 2 + n] = tableau[i][m - 1];
    }
}

void Positiva_B(double *tableau[], int n, int m)
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

void CanonizaComAuxiliar(double *tableau[], double *auxiliar[], int n, int m)
{
    int pivoteamentos = 0;
    int pivot_i = -1;
    int pivot_j = -1;
    bool base = false;
    for (int j = n - 1; j < m - 1; j++)
    {
        base = false;
        cout << "Analisando coluna" << j << endl;
        for (int i = 0; i < n; i++)
        {
            if (auxiliar[i][j] == 1 || auxiliar[i][j] == 0)
            {
                if (auxiliar[i][j] == 1)
                {
                    base = true;
                    if (pivot_i != -1)
                        base = false;
                    pivot_i = i;
                    pivot_j = j;
                }
            }
            else
            {
                base = false;
            }
        }
        if (auxiliar[0][j] != 0)
            base = false;
        if (base and pivoteamentos < n-1)
        {
            cout << "Pivoteando " << tableau[pivot_i][pivot_j] << endl;
            Pivoteia(tableau, n, m, pivot_i, pivot_j);
            pivoteamentos++;
        }
        pivot_i = pivot_j = -1;
        base = false;
    }
}

void SimplexCanonica(double *tableau[], int n, int m)
{
    for (int j = n - 1; j < m - 1; j++)
    {
        if (tableau[0][j] < 0)
        {
            cout << "Pivoteando coluna" << j << endl;
            Pivoteia(tableau, n, m, EncontraMenorRazao(tableau, n, m, j), j);
            ImprimeTableau(tableau, n, m);
            j = n - 1;
        }
    }
}

void Simplex(double *tableau[], int n, int m)
{
    cout << "tableau inicial: " << endl;
    ImprimeTableau(tableau, n, m);

    double **tableauFolgas = new double *[n];
    adicionaFolga(tableauFolgas, tableau, n, m);
    int m_folga = m + n - 1;
    cout << "Tableau com folgas: " << endl;
    ImprimeTableau(tableauFolgas, n, m_folga);

    double **auxiliar = new double *[n];
    int n_auxiliar = n;
    int m_auxiliar = m_folga + n - 1;
    Positiva_B(tableauFolgas, n, m_folga);
    cout << "tableau b positivo:     " << endl;
    ImprimeTableau(tableauFolgas, n, m_folga);
    MontaAux(auxiliar, tableauFolgas, n, m_folga);
    cout << "auxiliar canonizada: " << endl;
    ImprimeTableau(auxiliar, n_auxiliar, m_auxiliar);

    cout << "Executando simplex auxiliar" << endl;
    SimplexCanonica(auxiliar, n_auxiliar, m_auxiliar);
    cout << "Auxiliar otimizada: " << endl;
    ImprimeTableau(auxiliar, n_auxiliar, m_auxiliar);
    cout << endl << endl;

    if (auxiliar[0][m_auxiliar - 1] < 0)
    {
        cout << "inviavel" << endl;
        for (int i = 0; i < n - 1; i++)
        {
            cout << auxiliar[0][i] << " ";
        }
        cout << endl;
        return;
    }
    else
    {
        cout << "Canonizada com auxiliar: " << endl;
        CanonizaComAuxiliar(tableauFolgas, auxiliar, n, m_folga);
        ImprimeTableau(tableauFolgas, n, m_folga);
    }
}

int main()
{
    int n = 0;
    int m = 0;
    cin >> n;
    cin >> m;

    double **tableau = new double *[n + 1];
    for (int i = 0; i < n + 1; i++)
        tableau[i] = new double[n + m + 1];

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
                if (tableau[i][j + n] != 0)
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