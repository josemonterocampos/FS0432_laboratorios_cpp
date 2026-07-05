#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double f(double x)
{
    return sin(x);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 128000;

    int local_n = N / size;

    vector<double> localA(local_n);
    vector<double> localB(local_n);

    if(rank == 0)
    {
        vector<double> A(N);
        vector<double> B(N);

        for(int i=0;i<N;i++)
        {
            A[i] = f((double)i);
            B[i] = 2.0*f((double)i);
        }

        // Enviar bloques a los demás procesos
        for(int p=1;p<size;p++)
        {
            MPI_Send(&A[p*local_n], local_n, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
            MPI_Send(&B[p*local_n], local_n, MPI_DOUBLE, p, 1, MPI_COMM_WORLD);
        }

        // Copiar el bloque del proceso 0
        for(int i=0;i<local_n;i++)
        {
            localA[i]=A[i];
            localB[i]=B[i];
        }
    }
    else
    {
        MPI_Recv(localA.data(), local_n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(localB.data(), local_n, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double inicio = MPI_Wtime();

    double suma_local = 0.0;

    for(int i=0;i<local_n;i++)
        suma_local += localA[i]*localB[i];

    double fin = MPI_Wtime();

    double tiempo = fin - inicio;

    double suma_global;

    MPI_Reduce(&suma_local,
               &suma_global,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    double tiempo_max;

    MPI_Reduce(&tiempo,
               &tiempo_max,
               1,
               MPI_DOUBLE,
               MPI_MAX,
               0,
               MPI_COMM_WORLD);

    if(rank==0)
    {
        cout<<"Producto punto = "<<suma_global<<endl;
        cout<<"Tiempo = "<<tiempo_max<<" s"<<endl;
    }

    MPI_Finalize();

    return 0;
}