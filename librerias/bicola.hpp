#include <iostream>
using namespace std;

const int MAX_COLA = 20;
typedef char tcontenedorChar[MAX_COLA];
typedef struct tcola{
    tcontenedorChar datos1;
    tcontenedorChar datos2;
    int frente;
    int final;
};
void iniciarCola(tcola &cola){
    cola.frente = 0; // frente
    cola.final = 0; // final
}
int siguiente(int indice){
    if (indice == MAX_COLA*2-1)
        indice = 0;
    else
        indice += 1;
    return indice;
}
int anterior(int indice){
    if (indice == 0)
        indice = MAX_COLA*2-1;
    else
        indice -= 1;
    return indice;
}
bool colaVacia(tcola cola){
    return cola.frente == cola.final;
}
bool colaLlena(tcola cola){
    return siguiente(cola.final) == cola.frente;
}
void agregarCola(tcola &cola, int nuevo){
    if (colaLlena(cola) == true){
        cout << "COLA LLENA!" << endl;
    }
    else{
        cola.final = siguiente(cola.final);
        if (cola.final < MAX_COLA){
            cola.datos1[cola.final] = nuevo;
        }
        else{
            cola.datos2[cola.final%MAX_COLA] = nuevo;
        }
    }
}
char quitarCola(tcola &cola, bool quitarFrente){
    int extraido;
    if (colaVacia(cola) == true){
        extraido = -404;
    }
    else{
        if (quitarFrente == true){
            cola.frente = siguiente(cola.frente);
            if (cola.frente < MAX_COLA)
                extraido = cola.datos1[cola.frente];
            else
                extraido = cola.datos2[cola.frente%MAX_COLA];
        }
        else{
            if (cola.final < MAX_COLA)
                extraido = cola.datos1[cola.final];
            else
                extraido = cola.datos2[cola.final%MAX_COLA];
            cola.final = anterior(cola.final);
        }
    }
    return extraido;
}