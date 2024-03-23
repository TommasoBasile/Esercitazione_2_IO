#include <iostream>
#include "Eigen/Eigen"

using namespace std;  // per evitare di ripeterlo ma non metterlo semore perche si potrebbe utilizzare un altro namespace
using namespace Eigen;

int foo(int c)
{   c++;
    return c;
}

int foo2(int &c,  // a livello di memoria per INT e DOUBLE passare la variabile o la referenza è la STESSA COSA (occupano poco spazio)
         int &d)
{   c++;
    return c;
}

int main()
{
    int a = 0;
    int c = a;  // si crea una copia della variabile a

    a++;

    // cout << "c: " << c << endl;  // c NON viene modificato in quando a e c sono oggetti DIVERSI

    const int i = 0; // variabile int che NON può essere modificata dal codice e deve essere subito inizializzata
    // i++; infatti dà errore


   int &ref = a; // si crea un ALIAS, un altro nome alla variabile a
   a++; // modificare a vuol dire modificare il contenuto della referenza

   // Attenzione: la referenza deve essere inizializzata con lo STESSO tipo dell'oggeto associato (anche const), ma l'oggetto potrebbe essere non costante a differenza della referenza

   double d = 5.5;
   int temp = d;
   const int &ref2 = temp; // se si modifica d -> NON viene modificato ref2
   // equivale
   // double d = 5.5
   // const int &ref2 = d;

   int jj = 0;
   int ii = 0;
   int b = foo(jj);

   // Chiamare una funzione
   // Step 1: int c = jj;  si sta facendo una COPIA di jj che quindi rimarrà invariato
   // Step 2: eseguire il corpo della funzione
   // Step 3: return -> int b = valueReturn

   int b4 = foo2(jj,ii);
   // Chiamare una funzione
   // Step 1: int c = jj;  si sta facendo un ALIAS di jj quindi si MODIFICA il valore della variabile
   // Step 2: eseguire il corpo della funzione
   // Step 3: return -> int b = valueReturn

    // Vettori
   srand(5);  // settare il seme: riprodurre sempre le stesse condizioni di partenza
   Vector2d v = Vector2d::Constant(14);  // Vector + dimensione + tipo: in realtà Matrix<double, 2, 1>. si può usare Zero, Random, ones, constant

   // si ottiene vettore riga trasponendo v.transpose() oppure usando RowVector al posto di Vector di prima

   // Operazioni vettoriali tenendo in considerazione righe e colonne
   // Operazioni puntuali v.cwiseProduct(v) così come valore assoluto cwiseAbs() e tutte le altre operazioni puntuali

   // Matrici
   Matrix4d A1 =  Matrix4d::Zero(); // Matrix + dimensione(4x4) + tipo, non si può modificare la struttura della matrice
   MatrixXd A2 = MatrixXd::Ones(3,4); // Matrix con dimensione X VARIABILE, per adesso la dim è 3x4
   // cout << A2 << endl;

   // A2.resize(4,4); // si CAMBIA la dimensione
   // cout << A2 << endl; // resize porta tutto a 0

   A2.conservativeResize(4,4); // si CAMBIA la dimensione
   // cout << A2 << endl; // mantiene (conservative)

   // .col() e .row() .size() danno le caratteristiche


    srand(5);
    unsigned int n = 5;

    // Prima Matrice
    VectorXd v2 = VectorXd::LinSpaced(n*n,1,n*n);
    MatrixXd A3 = v2.reshaped(n,n).transpose();

    const MatrixXd LU3 = A3.fullPivLu().matrixLU();
    MatrixXd I =  MatrixXd::Identity(5,5);
    MatrixXd L3b = LU3.triangularView<StrictlyLower>();
    MatrixXd L3 = L3b + I;
    MatrixXd U3 = LU3.triangularView<Upper>();
    MatrixXd P3 = A3.fullPivLu().permutationP();




    //MatrixXi l = MatrixXi::Identity();
    //l.block<5,5>(0,0).triangularView<StrictlyLower>() = lu.matrixLU();
    //cout << l << endl;

    // oppure con ciclo for

    // for(unsigned int k = 0; i < n; k++)
    // {
    //    A.row(k) = v2.segment(k*n,n); // parto dalla riga i-esima e prendo n elementi
    // }
    VectorXd b1 = A3*VectorXd::Ones(n,1);
    VectorXd x1 = A3.lu().solve(b1);

    // Seconda matrice: randomica
    MatrixXd A4 = MatrixXd::Random(n,n);
    MatrixXd A5 = A4 + MatrixXd::Ones(n,n);
    VectorXd b2 = A5*VectorXd::Ones(n,1);
    VectorXd x2 = A5.lu().solve(b2);

    // Terza matrice: matrice Hilbert
    MatrixXd A6 = MatrixXd::Zero(n,n);
    VectorXd v3 = VectorXd::LinSpaced(n*n,1,n*n);

    for (unsigned int i = 0; i < n; i++)
    {
        A6.col(i) = VectorXd::LinSpaced(n,i+1,n+i);
    }
    A6 = A6.cwiseInverse();
    VectorXd b3 = A6*VectorXd::Ones(n,1);
    VectorXd x3 = A6.lu().solve(b3);

    // JacobiSVD<MatrixXd> svd(A4);
    // VectorXd v1 = svd.singularValues();



    return 0;
}
