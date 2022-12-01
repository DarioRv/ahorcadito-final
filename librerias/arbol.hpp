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
            if (nuevo->dato.puntaje < arbol->dato.puntaje)
                insertarNodo(arbol->izquierda, nuevo);
            else
                insertarNodo(arbol->derecha, nuevo);
    }
}
void mostrarArbol(pnodoArbol arbol, int orden){
    if (orden == 1){
        if (arbol != NULL){
            mostrarArbol(arbol->izquierda, orden);
            if (arbol->dato.partidasGanadas > 0)
                cout << arbol->dato.id << "     " << arbol->dato.nickname << "          " << arbol->dato.partidasGanadas << "        " << arbol->dato.puntaje << endl;
            mostrarArbol(arbol->derecha, orden);
        }
    }
    else{
        if (arbol != NULL){
            mostrarArbol(arbol->derecha, orden);
            if (arbol->dato.partidasGanadas > 0)
                cout << arbol->dato.id << "     " << arbol->dato.nickname << "          " << arbol->dato.partidasGanadas << "        " << arbol->dato.puntaje << endl;
            mostrarArbol(arbol->izquierda, orden);
        }
    }
}
