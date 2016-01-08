#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int k = 3;
    int M[3][3];
    M = retournement(M,k);


    w.show();

    return a.exec();
}

int ** retournement(int ** M, int k){
    int tmp[k][k];
    int S[k][k];
    for(int i = 0;i<k;i++){
        for(int j = 0 ;j<k;j++){
            S[k -(i+1)][k -(j+1)] = M[i][j];
        }
    }

    return S;
}

void afficheMatrice(int ** M, int k){
    cout << "[";
    for(int i=0;i<k;i++){
        for(int j = 0;j<k;j++){

        }
        cout << "\n";
    }
}
