#include <iostream>
using namespace std;

typedef struct tnodo *pnodo;
typedef struct tnodo{
    tpalabra dato;
    pnodo anterior;
    pnodo siguiente;
};
typedef struct tlista{
    pnodo inicio;
    pnodo final;
};
void iniciarLista(tlista &lista){
    lista.inicio = NULL;
    lista.final = NULL;
    cout << "LISTA INICIADA!" << endl;
}
void crearNodo(pnodo &nuevo, tpalabra palabra){
    nuevo = new tnodo;
    if (nuevo != NULL){
        nuevo->dato = palabra;
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
    }
    else
        cout << "MEMORIA INSUFICIENTE!" << endl;
}
void agregarInicio(tlista &lista, pnodo nuevo){
    if (lista.inicio == NULL){
        lista.inicio = nuevo;
        lista.final = nuevo;
    }
    else{
        lista.inicio->anterior = nuevo;
        nuevo->siguiente = lista.inicio;
        lista.inicio = nuevo;
    }
    cout << "NODO AGREGADO AL INICIO!" << endl;
}
void agregarFinal(tlista &lista, pnodo nuevo){
    if (lista.inicio == NULL){
        lista.inicio = nuevo;
        lista.final = nuevo;
    }
    else{
        lista.final->siguiente = nuevo;
        nuevo->anterior = lista.final;
        lista.final = nuevo;
    }
    cout << "NODO AGREGADO AL FINAL!" << endl;

}
void mostrarLista(tlista lista){
    pnodo i;
    if (lista.inicio != NULL){
        for (i=lista.inicio; i != NULL; i = i->siguiente){
            cout << " - PALABRA - " << endl;
            cout << "PALABRA: " << i->dato.palabra << endl;
            cout << "SIGNIFICADO: " << i->dato.definicion << endl;
        }
    }
    else
        cout << "LISTA VACIA!" << endl;
}