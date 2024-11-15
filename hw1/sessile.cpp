#include <fstream>
#include <iostream>
#include <cmath>

#define BOND 0.436
#define DEGTORAD 0.017453278
#define RADTODEG 57.295827909

const double ds = 0.1;
int contactAngle = 107;

typedef struct
{
    double x;
    double z;
    double theta;
} Cell;

double forward_euler (double xn, double ds, double rhs)  // returns xn+1 or zn+1
{
    return xn + ds*(rhs);
}

Cell init(double s, double x, double z, double theta)    // returns theta n+1 from s=0
{
    Cell data = {0,0,0};
    if (s == 0) {
        data.x = forward_euler(x, ds, cos(theta));
        data.z = forward_euler(z, ds, sin(theta));
        data.theta = (2 + BOND*data.z - sin(theta))*DEGTORAD;
        return data;
    }
    else {
        std::cout << "ERROR: Simulation doesn't start at s=0!\n";
        return data;
    }  
}

double ab2 (double xn, double ds, double rhsn0, double rhsn)
{
    return xn + 1.5*ds*rhsn - 0.5*ds*rhsn0;
}

void run_simulation()
{
    char name[80];
    sprintf(name, "bo%g-a%d-%g.dat", BOND, contactAngle, ds);
    std::ofstream outf{name};

    Cell dataN0 = {0,0,0}, dataN1 = {0,0,0};
    Cell dataN = init(0, 0, 0, 0);
    double s = 0;   // start "time"

    outf << "s | " << "x | " << "z | " << "theta" << "\n";
    outf << s << " " << dataN.x << " " << dataN.z << " " << dataN.theta * RADTODEG << "\n";

    while(dataN.theta <= contactAngle * DEGTORAD) {
        // Update n --> n+1
        dataN1.x = ab2(dataN.x, ds, cos(dataN0.theta), cos(dataN.theta));
        dataN1.z = ab2(dataN.z, ds, sin(dataN0.theta), sin(dataN.theta));
        dataN1.theta = (2 + BOND*dataN1.z - sin(dataN1.theta)/dataN1.x)*DEGTORAD;

        // Store n-1 --> ns
        dataN0.x = dataN.x;
        dataN0.z = dataN.z;
        dataN0.theta = dataN.theta;

        // Store n+1 --> n
        dataN.x = dataN1.x;
        dataN.z = dataN1.z;
        dataN.theta = dataN1.theta;
        s += ds;
        outf << s << " " <<dataN1.x << " " << dataN1.z<< " "  << dataN1.theta * RADTODEG << "\n";
    }
}

int main()
{
    run_simulation();
    return 0;
}
