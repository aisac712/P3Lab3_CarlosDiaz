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

int det(int**, int);

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
    if(matriz==sub){
        imprimirMatriz(sub, size);
    } else {
        imprimirMatriz(sub, size-1);
    }
    
    cout << "Su determinante: ";
    int deter = det(matriz, size);
    cout << deter << endl;
    
    /*liberarMatriz(matriz, size);
    if(matriz==sub){
        liberarMatriz(sub, size);
    } else {
        liberarMatriz(sub, size-1);
    }*/
    
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

int** obtenerCofactor(int** matriz, int size, int x, int y){
    //if(size==3){
        //return matriz;
    //} else {
    int** submatriz = provisionarMatriz2(size-1);
    int iEliminar=x, jEliminar=y;
    int m=0, n=0;
    
    //for(int h=0; h<size; h++){
        //int m=0, n=0;
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
        //jEliminar++;
    //}
    /*cout << "" << endl;
    imprimirMatriz(submatriz, size-1);                                              //para corroborar
    cout << "" << endl;*/
    
    return submatriz;
    //}
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
                deter = deter + (matriz[0][k] * det( obtenerCofactor(matriz, size, 0, k), size-1 ));
            } else if(k%2==1){
                //cout << "impar" << endl;
                //cout << std::to_string(matriz[0][k]) << endl;                     //para corroborar
                deter = deter - (matriz[0][k] * det( obtenerCofactor(matriz, size, 0, k), size-1 ));
            }
            
        }
        
        return deter;
    }
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
