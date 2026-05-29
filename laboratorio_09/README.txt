# Laboratorio 09 — Método de Euler
# Estudiante: Jose Ricardo Montero Campos
# Carné: C05005

## Descripción

Este programa implementa el método de Euler para aproximar la solución de la ecuación diferencial ordinaria:

[
\frac{dx}{dt} = -x + \sin(t)
]

con condición inicial:

[
x(0)=1
]

El programa:

* calcula la solución numérica usando Euler,
* compara con la solución analítica,
* calcula el error absoluto,
* genera gráficas en formato PNG.

---

# Archivos incluidos

* `main.cpp`
* `matplotlibcpp.h`
* `solucion_euler.png`
* `error_local.png`

---

# Requisitos

* Python 3
* NumPy
* Matplotlib
* g++

---

# Instalación de dependencias

```powershell
pip install matplotlib numpy
```

---

# Compilación

```powershell
g++ main.cpp -o main -IC:\Users\monge\AppData\Local\Programs\Python\Python313\Include -LC:\Users\monge\AppData\Local\Programs\Python\Python313\libs -lpython313
```

---

# Ejecución

```powershell
.\main.exe
```

---

# Salida

El programa:

* imprime una tabla con:

  * tiempo,
  * solución numérica,
  * solución exacta,
  * error absoluto.
* genera las imágenes:

  * `solucion_euler.png`
  * `error_local.png`
