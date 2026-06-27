#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

int main()
{
    // Tamaño de la matriz
    int N =  12800;

    // Matrices
    vector<double> A(N * N, 1.5);
    vector<double> B(N * N, 2.0);
    vector<double> C(N * N, 0.0);

    // Número de hilos a probar
    vector<int> hilos = {1, 2, 4, 8, 16, 32};

    // Vector para guardar los tiempos
    vector<double> tiempos;

    // Archivo de salida
    ofstream archivo("tiempos.txt");

    archivo << "# Hilos Tiempo(s)\n";

    for (int threads : hilos)
    {
        omp_set_num_threads(threads);

        // Reiniciar matriz C
        fill(C.begin(), C.end(), 0.0);

        double inicio = omp_get_wtime();

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                double suma = 0.0;

                for (int k = 0; k < N; k++)
                {
                    suma += A[i * N + k] * B[k * N + j];
                }

                C[i * N + j] = suma;
            }
        }

        double fin = omp_get_wtime();

        double tiempo = fin - inicio;

        tiempos.push_back(tiempo);

        archivo << threads << " " << tiempo << endl;

        cout << "Hilos: "
             << threads
             << "   Tiempo: "
             << tiempo
             << " s"
             << endl;
    }

    archivo.close();

    // -------------------------------
    // Graficar con matplotlib-cpp
    // -------------------------------

    plt::figure_size(900,600);

    plt::plot(hilos, tiempos, "bo-");

    plt::title("Tiempo de ejecucion vs Numero de hilos");

    plt::xlabel("Numero de hilos");

    plt::ylabel("Tiempo (s)");

    plt::grid(true);

    plt::save("tiempo_vs_hilos.png");

    cout << "\nGrafica guardada como tiempo_vs_hilos.png\n";

    return 0;
}