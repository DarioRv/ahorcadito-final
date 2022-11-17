#include <iostream>
using namespace std;

typedef struct tnodo *pnodo;
typedef struct tnodo{
    int dato;
    pnodo izquierda;
    pnodo derecha;
};
void crearNodoArbol(pnodo &nuevo){
    nuevo = new tnodo;
    if (nuevo != NULL){
        cout << "Ingresar dato: ";
        cin >> nuevo->dato;
        nuevo->derecha = NULL;
        nuevo->izquierda = NULL;
    }
    else
        cout << "NO ES POSIBLE CREAR UN NODO" << endl;
}
void iniciarArbol(pnodo &arbol){
    arbol = NULL;
}
void insertarNodo(pnodo &arbol, pnodo nuevo){
    if (arbol == NULL)
        arbol = nuevo;
    else{
        if (nuevo->dato < arbol->dato)
            insertarNodo(arbol->izquierda, nuevo);
        else
            insertarNodo(arbol->derecha, nuevo);
    }
}