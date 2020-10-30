//#include <cstdlib>
#include <iostream>
#include<stdlib.h>

//using namespace std;
using std::cout;
using std::cin;
using std::endl;

/*
 * 
 */
//PROTOTIPOS DE FUNCIONES
int** provisionarMatriz(int);
int** provisionarMatriz2(int);
void liberarMatriz(int**&, int);

void imprimirMatriz(int**, int);

int** obtenerSubconjunta(int**, int);

int main(int argc, char** argv) {
    
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
    
    cout << "La subconjunta: " << endl;
    int** sub = obtenerSubconjunta(matriz, size);
    imprimirMatriz(sub, size-1);
    
    //liberarMatriz(matriz, size);
    //liberarMatriz(sub, size-1);
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
                matriz[i][j] = (-9) + rand()%((9+1) - (-9));
                //matriz[i][j] = 1;
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
    int** submatriz = provisionarMatriz2(size-1);
    int iEliminar=0, jEliminar=0;
    int m=0, n=0;
    
    for(int h=0; h<size; h++){
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
