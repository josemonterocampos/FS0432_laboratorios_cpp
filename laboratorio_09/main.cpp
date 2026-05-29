#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

using namespace std;

// --------------------------------------------------
// Lado derecho de la EDO
// dx/dt = -x + sin(t)
// --------------------------------------------------
double f(double x, double t)
{
    return -x + sin(t);
}

// --------------------------------------------------
// Solución analítica
// x(t) = 1/2 (sin(t) - cos(t)) + 3/2 e^(-t)
// --------------------------------------------------
double exacta(double t)
{
    return 0.5 * (sin(t) - cos(t)) + 1.5 * exp(-t);
}

// --------------------------------------------------
// Método de Euler
// --------------------------------------------------
void euler(
    vector<double>& tiempos,
    vector<double>& numerica,
    vector<double>& analitica,
    vector<double>& errores,
    double t0,
    double tf,
    double h,
    double x0
)
{
    int N = static_cast<int>((tf - t0) / h);

    // Limpiar vectores por seguridad
    tiempos.clear();
    numerica.clear();
    analitica.clear();
    errores.clear();

    // Variables iniciales
    double t = t0;
    double x = x0;

    // Guardar condición inicial
    tiempos.push_back(t);
    numerica.push_back(x);

    double x_exacta = exacta(t);
    analitica.push_back(x_exacta);

    double error = fabs(x - x_exacta);
    errores.push_back(error);

    // Iteraciones de Euler
    for (int n = 0; n < N; n++)
    {
        // Método de Euler
        x = x + h * f(x, t);

        // Actualizar tiempo
        t = t + h;

        // Solución exacta
        x_exacta = exacta(t);

        // Error absoluto
        error = fabs(x - x_exacta);

        // Guardar resultados
        tiempos.push_back(t);
        numerica.push_back(x);
        analitica.push_back(x_exacta);
        errores.push_back(error);
    }
}

// --------------------------------------------------
// Programa principal
// --------------------------------------------------
int main()
{
    // Parámetros
    double t0 = 0.0;
    double tf = 10.0;
    double h  = 0.1;
    double x0 = 1.0;

    // Vectores
    vector<double> tiempos;
    vector<double> numerica;
    vector<double> analitica;
    vector<double> errores;

    // Ejecutar Euler
    euler(
        tiempos,
        numerica,
        analitica,
        errores,
        t0,
        tf,
        h,
        x0
    );

    // Calcular error global máximo
    double error_max = 0.0;

    for (size_t i = 0; i < errores.size(); i++)
    {
        if (errores[i] > error_max)
        {
            error_max = errores[i];
        }
    }

    // Imprimir tabla
    cout << fixed << setprecision(6);

    cout << "t\tEuler\t\tExacta\t\tError\n";

    for (size_t i = 0; i < tiempos.size(); i++)
    {
        cout << tiempos[i] << "\t"
             << numerica[i] << "\t"
             << analitica[i] << "\t"
             << errores[i] << endl;
    }

    cout << "\nError global maximo: "
         << error_max << endl;
    
        // --------------------------------------------------
    // GRAFICA 1
    // Solucion numerica vs solucion analitica
    // --------------------------------------------------

    plt::figure();

    plt::plot(tiempos, numerica, {{"label", "Euler"}});
    plt::plot(tiempos, analitica, {{"label", "Exacta"}});

    plt::title("Metodo de Euler");
    plt::xlabel("Tiempo");
    plt::ylabel("x(t)");

    plt::legend();

    plt::save("solucion_euler.png");


    // --------------------------------------------------
    // GRAFICA 2
    // Error absoluto
    // --------------------------------------------------

    plt::figure();

    plt::plot(tiempos, errores, {{"label", "Error absoluto"}});

    plt::title("Error absoluto");
    plt::xlabel("Tiempo");
    plt::ylabel("Error");

    plt::legend();

    plt::save("error_local.png");

    return 0;
}