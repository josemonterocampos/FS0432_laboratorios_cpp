/* poisson_1d_GaussSeidel.cpp

Repositorio oficial Matplotlib-cpp:
https://github.com/lava/matplotlib-cpp

Recuerde descargar matplotlibcpp.h y
colocarlo en el mismo directorio que este código.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

double fuente(double x)
{
    return std::sin(M_PI * x);
}

double solucion_exacta(double x)
{
    return -std::sin(M_PI * x) / (M_PI * M_PI);
}

int main()
{
    const int N = 10;
    const double a = 0.0;
    const double b = 1.0;
    const double h = (b - a) / N;

    const double alpha = 0.0;
    const double beta = 0.0;

    const int max_iter = 100000;
    const double tol = 1e-10;

    std::vector<double> x(N + 1);
    std::vector<double> u(N + 1, 0.0);
    std::vector<double> u_exacta(N + 1);

    for (int i = 0; i <= N; i++)
    {
        x[i] = a + i * h;
        u_exacta[i] = solucion_exacta(x[i]);
    }

    u[0] = alpha;
    u[N] = beta;

    std::vector<double> errores_convergencia;

    int iter = 0;
    double error = 1.0;

    while (iter < max_iter && error > tol)
    {
        error = 0.0;

        // Gauss-Seidel
        for (int i = 1; i < N; i++)
        {
            double valor_anterior = u[i];

            u[i] = 0.5 *
                   (u[i + 1]
                  + u[i - 1]
                  - h * h * fuente(x[i]));

            error = std::max(
                error,
                std::abs(u[i] - valor_anterior));
        }

        double error_exacto = 0.0;

        for (int i = 0; i <= N; i++)
        {
            error_exacto = std::max(
                error_exacto,
                std::abs(u[i] - u_exacta[i]));
        }

        errores_convergencia.push_back(error_exacto);

        iter++;
    }

    std::cout << "Iteraciones: "
              << iter << std::endl;

    std::cout << "Error final entre iteraciones: "
              << error << std::endl;

    double error_max = 0.0;

    for (int i = 0; i <= N; i++)
    {
        error_max = std::max(
            error_max,
            std::abs(u[i] - u_exacta[i]));
    }

    std::cout << "Error maximo contra solucion exacta: "
              << error_max << std::endl;

    // ==========================
    // Grafica de la solución
    // ==========================

    plt::figure();

    plt::plot(x, u,
    {
        {"label", "Solucion numerica"}
    });

    plt::plot(x, u_exacta,
    {
        {"label", "Solucion exacta"}
    });

    plt::title("Ecuacion de Poisson 1D - Gauss-Seidel");
    plt::xlabel("x");
    plt::ylabel("u(x)");

    plt::legend();

    plt::save("solucion_gauss_seidel.png");

    // ==========================
    // Grafica de la convergencia
    // ==========================

    std::vector<double> iteraciones(
        errores_convergencia.size());

    for (size_t i = 0;
         i < iteraciones.size();
         i++)
    {
         iteraciones[i] = static_cast<double>(i);
    }

    plt::clf();
    plt::close();
    plt::figure();

    plt::plot(iteraciones,
              errores_convergencia);

    plt::title("Convergencia Gauss-Seidel");
    plt::xlabel("Iteracion");
    plt::ylabel("Error maximo");

    plt::save("error_gauss_seidel.png");

    std::cout << "Grafica de error guardada." << std::endl;

    return 0;
}