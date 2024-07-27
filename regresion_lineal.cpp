#include "regresion_lineal.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


Datos* crearDatos(int n) {
    Datos* datos = new Datos;
    datos->n = n;
    datos->x.resize(n);
    datos->y.resize(n);
    return datos;
}


void liberarDatos(Datos* datos) {
    delete datos;
}


void calcularRegresion(Datos* datos, double& m, double& b, double alpha, int epochs) {
    int n = datos->n;
    vector<double> x = datos->x;
    vector<double> y = datos->y;

    ofstream mseFile("mse.txt");

    for (int epoch = 0; epoch < epochs; ++epoch) {
        double m_gradient = 0;
        double b_gradient = 0;
        double totalError = 0;

        for (int i = 0; i < n; ++i) {
            double y_pred = m * x[i] + b;
            double error = y_pred - y[i];
            m_gradient += error * x[i];
            b_gradient += error;
            totalError += error * error;
        }

        m_gradient /= n;
        b_gradient /= n;
        m -= alpha * m_gradient;
        b -= alpha * b_gradient;

        double mse = totalError / n;
        mseFile << mse << endl;

        if (epoch % 10 == 0 || epoch == epochs - 1) {
            cout << "Epoca: " << epoch + 1 << endl;
            cout << "X\tY\tY_pred\tY - Y_pred\tError_Cuad" << endl;
            for (int i = 0; i < n; ++i) {
                double y_pred = m * x[i] + b;
                double error = y_pred - y[i];
                cout << x[i] << "\t" << y[i] << "\t" << y_pred << "\t" << error << "\t" << error * error << endl;
            }
            cout << "MSE: " << mse << endl << endl;
        }
    }

    mseFile.close();
}
