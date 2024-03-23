#include <iostream>
#include "Eigen/Eigen"
#include <iomanip>

using namespace std;
using namespace Eigen;

Vector2d sistemiLU(Matrix2d &A,Vector2d &b)
{
    Vector2d xLU = A.lu().solve(b);
    return xLU;
}

Vector2d sistemiLUdecomp(Matrix2d &A,Vector2d &b)  // calcolando la decomposizione
{
    Matrix2d LU = A.fullPivLu().matrixLU();
    Matrix2d Lb = LU.triangularView<StrictlyLower>();
    Matrix2d L = Lb + Matrix2d::Identity(2,2);
    Matrix2d U = LU.triangularView<Upper>();
    Matrix2d P = A.fullPivLu().permutationP();
    Vector2d y = L.inverse()*P*b;
    Vector2d x = U.inverse()*y;
    return x;
}

Vector2d sistemiLUerr(Vector2d &b,Vector2d &xLU)
{
    Vector2d xVero = Vector2d::Constant(-1);
    Vector2d difxLU = xVero - xLU;
    Vector2d errRelLU = difxLU.cwiseProduct(xVero);
    return errRelLU.cwiseAbs();
}

Vector2d sistemiQR(Matrix2d &A,Vector2d &b)
{
    Vector2d xQR = A.fullPivHouseholderQr().solve(b);
    return xQR;
}

Vector2d sistemiQRerr(Vector2d &b,Vector2d &xQR)
{
    Vector2d xVero = Vector2d::Constant(-1);
    Vector2d difxQR = xVero - xQR;
    Vector2d errRelQR = difxQR.cwiseProduct(xVero);
    return errRelQR.cwiseAbs();
}

int main()
{   // Punto 1 PALU
    Matrix2d A1;
    A1(0,0) = 5.547001962252291e-01;
    A1(0,1) = -3.770900990025203e-02;
    A1(1,0) = 8.320502943378437e-01;
    A1(1,1) = -9.992887623566787e-01;
    Vector2d b1;
    b1(0) = -5.169911863249772e-01;
    b1(1) = 1.672384680188350e-01;

    Vector2d x1LU = sistemiLU(A1,b1);
    // cout << x1LU << endl; // torna x = [-1,-1]
    Vector2d x1Ludecomp = sistemiLUdecomp(A1,b1);
    // cout << x1Ludecomp << endl; // torna x = [-1,-1]
    // cout << x1LU - x1Ludecomp << std::setprecision(0) << endl; // non c'è differenza
    Vector2d errRel1LU = sistemiLUerr(b1,x1LU);
    // cout << errRel1LU.cwiseAbs() << endl; // ordine di 10^-16

    // Punto 1 QR
    Vector2d x1QR = sistemiQR(A1,b1);
    // cout << x1QR << endl; // torna x = [-1,1]
    Vector2d errRel1QR = sistemiQRerr(b1,x1QR);
    // cout << errRel1QR << endl; // ordine di 10^-16


    // Punto 2 PALU
        Matrix2d A2;
        A2(0,0) = 5.547001962252291e-01;
        A2(0,1) = -5.540607316466765e-01;
        A2(1,0) = 8.320502943378437e-01;
        A2(1,1) = -8.324762492991313e-01;
        Vector2d b2;
        b2(0) = -6.394645785530173e-04;
        b2(1) = 4.259549612877223e-04;

        Vector2d x2LU = sistemiLU(A2,b2);
        // cout << x2LU << endl; // torna x = [-1,-1]
        Vector2d errRel2LU = sistemiLUerr(b2,x2LU);
        // cout << errRel2LU.cwiseAbs() << endl; // ordine di 10^-13

     // Punto 2 QR
        Vector2d x2QR = sistemiQR(A2,b2);
        // cout << x2QR << endl; // torna x = [-1,1]
        Vector2d errRel2QR = sistemiQRerr(b2,x2QR);
        // cout << errRel2QR << endl; // ordine di 10^-13


      // Punto 3 PALU
            Matrix2d A3;
            A3(0,0) = 5.547001962252291e-01;
            A3(0,1) = -5.547001955851905e-01;
            A3(1,0) = 8.320502943378437e-01;
            A3(1,1) = -8.320502947645361e-01;
            Vector2d b3;
            b3(0) = -6.400391328043042e-10;
            b3(1) = 4.266924591433963e-10;

            Vector2d x3LU = sistemiLU(A3,b3);
            // cout << x3LU << endl; // torna x = [-1,-1]
            Vector2d errRel3LU = sistemiLUerr(b3,x3LU);
            // cout << errRel3LU.cwiseAbs() << endl; // ordine di 10^-7

       // Punto 3 QR
            Vector2d x3QR = sistemiQR(A3,b3);
            // cout << x3QR << endl; // torna x = [-1,1]
            Vector2d errRel3QR = sistemiQRerr(b3,x3QR);
            // cout << errRel3QR << endl; // ordine di 10^-7

    return 0;
}
