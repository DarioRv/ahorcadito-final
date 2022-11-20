const int MAX_CONJ = 50;
typedef char tcontenedorConjunto[MAX_CONJ];
typedef struct tconjunto{
    tcontenedorConjunto datos;
    int ocupado;
};
void crearConjunto(tconjunto &c){
    c.ocupado = -1;
}
bool pertenencia(tconjunto c, char elemento){
    bool existe = false;
    int i;
    for (i = 0; i <= c.ocupado; i+=1)
        if (c.datos[i] == elemento)
            existe = true;
    return existe;
}
void agregarElementos(tconjunto &c, char nuevo){
    if (c.ocupado != MAX_CONJ-1){
        if (pertenencia(c, nuevo) == false){
            c.ocupado += 1;
            c.datos[c.ocupado] = nuevo;
        }
    }
}