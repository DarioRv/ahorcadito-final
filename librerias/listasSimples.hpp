#include <iostream>
using namespace std;

typedef struct tnodo{
    tpalabra dato;
    pnodo siguiente;
};
void iniciarLista(pnodo &lista){
    lista = NULL;
}
void crearNodo(pnodo &nuevo, tpalabra palabra){
    nuevo = new tnodo;
    if (nuevo != NULL){
        nuevo->dato = palabra;
        nuevo->siguiente = NULL;
    }
}
void agregarInicio(pnodo &lista, pnodo nuevo){
    if (lista == NULL){
        lista = nuevo;
    }
    else{
        nuevo->siguiente = lista;
        lista = nuevo;
    }
}
void mostrarLista(pnodo lista){
    pnodo i;
    if (lista != NULL){
        for (i=lista; i != NULL; i = i->siguiente){
            cout << " - PALABRA - " << endl;
            cout << "PALABRA: " << i->dato.palabra << endl;
            cout << "SIGNIFICADO: " << i->dato.definicion << endl;
        }
    }
}