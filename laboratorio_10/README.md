**Curso:** FS0432 Física Computacional
**Laboratorio:** 10
**Estudiante: Jose Ricardo Montero Campos 
**Carné: C05005

## Descripción

En este laboratorio se resuelve numéricamente la ecuación de Poisson en una dimensión:

[
\frac{d^2u}{dx^2}=f(x)
]

en el intervalo (0 \le x \le 1), con condiciones de frontera de Dirichlet:

[
u(0)=0, \qquad u(1)=0
]

utilizando una discretización por diferencias finitas y los métodos iterativos de Jacobi y Gauss-Seidel.

La función fuente utilizada es:

[
f(x)=\sin(\pi x)
]

y la solución analítica correspondiente es:

[
u(x)=-\frac{\sin(\pi x)}{\pi^2}
]

## Archivos incluidos

* `poisson_1d_Jacobi.cpp`
* `poisson_1d_GaussSeidel.cpp`
* `solucion_jacobi.png`
* `error_jacobi.png`
* `solucion_gauss_seidel.png`
* `error_gauss_seidel.png`
* `output_jacobi.txt`
* `output_gauss_seidel.txt`
* `comparacion.txt`
* `README.md`

## Requisitos

Para compilar los programas es necesario contar con:

* Compilador `g++`
* Python 3
* NumPy
* Biblioteca `matplotlib-cpp`
* Archivo `matplotlibcpp.h` ubicado en el mismo directorio que los programas

Repositorio oficial de matplotlib-cpp:

https://github.com/lava/matplotlib-cpp

## Compilación

### Jacobi

```bash
g++ poisson_1d_Jacobi.cpp -o poisson_1d_Jacobi.x \
-I$CONDA_PREFIX/include/python3.11 \
-I$(python -c "import numpy; print(numpy.get_include())") \
-L$CONDA_PREFIX/lib \
-lpython3.11 \
-Wl,-rpath,$CONDA_PREFIX/lib
```

### Gauss-Seidel

```bash
g++ poisson_1d_GaussSeidel.cpp -o poisson_1d_GaussSeidel.x \
-I$CONDA_PREFIX/include/python3.11 \
-I$(python -c "import numpy; print(numpy.get_include())") \
-L$CONDA_PREFIX/lib \
-lpython3.11 \
-Wl,-rpath,$CONDA_PREFIX/lib
```

## Ejecución

### Jacobi

```bash
./poisson_1d_Jacobi.x
```

Guardar la salida en un archivo:

```bash
./poisson_1d_Jacobi.x > output_jacobi.txt
```

### Gauss-Seidel

```bash
./poisson_1d_GaussSeidel.x
```

Guardar la salida en un archivo:

```bash
./poisson_1d_GaussSeidel.x > output_gauss_seidel.txt
```

## Resultados

Cada programa imprime:

* Número total de iteraciones.
* Error final de convergencia.
* Error máximo respecto a la solución analítica.

Además genera las siguientes figuras:

* Comparación entre la solución numérica y la solución exacta.
* Error máximo de convergencia en función del número de iteración.

## Comparación de métodos

Se comparan los métodos de Jacobi y Gauss-Seidel utilizando:

* El número de iteraciones requeridas para converger.
* El error final obtenido.

En general, el método de Gauss-Seidel converge más rápidamente debido a que utiliza inmediatamente los valores actualizados durante cada iteración.
