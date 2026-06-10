#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;

const double sigma = 10.0;
const double rho = 28.0;
const double beta = 8.0/3.0;

std::vector<double> lorenz(const std::vector<double>& r)
{
    double x = r[0];
    double y = r[1];
    double z = r[2];

    return {
        sigma*(y-x),
        x*(rho-z)-y,
        x*y-beta*z
    };
}

std::vector<std::vector<double>> euler(double h,double t0,double tf,double x0,double y0,double z0)
{
    int N = (tf-t0)/h + 1;
    std::vector<std::vector<double>> sol;
    std::vector<double> r = {x0,y0,z0};
    sol.push_back(r);

    for(int i=1;i<N;i++){
        auto k1 = lorenz(r);
        for(int j=0;j<3;j++) r[j] += h*k1[j];
        sol.push_back(r);
    }
    return sol;
}

std::vector<std::vector<double>> rk2(double h,double t0,double tf,double x0,double y0,double z0)
{
    int N = (tf-t0)/h + 1;
    std::vector<std::vector<double>> sol;
    std::vector<double> r = {x0,y0,z0};
    sol.push_back(r);

    for(int i=1;i<N;i++){
        auto k1 = lorenz(r);
        std::vector<double> temp(3);

        for(int j=0;j<3;j++) temp[j] = r[j] + 0.5*h*k1[j];
        auto k2 = lorenz(temp);

        for(int j=0;j<3;j++) r[j] += h*k2[j];
        sol.push_back(r);
    }
    return sol;
}

std::vector<std::vector<double>> rk4(double h,double t0,double tf,double x0,double y0,double z0)
{
    int N = (tf-t0)/h + 1;
    std::vector<std::vector<double>> sol;
    std::vector<double> r = {x0,y0,z0};
    sol.push_back(r);

    for(int i=1;i<N;i++){
        auto k1 = lorenz(r);

        std::vector<double> temp(3);

        for(int j=0;j<3;j++) temp[j] = r[j] + 0.5*h*k1[j];
        auto k2 = lorenz(temp);

        for(int j=0;j<3;j++) temp[j] = r[j] + 0.5*h*k2[j];
        auto k3 = lorenz(temp);

        for(int j=0;j<3;j++) temp[j] = r[j] + h*k3[j];
        auto k4 = lorenz(temp);

        for(int j=0;j<3;j++)
            r[j] += h/6.0*(k1[j] + 2*k2[j] + 2*k3[j] + k4[j]);

        sol.push_back(r);
    }
    return sol;
}

PYBIND11_MODULE(lorenz_methods, m)
{
    m.def("euler",&euler);
    m.def("rk2",&rk2);
    m.def("rk4",&rk4);
}