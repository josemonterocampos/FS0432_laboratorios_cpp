// clasificar_notas.cpp
// FS0432 - Física Computacional
// Laboratorio 7

#include <iostream>

using namespace std;


void mostrarNotas(double* notas, int cantidad)
{
    cout << "\nNotas validas ingresadas:\n";

    for (int i = 0; i < cantidad; i++)
    {
        cout << "Nota " << i + 1 << ": " << notas[i] << endl;
    }
}

// Función para clasificar el rendimiento de los estudiantes
// Reprobado: menor a 70
// Aprobado: entre 70 y 89
// Sobresaliente: 90 o más

void clasificarRendimiento(double* notas,
                           int cantidad,
                           int& reprobados,
                           int& aprobados,
                           int& sobresalientes)
{
    // Inicializar contadores
    reprobados = 0;
    aprobados = 0;
    sobresalientes = 0;

    for (int i = 0; i < cantidad; i++)
    {
        if (notas[i] < 70.0)
        {
            reprobados++;
        }
        else if (notas[i] < 90.0)
        {
            aprobados++;
        }
        else
        {
            sobresalientes++;
        }
    }
}

// Función para calcular el promedio del grupo

double calcularPromedio(double* notas, int cantidad)
{
    double suma = 0.0;

    for (int i = 0; i < cantidad; i++)
    {
        suma += notas[i];
    }

    if (cantidad > 0)
    {
        return suma / cantidad;
    }
    else
    {
        return 0.0;
    }
}

// Función para encontrar nota máxima y mínima


void encontrarMaxMin(double* notas,
                     int cantidad,
                     double& maxima,
                     double& minima)
{
    maxima = notas[0];
    minima = notas[0];

    for (int i = 1; i < cantidad; i++)
    {
        if (notas[i] > maxima)
        {
            maxima = notas[i];
        }

        if (notas[i] < minima)
        {
            minima = notas[i];
        }
    }
}

// Función principal

int main()
{
    // Arreglo estático de 10 elementos
    double notas[10];

    int cantidad = 0;
    int intentos = 0;

    double entrada;

    cout << "===== SISTEMA DE NOTAS =====\n";

    // Ingreso de notas usando do-while
    
    do
    {
        cout << "\nIngrese una nota entre 0 y 100 ";
        cout << "(o -1 para terminar): ";

        cin >> entrada;

        intentos++;

        if (entrada == -1)
        {
            break;
        }

        // Validacion de rango
        if (entrada < 0.0 || entrada > 100.0)
        {
            cout << "Nota inválida. Intente nuevamente.\n";
            continue;
        }

        // Guardar nota
        if (cantidad < 10)
        {
            notas[cantidad] = entrada;
            cantidad++;
        }
        else
        {
            cout << "Se alcanzó el límite de 10 notas.\n";
            break;
        }

    } while (cantidad < 10 && intentos < 15);

    // Mostrar notas ingresadas
    mostrarNotas(notas, cantidad);

    // Clasificación de rendimiento
    int reprobados;
    int aprobados;
    int sobresalientes;

    clasificarRendimiento(notas,
                           cantidad,
                           reprobados,
                           aprobados,
                           sobresalientes);

    cout << "\nClasificación del grupo:\n";
    cout << "Reprobados: " << reprobados << endl;
    cout << "Aprobados: " << aprobados << endl;
    cout << "Sobresalientes: " << sobresalientes << endl;

    // Promedio del grupo
    double promedio = calcularPromedio(notas, cantidad);

    cout << "\nPromedio del grupo: " << promedio << endl;

    // Nota máxima y mínima
    if (cantidad > 0)
    {
        double maxima;
        double minima;

        encontrarMaxMin(notas, cantidad, maxima, minima);

        cout << "\nNota máxima: " << maxima << endl;
        cout << "Nota mínima: " << minima << endl;
    }
    else
    {
        cout << "\nNo se ingresaron notas válidas.\n";
    }

    return 0;
}