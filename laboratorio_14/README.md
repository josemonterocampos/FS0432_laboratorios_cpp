# Laboratorio 14 - Multiplicación Matricial con OpenMP

###Estudiante: Jose Ricardo Montero Campos
###Carné: C05005

## Descripción

Este laboratorio implementa la multiplicación de dos matrices cuadradas utilizando C++ y OpenMP para paralelizar el algoritmo. El programa mide el tiempo de ejecución para distintos números de hilos y genera automáticamente una gráfica del tiempo de ejecución en función del número de hilos utilizando la biblioteca **matplotlib-cpp**.

## Archivos incluidos

* `matrix_multiplication.cpp` : Código fuente del programa.
* `tiempos.txt` : Archivo con los tiempos de ejecución para cada número de hilos.
* `tiempo_vs_hilos.png` : Gráfica del tiempo de ejecución vs. número de hilos.
* `README.md` : Descripción del laboratorio.
* `matplotlibcpp.h` : Biblioteca enlace para graficar con python desde c++.

## Requisitos

* Compilador **g++** con soporte para OpenMP.
* Python 3.
* Biblioteca **matplotlib-cpp**.
* Biblioteca de desarrollo de Python (`Python.h`).

## Compilación

En Windows (MSYS2 + g++):

```bash
g++ matrix_multiplication.cpp -O3 -fopenmp -IC:\Users\monge\AppData\Local\Programs\Python\Python313\include -LC:\Users\monge\AppData\Local\Programs\Python\Python313\libs -lpython313 -o matrix.exe
```

## Ejecución

```bash
.\matrix.exe
```

El programa realiza automáticamente las siguientes acciones:

1. Inicializa las matrices.
2. Ejecuta la multiplicación matricial utilizando 1, 2, 4, 8, 16 y 32 hilos.
3. Mide el tiempo de ejecución mediante `omp_get_wtime()`.
4. Guarda los resultados en `tiempos.txt`.
5. Genera la gráfica `tiempo_vs_hilos.png`.

## Resultados

El archivo `tiempos.txt` contiene dos columnas:

```text
Hilos   Tiempo(s)
```

La gráfica `tiempo_vs_hilos.png` muestra el comportamiento del tiempo de ejecución conforme aumenta el número de hilos utilizados.
