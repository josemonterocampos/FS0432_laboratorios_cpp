# Laboratorio 15 – Producto Punto con MPI

Curso FS0432 – Física Computacional
Nombre / Carné: Jose Ricardo Montero Campos / C05005

**Curso:** FS0432 – Física Computacional
**Tema:** Producto punto utilizando MPI en C++

## Descripción

Este laboratorio implementa el cálculo del producto punto entre dos vectores utilizando programación paralela con MPI (Message Passing Interface).

El programa distribuye dos vectores entre varios procesos mediante `MPI_Send` y `MPI_Recv`. Cada proceso calcula un producto punto parcial y posteriormente todos los resultados son combinados utilizando `MPI_Reduce` con la operación `MPI_SUM` para obtener el producto punto global.

## Archivos incluidos

* `producto_punto_mpi.cpp` → Código fuente del programa.
* `tiempos.txt` → Tiempos de ejecución para diferentes números de procesos.
* `tiempo_vs_procesos.png` → Gráfica del tiempo de ejecución en función del número de procesos.
* `README.md` → Instrucciones de compilación y ejecución.
* `reporte.pdf` → Informe del laboratorio.

## Requisitos

* Compilador C++ compatible con MPI.
* Microsoft MPI (MS-MPI) instalado.
* SDK de Microsoft MPI instalado.

## Compilación

```bash
g++ producto_punto_mpi.cpp -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi -o producto.exe
```

## Ejecución

Ejecutar el programa con el número deseado de procesos.

### 1 proceso

```bash
mpiexec -n 1 .\producto.exe
```

### 2 procesos

```bash
mpiexec -n 2 .\producto.exe
```

### 4 procesos

```bash
mpiexec -n 4 .\producto.exe
```

### 8 procesos

```bash
mpiexec -n 8 .\producto.exe
```

## Funcionamiento del programa

1. El proceso con `rank = 0` inicializa los vectores `A` y `B`.
2. Los datos se dividen en bloques iguales y se envían al resto de procesos mediante `MPI_Send`.
3. Cada proceso recibe su bloque utilizando `MPI_Recv`.
4. Cada proceso calcula el producto punto de su bloque local.
5. Los resultados parciales se combinan utilizando `MPI_Reduce` con la operación `MPI_SUM`.
6. El proceso 0 imprime el producto punto total y el tiempo de ejecución.

## Resultado esperado

El producto punto obtenido es aproximadamente:

```
Producto punto = 128000
```

El tiempo de ejecución disminuye al aumentar el número de procesos, aunque para un problema de tamaño relativamente pequeño pueden observarse pequeñas variaciones debido al costo de comunicación entre procesos.





