#include <iostream>
using namespace std;

const int MAX = 15;
typedef struct tnodo *pnodo;
typedef struct tnodo{
    float dato;
    pnodo siguiente;
    pnodo anterior;
};
typedef struct tcola{
    pnodo frente;
    pnodo final;
    int contador;
};

void crearNodoBicola(pnodo &nuevo, int dato){
    nuevo = new tnodo;
    if (nuevo != NULL){
        nuevo->dato = dato;
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
    }
    else
        cout << "ERROR" << endl;
}
void iniciarCola(tcola &cola){
    cola.frente = NULL;
    cola.final = NULL;
}
bool colaVacia(tcola cola){
    return cola.contador == 0;
}
bool colaLlena(tcola cola){
    return cola.contador == MAX;
}
void agregarCola(tcola &cola, int nuevoDato){
    if (colaLlena(cola) == true){
        cout << "COLA LLENA!" << endl;
    }
    else{
        pnodo nuevo;
        crearNodoBicola(nuevo, nuevoDato);
        if (cola.frente == NULL){
            cola.frente = nuevo;
            cola.final = nuevo;
        }
        else{
            nuevo->anterior = cola.final;
            cola.final->siguiente = nuevo;
            cola.final = nuevo;
        }
        cola.contador += 1;
    }
}
pnodo quitarCola(tcola &cola, bool quitarFrente){
    pnodo extraido, i;
    if (colaVacia(cola) == true)
        extraido = NULL;
    else{
        if (quitarFrente == true){
            if (cola.frente == cola.final){
                extraido = cola.frente;
                cola.frente = NULL;
                cola.final = NULL;
            }
            else{
                extraido = cola.frente;
                cola.frente = cola.frente->siguiente;
                cola.frente->anterior = NULL;
                extraido->siguiente = NULL;
            }
        }
        else{
            if (cola.final == cola.frente){
                extraido = cola.frente;
                cola.frente = NULL;
                cola.final = NULL;
            }
            else{
                extraido = cola.final->anterior;
                cola.final = cola.final->anterior;
                cola.final->siguiente = NULL;
                extraido->anterior = NULL;
            }
        }
        cola.contador -= 1;
    }
    return extraido;
}
pnodo consultarFrente(tcola cola){
    pnodo frente;
    if (cola.frente != NULL)
        frente = cola.frente;
    else
        frente = NULL;
    return frente;
}
pnodo consultarFinal(tcola cola){
    pnodo final;
    if (cola.final != NULL)
        final = cola.final;
    else
        final = NULL;
    return final;
}