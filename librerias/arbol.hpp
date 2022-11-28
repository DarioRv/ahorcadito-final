#include <iostream>
using namespace std;

typedef struct tnodoArbol *pnodoArbol;
typedef struct tnodoArbol{
    tjugador dato;
    pnodoArbol izquierda;
    pnodoArbol derecha;
};
void crearNodoArbol(pnodoArbol &nuevo, tjugador dato){
    nuevo = new tnodoArbol;
    if (nuevo != NULL){
        nuevo->dato = dato;
        nuevo->derecha = NULL;
        nuevo->izquierda = NULL;
    }
    else
        cout << "NO ES POSIBLE CREAR UN NODO" << endl;
}
void iniciarArbol(pnodoArbol &arbol){
    arbol = NULL;
}
void insertarNodo(pnodoArbol &arbol, pnodoArbol nuevo){
    pnodoArbol aux;
    if (arbol == NULL)
        arbol = nuevo;
    else{
        if (nuevo->dato.puntaje > arbol->dato.puntaje){
            aux = arbol;
            arbol = nuevo;
            arbol->izquierda = aux;
        }
        else{
            if (nuevo->dato.puntaje < arbol->dato.puntaje)
                insertarNodo(arbol->izquierda, nuevo);
            else
                insertarNodo(arbol->derecha, nuevo);
        }
    }
}