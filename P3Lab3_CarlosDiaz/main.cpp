//#include <cstdlib>
#include <iostream>
#include<stdlib.h>                                                              //sirve para hacer el random
#include <math.h>

//using namespace std;
using std::cout;
using std::cin;
using std::endl;

/*
 * 
 */
//PROTOTIPOS DE FUNCIONES
int** provisionarMatriz(int);                                                   //Se recibe un entero n  y se devuelve una matriz de nxn con números aleatorios
int** provisionarMatriz2(int);
double** provisionarMatriz3(int);
void liberarMatriz(int**&, int);
void liberarMatriz(double**&, int);

void imprimirMatriz(int**, int);

int** obtenerSubconjunta(int**, int);
int** obtenerCofactor(int**, int, int, int, bool);

int det(int**, int);

int** transpuesta(int**, int);

int** split(int** m1, int size);                                                //Se recibe una matriz y se retorna la matriz adjunta de esta

double** inversa(int**, int, int);                                              //Se recibe una matriz y su determinante, se retorna su matriz inversa

void fraccion(int, int);                                                        //MéTODO EXTRA

int main(int argc, char** argv) {
    int seguir = 0, size=0;
    int** matriz = NULL; int** transp = NULL; int** adj = NULL;
    double ** inv = NULL;
    while(seguir!=1){
        int size=0;
        cout << "Ingresa el tamaño de la matriz: ";
        cin >> size;
        while(size<=1){
            cout << "Ingresa el tamaño mayor o igual a 2: ";
            cin >> size;
        }

        int** matriz = provisionarMatriz(size);
        cout << "La matriz generada es: " << endl;
        imprimirMatriz(matriz, size);
        cout << "" << endl;

        /*cout << "La subconjunta: " << endl;
        int** sub = obtenerSubconjunta(matriz, size);
        if(matriz==sub){
            imprimirMatriz(sub, size);
        } else {
            imprimirMatriz(sub, size-1);
        }*/

        cout << "Su determinante: ";
        int deter = det(matriz, size);
        cout << deter << endl;
        cout << "" << endl;

        cout << "La transpuesta: " << endl;
        int** transp = transpuesta(matriz, size);
        imprimirMatriz(transp, size);
        cout << "" << endl;

        cout << "La adjunta: " << endl;
        int** adj = split(transp, size);
        imprimirMatriz(adj, size);
        cout << "" << endl;

        cout << "La inversa: " << endl;
        double** inv = inversa(adj, size, deter);
        //imprimirMatriz((int) inv, size);
        cout << "" << endl;
        
        cout << "Desea seguir?: 0. Sí   1. No: ";
        cin >> seguir;
    }
    
        cout << "" << endl;
        liberarMatriz(matriz, size);
        //liberarMatriz(sub, size-1);
        liberarMatriz(transp, size);
        liberarMatriz(adj, size);
        liberarMatriz(inv, size);

        cout << "Memoria liberada";
        return 0;
    
}

int** provisionarMatriz(int size){
    int** matriz = NULL;
    if(size>1){                                                                 //SAFE CODE
        matriz = new int*[size];                                //filas

        for(int i=0; i < size; i++){
            matriz[i] = new int[size];                          //columnas
        }
        
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                //matriz[i][j] = (-9) + rand()%((9+1) - (-9));                  //RELLENADO ALETAROIO
                matriz[i][j] = rand() % 19 - 9;                                 //RELLENADO ALETAROIO
                
                /*int k=0;
                cin >> k;                                                       //LLENADO MANUAL
                matriz[i][j] = k;*/
                
                //matriz[i][j] = 1;                                             //MATRIZ IDENTIDAD
            }
        }
    }
    return matriz;
}

void imprimirMatriz(int** matriz, int size){
    if(matriz!=NULL){                                                 //SAFE CODE
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                cout << std::to_string(matriz[i][j]) +"\t";
            }
            cout << "" << endl;
        }
    }
}

int** obtenerSubconjunta(int** matriz, int size){
    if(size==2){
        //return matriz;
        return matriz;
    } else {
    int** submatriz = provisionarMatriz2(size-1);
    int iEliminar=0, jEliminar=0;
    int m=0, n=0;
    
    for(int h=0; h<=0; h++){
        int m=0, n=0;
        for(int i=0; i<size; i++){                                                  //en realidad solo uso la primera fila
            for(int j=0; j<size; j++){
                if(i!=0 && j!=jEliminar){
                    submatriz[m][n] = matriz[i][j];
                    n++;
                    //cout << std::to_string(matriz[i][j]) + " ";                   //solo comprueba q sirva
                }
                //cout << " " << endl;
            }
            n=0;
            if(i!=0){                                                               //ESTO PORQUE COMO SE COME LA PRIMERA FILA, PARA QUE NO INICIE EN 1
                m++;
            }
        }
        jEliminar++;
    }
    
    return submatriz;
    }
}

int** obtenerCofactor(int** matriz, int size, int x, int y, bool flag){
    int** submatriz = provisionarMatriz2(size-1);
    int iEliminar=x, jEliminar=y;
    int m=0, n=0;
    
        for(int i=0; i<size; i++){                                                  //en realidad solo uso la primera fila
            for(int j=0; j<size; j++){
                if(i!=iEliminar && j!=jEliminar){
                    submatriz[m][n] = matriz[i][j];
                    n++;
                    //cout << std::to_string(matriz[i][j]) + " ";                   //solo comprueba q sirva
                }
                //cout << " " << endl;
            }
            n=0;
            /*if(flag==true){                                                               //ESTO PORQUE COMO SE COME LA PRIMERA FILA, PARA QUE NO INICIE EN 1
                m++;
            } else if(flag==false && i!=0){
                m++;
            }*/
            if(i!=0){
                m++;
            }
        }
    /*cout << "" << endl;
    imprimirMatriz(submatriz, size-1);                                              //para corroborar
    cout << "" << endl;*/
    
    return submatriz;
}

int det(int** matriz, int size){
    
    if(size==2){
        int det=0;
        det = (matriz[0][0]*matriz[1][1]) - (matriz[1][0]*matriz[0][1]);
        return det;
    } else{
        int deter=0;
        for(int k=0; k<size; k++){
            
            if(k==0 || k%2==0){
                //cout << "par" << endl;
                //cout << std::to_string(matriz[0][k]) << endl;                     //para corroborar
                deter = deter + (matriz[0][k] * det( obtenerCofactor(matriz, size, 0, k, false), size-1 ));
            } else if(k%2==1){
                //cout << "impar" << endl;
                //cout << std::to_string(matriz[0][k]) << endl;                     //para corroborar
                deter = deter - (matriz[0][k] * det( obtenerCofactor(matriz, size, 0, k, false), size-1 ));
            }
            
        }
        
        return deter;
    }
}

int** transpuesta(int** matriz, int size){
    int** mAdjunta = NULL;
    if(matriz!=NULL){
        mAdjunta = provisionarMatriz2(size);

        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                mAdjunta[i][j] = pow(-1, (i+j))*det( obtenerCofactor(matriz, size, i, j, true), size-1 );
            }
        }
    }
    return mAdjunta;
}

int mult(int** matriz, int size, int numero){
    int reul=0;
    for(int i=0; i<size; i++){                                                  
        for(int j=0; j<size; j++){
            reul += matriz[i][j] * numero;
        }
    }
    return reul;
}

int** split(int** m1, int size){
    int** m2 = NULL;
    if(m1!=NULL){                                                               //SAFE CODE
        m2 = provisionarMatriz2(size);
        
        for(int i=0; i<size; i++){                                                  
            for(int j=0; j<size; j++){
                m2[i][j] = m1[j][i];
            }
        }
    }
    return m2;
}

double** inversa(int** matriz, int size, int det){
    double** inversa = NULL;
    if(matriz!=NULL){
        inversa = provisionarMatriz3(size);
        
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                inversa[i][j] = matriz[i][j]*(1/det);
                fraccion(matriz[i][j], det);                             //imprime la inversa en forma de fracción
                cout << "   ";
            }
            cout << "" << endl;
        }
    }
    return inversa;
}

void fraccion(int num, int denom){
    int mayor=0;
    if(num>denom){
        mayor = num;
    } else{
        mayor = denom;
    }
    if(mayor<0)
        mayor = mayor * -1;
    for(int n=2; n<=mayor; n++){
        if(num%n==0 && denom%n==0){                                             //si n es cociente de ambos...
            num = num/n;
            denom = denom/n;                                                    //...se simplifica
            n=1;                                                                //regreso el cociente para que a la otra vuelta regresa a 2 por si los numeros siguen sieendo divisibles
        }
        
    }
    if(num%denom==0){                                                           //si son divisibles, 4/2 = 2
        cout << std::to_string(num/denom);
    } else {
        if(num<0 && denom <0){                                                  //validaciones si ambos son negativos
            cout << std::to_string(-1*num) + "/" + std::to_string(-1*denom);
        }
        else{
            cout << std::to_string(num) + "/" + std::to_string(denom);
        }
    }
}

int** provisionarMatriz2(int size){
    int** matriz = NULL;
    if(size>1){                                                                 //SAFE CODE
        matriz = new int*[size];                                //filas

        for(int i=0; i < size; i++){
            matriz[i] = new int[size];                          //columnas
        }
        
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                //matriz[i][j] = (-9) + rand()%((9+1) - (-9));
                matriz[i][j] = 1;
            }
        }
    }
    return matriz;
}

double** provisionarMatriz3(int size){
    double** matriz = NULL;
    if(size>1){                                                                 //SAFE CODE
        matriz = new double*[size];                                //filas

        for(int i=0; i < size; i++){
            matriz[i] = new double[size];                          //columnas
        }
        
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                //matriz[i][j] = (-9) + rand()%((9+1) - (-9));
                matriz[i][j] = 1;
            }
        }
    }
    return matriz;
}

void liberarMatriz(int**& matrix, int size){
    if(matrix != NULL){                                                             //SAFE CODE
        for(int i = 0; i < size; i++){
            if(matrix[i] != NULL){
                delete[] matrix[i];
            }
            matrix[i] = NULL;
        }
    }
    
    if(matrix != NULL){
        delete[] matrix;
        matrix = NULL;
    }
}

void liberarMatriz(double**& matrix, int size){
    if(matrix != NULL){                                                             //SAFE CODE
        for(int i = 0; i < size; i++){
            if(matrix[i] != NULL){
                delete[] matrix[i];
            }
            matrix[i] = NULL;
        }
    }
    
    if(matrix != NULL){
        delete[] matrix;
        matrix = NULL;
    }
}
