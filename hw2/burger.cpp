#include <fstream>
#include <iostream>
#include <cmath>

#define L0 2
#define SMALL 1e-10

const double dx = 0.01;
const int N =L0/dx;
const int xStart = -1;
const double soundSpeed = 2;
const double viscosity = 0;
const int endTime = 2;
const double dt = 0.01;

double x[N + 1];
double u[N + 1];

void init(std::ofstream& outf)
{
    for(int i = 0; i < N + 1; i++) {
        x[i] = xStart + dx*i;       // initialize global x coordinates
        u[i] = -sin (M_PI*x[i]);    // initalize velocity field
        outf << 0 << " " << x[i] << " " << u[i] << "\n";
    }
}

double forward_euler (double un, double rhs)
{
    return un + dt*(rhs); // u^n+1
}

double first_central_diff (double coeff, double left, double right)     // first derivative central differnce
{
    return coeff * (right - left) / (2 * dx);
}

double first_upwind (double coeff, double left, double center)
{
    return coeff * (center - left) / dx;
}

double second_central_diff (double coeff, double left, double center, double right)     // second derivative central differnce
{
    return coeff*(right - 2*center + left) / (pow(dx,2));
}

double lax_fried (double left, double center, double right)
{
    return (pow(right,2) - pow(left,2)) / (2 * dx) - (right - 2*center + left) / (2 * dt);
}

void periodicBC(int i, int index[2])
{
    if (i - 1 < 0)
        index[0] = N;
    else if (i + 1 > N)
        index[1] = 0;
}

void run_simulation()
{
    char name[80];
    sprintf(name, "burger-central-%g-%g", viscosity, dt);
    std::ofstream outf{name};
    init(outf);

    // main time loop
    for (double t = dt; t <= endTime; t+=dt) {

        for (int i = 0; i < N + 1; i++) {
            int index[2] = {i-1, i+1};
            periodicBC(i, index);   // check to see if on boundary
            double left = u[index[0]];
            double right = u[index[1]];

            // double adv = first_central_diff (soundSpeed, left, right);
            double adv = first_central_diff (u[i], left, right);
            // double adv = first_upwind (soundSpeed, left, u[i]);
            // double adv = lax_fried (left, u[i], right);
            double dif = second_central_diff (viscosity, left, u[i], right);
            
            // update u^n --> u^n+1
            u[i] = forward_euler (u[i], adv + dif);
            outf << t << " " << x[i] << " " << u[i] << "\n";
        }
    }
}

int main()
{
    run_simulation();
    return 0;
}
