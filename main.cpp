#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "librerias/bicola.hpp"
#include "librerias/conjunto.hpp"
using namespace std;

typedef char tcadena[50];
typedef char tcadenaLarga[200];
typedef FILE *parchivo;
typedef struct tnodo *pnodo;
typedef struct tjugador{
    int id;
    tcadena apellido;
    tcadena nombre;
    tcadena nickname;
    int puntaje;
    int partidasGanadas;
};
typedef struct tpalabra{
    int id;
    tcadena palabra;
    int longitud;
    tcadenaLarga definicion;
};
typedef struct detallesJugador{
    tcadena nickname;
    int puntaje;
    int palabrasAdivinadas;
    int intentosRestantes;
};
typedef struct detallesPartida{
    detallesJugador jugador1;
    detallesJugador jugador2;
    int dificultad;
    pnodo listaPalabras;
};
const int CANT_PALABRAS = 6;
const int MAX = 30;
#include "librerias/listasSimples.hpp"
typedef tpalabra tcontenedor[MAX];
typedef struct tarreglo{
    tcontenedor datos;
    int ocupado;
};
typedef bool tcontenedor2[MAX];
typedef struct tarregloBool{
    tcontenedor2 datos;
    int ocupado;
};
void cargarDatosJugador(tjugador &j);
void cargarDatosPalabra(tpalabra &p);

void gestionJugadores(parchivo jugadores);
void gestionPalabras(parchivo palabras);
void jugar();
void rankingJugadores();

void registrarJugador(parchivo jugadores);
void consultarJugador(parchivo jugadores, tcadena nickname);
void modificarJugador(parchivo jugadores, tcadena nickname);
void listarJugadores(parchivo jugadores);
void eliminarJugador(parchivo jugadores, tcadena nickname);
bool verificarJugador(parchivo jugadores, tcadena nickname);

void registrarPalabra(parchivo palabras);
void consultarPalabra(parchivo palabras, tcadena palabra);
void listarPalabras(parchivo palabras);
bool verificarPalabra(parchivo palabras, tcadena palabra);

void elegirJugadores(detallesPartida &config, bool &jugadoresSeleccionados);
void seleccionarNivel(detallesPartida &config, bool &palabrasSeleccionadas);
void iniciarPartida(detallesPartida config);
void preSeleccionarPalabras(tarreglo &preListaPalabras, int criterio);
void seleccionarPalabras(pnodo &listaPalabras, tarreglo preListaPalabras);
void probarLetra(detallesPartida config, pnodo &palabraActual, tarregloBool &palabraOcultada);
void ocultarPalabra(pnodo palabraActual, tarregloBool &palabraOcultada);
bool verificarLetra(pnodo palabraActual, tarregloBool &palabraOcultada, char letra);
bool verificarPalabraAcertada(pnodo palabraActual, tarregloBool palabraOcultada);
void mostrarPalabra(pnodo palabraActual, tarregloBool palabraOcultada);
void controlPistas(detallesPartida &config, int jugadorActivo, pnodo palabraActual);
void controlPuntaje(detallesPartida &config, int jugadorActivo, pnodo palabraActual);
bool verificarPalindroma(pnodo palabraActual);
bool verificarCaracteresDistintos(pnodo palabraActual);

main(){
    int opcion;
    parchivo jugadores, palabras;
    srand(time(NULL));
    do{
        cout << "- - - AHORCADITO FINAL DESTINATION - - -" << endl;
        cout << "1. Gestion de Jugadores" << endl;
        cout << "2. Gestion de Palabras" << endl;
        cout << "3. Jugar" << endl;
        cout << "4. Ranking de Jugadores" << endl;
        cout << "5. Salir" << endl;
        cout << "Respuesta: ";
        cin >> opcion;
        switch (opcion){
            case 1:
                gestionJugadores(jugadores);
                break;
            case 2:
                gestionPalabras(palabras);
                break;
            case 3:
                jugar();
                break;
            case 5:
                cout << "FIN DEL JUEGO" << endl;
                break;
            default:
                break;
        }
        system("pause");
        system("cls");
    }while (opcion != 5);
}

/* - - MODULOS PRINCIPALES - - */
void gestionJugadores(parchivo jugadores){
    system("cls");
    int opcion;
    tcadena nickname;
    do{
        cout << "1. Agregar Jugador" << endl;
        cout << "2. Consultar Jugador" << endl;
        cout << "3. Modificar Jugador" << endl;
        cout << "4. Listar Jugadores" << endl;
        cout << "5. Eliminar Jugador" << endl;
        cout << "6. Salir" << endl;
        cout << "Respuesta: ";
        cin >> opcion;
        switch (opcion){
            case 1:
                registrarJugador(jugadores);
                break;
            case 2:
                cout << "Indique nickname: ";
                fflush(stdin);
                gets(nickname);
                consultarJugador(jugadores, nickname);
                break;
            case 3:
                cout << "Indique nickname: ";
                fflush(stdin);
                gets(nickname);
                modificarJugador(jugadores, nickname);
                break;
            case 4:
                listarJugadores(jugadores);
                break;
            case 5:
                cout << "Indique nickname: ";
                fflush(stdin);
                gets(nickname);
                eliminarJugador(jugadores,nickname);
                break;
            case 6:
                cout << "VOLVIENDO AL MENU ANTERIOR" << endl;
                break;
            default:
                cout << "OPCION NO VALIDA" << endl;
                break;
        }
        system("pause");
        system("cls");
    }while (opcion != 6);
}
void gestionPalabras(parchivo palabras){
    system("cls");
    int opcion;
    tcadena palabra;
    do{
        cout << "1. Agregar Palabra" << endl;
        cout << "2. Consultar Palabra" << endl;
        cout << "3. Listar Palabras" << endl;
        cout << "4. Salir" << endl;
        cout << "Respuesta: ";
        cin >> opcion;
        switch (opcion){
            case 1:
                registrarPalabra(palabras);
                break;
            case 2:
                cout << "Indique palabra: ";
                fflush(stdin);
                gets(palabra);
                consultarPalabra(palabras, palabra);
                break;
            case 3:
                listarPalabras(palabras);
                break;
            case 4:
                cout << "VOLVIENDO AL MENU ANTERIOR" << endl;
                break;
            default:
                break;
        }
        system("pause");
        system("cls");
    }while (opcion != 4);
}
void jugar(){
    system("cls");
    int opcion;
    detallesPartida config;
    bool jugadoresSeleccionados=false, palabrasCargadas=false;
    do{
        if (jugadoresSeleccionados == true){
            cout << "JUGADORES ACTUALES" << endl;
            cout << "Jugador 1: " << config.jugador1.nickname << endl;
            cout << "Jugador 2: " << config.jugador2.nickname << endl;
        }
        cout << "1. Elegir Jugadores" << endl;
        cout << "2. Seleccionar Nivel y Cargar Palabras" << endl;
        cout << "3. Iniciar Partida" << endl;
        cout << "4. Volver" << endl;
        cout << "Respuesta: ";
        cin >> opcion;
        switch (opcion){
            case 1:
                elegirJugadores(config, jugadoresSeleccionados);
                break;
            case 2:
                seleccionarNivel(config, palabrasCargadas);
                break;
            case 3:
                //if (jugadoresSeleccionados == true && palabrasCargadas == true)
                    iniciarPartida(config);
                //else
                    //cout << "Debe seleccionar jugadores y el nivel" << endl;
                break;
            case 4:
                cout << "Volviendo al menu anterior" << endl;
                break;
            default:
                cout << "OPCION NO VALIDA" << endl;
                break;
        }
        system("pause");
        system("cls");
    }while (opcion != 4);
}
void rankingJugadores();

/* - - Gestion de Jugadores - - */
void cargarDatosJugador(tjugador &j){
    cout << "ID: ";
    cin >> j.id;
    cout << "APELLIDO: ";
    fflush(stdin);
    gets(j.apellido);
    cout << "NOMBRE: ";
    fflush(stdin);
    gets(j.nombre);
    cout << "NICKNAME: ";
    fflush(stdin);
    gets(j.nickname);
    j.puntaje = 0;
    j.partidasGanadas = 0;
}
void registrarJugador(parchivo jugadores){
    tjugador j;
    int cantidad;
    jugadores = fopen("datos/jugadores.bat", "ab+");
    cout << "Cuantos jugadores registrara? ";
    cin >> cantidad;
    while (cantidad > 0){
        cargarDatosJugador(j);
        if (verificarJugador(jugadores, j.nickname) == false)
            fwrite(&j, sizeof(j), 1, jugadores);
        else
            cout << "ESTE JUGADOR YA ESTA REGISTRADO" << endl;
        cantidad -= 1;
    }
    fclose(jugadores);
}
void consultarJugador(parchivo jugadores, tcadena nickname){
    tjugador j;
    bool existe = false;
    jugadores = fopen("datos/jugadores.bat", "rb");
    while (!feof(jugadores)){
        fread(&j, sizeof(j), 1, jugadores);
        if (!feof(jugadores)){
            if (strcmp(j.nickname, nickname) == 0){
                existe = true;
                cout << "ID: " << j.id << endl;
                cout << "APELLIDO: " << j.apellido << endl;
                cout << "NOMBRE: " << j.nombre << endl;
                cout << "NICKNAME: " << j.nickname << endl;
                cout << "PUNTAJE: " << j.puntaje << endl;
                cout << "PARTIDAS GANADAS: " << j.partidasGanadas << endl;
            }
        }
    }
    if (existe == false)
        cout << "EL NICK PROPORCIONADO NO ESTA REGISTRADO \n DESCARTANDO DATOS INGRESADOS" << endl;
    fclose(jugadores);
}
void modificarJugador(parchivo jugadores, tcadena nickname){
    tjugador j;
    bool existe = false;
    jugadores = fopen("datos/jugadores.bat", "rb+");
    while (!feof(jugadores) && existe == false){
        fread(&j, sizeof(j), 1, jugadores);
        if (!feof(jugadores)){
            if (strcmp(j.nickname, nickname) == 0){
                existe = true;
                cargarDatosJugador(j);
                fseek(jugadores,-sizeof(j), 1);
                fwrite(&j, sizeof(j), 1, jugadores);
                cout << "DATOS MODIFICADOS!" << endl;
            }
        }
    }
    if (existe == false)
        cout << "EL NICK PROPORCIONADO NO ESTA REGISTRADO" << endl;
    fclose(jugadores);
}
void listarJugadores(parchivo jugadores){
    tjugador j;
    jugadores = fopen("datos/jugadores.bat", "rb");
    while (!feof(jugadores)){
        fread(&j, sizeof(j), 1, jugadores);
        if (!feof(jugadores)){
            cout << "ID: " << j.id << endl;
            cout << "APELLIDO: " << j.apellido << endl;
            cout << "NOMBRE: " << j.nombre << endl;
            cout << "NICKNAME: " << j.nickname << endl;
            cout << "PUNTAJE: " << j.puntaje << endl;
            cout << "PARTIDAS GANADAS: " << j.partidasGanadas << endl;
        }
    }
    fclose(jugadores);
}
void eliminarJugador(parchivo jugadores, tcadena nickname){
    tjugador j;
    parchivo aux;
    aux = fopen("datos/temporal.bat", "wb");
    jugadores = fopen("datos/jugadores.bat", "rb");
    if (jugadores != NULL){
        while (!feof(jugadores)){
            fread(&j, sizeof(j), 1, jugadores);
            if (strcmp(j.nickname, nickname) != 0 && !feof(jugadores)){
                fwrite(&j, sizeof(j), 1, aux);
            }
        }
        fclose(aux);
        fclose(jugadores);
        remove("datos/jugadores.bat");
        rename("datos/temporal.bat","datos/jugadores.bat");
        cout << j.nickname << " A SIDO ELIMINADO DE LA LISTA DE JUGADORES" << endl;
    }
}
bool verificarJugador(parchivo jugadores, tcadena nickname){
    tjugador j;
    bool existe = false;
    jugadores = fopen("datos/jugadores.bat", "rb");
    while (!feof(jugadores)){
        fread(&j, sizeof(j), 1, jugadores);
        if (!feof(jugadores)){
            if (strcmp(j.nickname, nickname) == 0)
                existe = true;
        }
    }
    fclose(jugadores);
    return existe;
}

/* - - Gestion de Palabras - - */
void cargarDatosPalabra(tpalabra &p){
    cout << "ID: ";
    cin >> p.id;
    cout << "PALABRA: ";
    fflush(stdin);
    gets(p.palabra);
    cout << "DEFINICION: ";
    fflush(stdin);
    gets(p.definicion);
    p.longitud = strlen(p.palabra);
}
void registrarPalabra(parchivo palabras){
    tpalabra p;
    palabras = fopen("datos/palabras.bat", "ab+");
    cargarDatosPalabra(p);
    if (verificarPalabra(palabras, p.palabra) == false)
        fwrite(&p, sizeof(p), 1, palabras);
    else
        cout << "ESTA PALABRA YA ESTA REGISTRADA \n DESCARTANDO DATOS" << endl;
    fclose(palabras);
}
void consultarPalabra(parchivo palabras, tcadena palabra){
    tpalabra p;
    bool existe = false;
    palabras = fopen("datos/palabras.bat", "rb");
    while (!feof(palabras)){
        fread(&p, sizeof(p), 1, palabras);
        if (!feof(palabras)){
            if (strcmp(p.palabra, palabra) == 0){
                existe = true;
                cout << "ID: " << p.id << endl;
                cout << "PALABRA: " << p.palabra << endl;
                cout << "DEFINICION: " << p.definicion << endl;
                cout << "LONGITUD: " << p.longitud << endl;
            }
        }
    }
    if (existe == false)
        cout << "LA PALABRA PROPORCIONADA NO ESTA REGISTRADA \n DESCARTANDO DATOS INGRESADOS" << endl;
    fclose(palabras);
}
void listarPalabras(parchivo palabras){
    tpalabra p;
    palabras = fopen("datos/palabras.bat", "rb");
    while (!feof(palabras)){
        fread(&p, sizeof(p), 1, palabras);
        if (!feof(palabras)){
            cout << "ID: " << p.id << endl;
            cout << "PALABRA: " << p.palabra << endl;
            cout << "DEFINICION: " << p.definicion << endl;
            cout << "LONGITUD: " << p.longitud << endl;
        }
    }
    fclose(palabras);
}
bool verificarPalabra(parchivo palabras, tcadena palabra){
    tpalabra p;
    bool existe = false;
    palabras = fopen("datos/palabras.bat", "rb");
    while (!feof(palabras)){
        fread(&p, sizeof(p), 1, palabras);
        if (!feof(palabras)){
            if (strcmp(p.palabra, palabra) == 0)
                existe = true;
        }
    }
    fclose(palabras);
    return existe;
}

/* - - Jugar - - */
void elegirJugadores(detallesPartida &config, bool &jugadoresSeleccionados){
    parchivo jugadores;
    cout << "Indique el nickname del primer jugador" << endl;
    fflush(stdin);
    gets(config.jugador1.nickname);
    cout << "Indique el nickname del segundo jugador" << endl;
    fflush(stdin);
    gets(config.jugador2.nickname);
    if (verificarJugador(jugadores, config.jugador1.nickname) == true && verificarJugador(jugadores, config.jugador2.nickname)){
        cout << "JUGADORES SELECCIONADOS" << endl;
        jugadoresSeleccionados = true;
        config.jugador1.puntaje = 0;
        config.jugador1.palabrasAdivinadas = 0;
        config.jugador1.intentosRestantes = 6;
        config.jugador2.puntaje = 0;
        config.jugador2.palabrasAdivinadas = 0;
        config.jugador2.intentosRestantes = 6;
    }
    else{
        cout << "ALGUNO DE LOS JUGADORES NO ESTA REGISTRADO, VUELVA A INTENTAR" << endl;
        jugadoresSeleccionados = false;
    }
}
void seleccionarNivel(detallesPartida &config, bool &palabrasSeleccionadas){
    system("cls");
    tarreglo preListaPalabras;
    preListaPalabras.ocupado = -1;
    do{
        cout << " - NIVELES DE DIFICULTAD - " << endl;
        cout << "1. Basico (palabras de 0-4 letras)" << endl;
        cout << "2. Intermedio (palabras de 0-6 letras)" << endl;
        cout << "3. Avanzado (palabras +6 letras)" << endl;
        cout << "Respuesta: ";
        cin >> config.dificultad;
        if (config.dificultad != 1 && config.dificultad != 2 && config.dificultad != 3)
            cout << "Ingrese un numero dentro del rango" << endl;
    }while (config.dificultad != 1 && config.dificultad != 2 && config.dificultad != 3);
    /* Seleccionar palabras */
    pnodo listaPalabras;
    iniciarLista(listaPalabras);
    int criterio;
    switch (config.dificultad){
        case 1:
            criterio = 4;
            break;
        case 2:
            criterio = 6;
            break;
        default:
            criterio = 99;
            break;
    }
    preSeleccionarPalabras(preListaPalabras, criterio);
    seleccionarPalabras(listaPalabras, preListaPalabras);
    config.listaPalabras = listaPalabras;
    palabrasSeleccionadas = true;
}
void iniciarPartida(detallesPartida config){
    system("cls");
    int opcion=0, jugadorActivo = 1;
    pnodo palabraActual;
    tarregloBool palabraOcultada;
    tcadena palabraArriesgada;
    bool tieneIntentos = true;
    for (palabraActual=config.listaPalabras; palabraActual!=NULL && opcion!=4; palabraActual = palabraActual->siguiente){
        bool estaAdivinada = false;
        ocultarPalabra(palabraActual, palabraOcultada);
        do{
            if (jugadorActivo == 1){
                cout << "JUGANDO: " << config.jugador1.nickname << endl;
                cout << "PUNTAJE: " << config.jugador2.puntaje << endl;
            }
            else{
                cout << "JUGANDO: " << config.jugador2.nickname << endl;
                cout << "PUNTAJE: " << config.jugador2.puntaje << endl;
            }
            cout << "PROGRESO: ";
            mostrarPalabra(palabraActual, palabraOcultada);
            cout << "1. Probar letra" << endl;
            cout << "2. Solicitar Pista" << endl;
            cout << "3. Arriesgar" << endl;
            cout << "4. Abandonar Partida" << endl;
            cout << "Respuesta: ";
            cin >> opcion;
            switch (opcion){
                case 1:
                    probarLetra(config, palabraActual, palabraOcultada);
                    break;
                case 2:
                    controlPistas(config, jugadorActivo, palabraActual);
                    break;
                case 3:
                    cout << "Ya la tienes? Dime la palabra: ";
                    fflush(stdin);
                    gets(palabraArriesgada);
                    if (strcmp(palabraArriesgada, palabraActual->dato.palabra) == 0){
                        cout << "Adivinaste la palabra!" << endl;
                        estaAdivinada = true;
                    }
                    else{
                        cout << "Esa no era la palabra, perdiste :(" << endl;
                    }
                    break;
                case 4:
                    cout << "Volviendo al menu anterior" << endl;
                    break;
                default:
                    cout << "OPCION NO VALIDA" << endl;
                    break;
            }
            if (estaAdivinada == true){
                controlPuntaje(config, jugadorActivo, palabraActual);
            }
            if (estaAdivinada == false)
                estaAdivinada = verificarPalabraAcertada(palabraActual, palabraOcultada);
            else{
                if (jugadorActivo == 1)
                    jugadorActivo = 2;
                else
                    jugadorActivo = 1;
            }
            system("pause");
            system("cls");
        }while (opcion != 4 && estaAdivinada != true);
    }
    cout << " - - - PARTIDA FINALIZADA - - - " << endl;
    cout << "GANADOR: " << endl;
    cout << "Puntaje jugador 1: " << endl;
    cout << "Puntaje jugador 2:" << endl;
}

void preSeleccionarPalabras(tarreglo &preListaPalabras, int criterio){
    parchivo palabras;
    tpalabra p;
    palabras = fopen("datos/palabras.bat", "rb");
    while (!feof(palabras)){
        fread(&p, sizeof(p), 1, palabras);
        if (!feof(palabras)){
            if (p.longitud <= criterio){
                preListaPalabras.ocupado += 1;
                preListaPalabras.datos[preListaPalabras.ocupado] = p;
            }
        }
    }
    fclose(palabras);
}
void seleccionarPalabras(pnodo &listaPalabras, tarreglo preListaPalabras){
    pnodo nuevo;
    int indice, cantidad = CANT_PALABRAS;
    while (cantidad > 0){
        indice =  1 + rand() % (preListaPalabras.ocupado - 0);
        crearNodo(nuevo, preListaPalabras.datos[indice]);
        agregarInicio(listaPalabras, nuevo);
        cantidad -= 1;
    }
    mostrarLista(listaPalabras);
}
void probarLetra(detallesPartida config, pnodo &palabraActual, tarregloBool &palabraOcultada){
    char letraJugada;
    cout << "La palabra es: " << palabraActual->dato.palabra << endl;
    //mostrarPalabra(palabraActual, palabraOcultada);
    cout << "Introduce una letra: ";
    cin >> letraJugada;
    if (verificarLetra(palabraActual, palabraOcultada, letraJugada) == true){
        cout << "Genial, acertaste una letra" << endl;
    }
    else{
        cout << "No acertaste una letra :(" << endl;
    }
    if (verificarPalabraAcertada(palabraActual, palabraOcultada) == true){
        cout << "Acertaste la palabra" << endl;
    }
}
void ocultarPalabra(pnodo palabraActual, tarregloBool &palabraOcultada){
    palabraOcultada.ocupado = -1;
    if (palabraActual != NULL){
        for (int i=0; i<palabraActual->dato.longitud; i+=1){
            palabraOcultada.ocupado += 1;
            palabraOcultada.datos[palabraOcultada.ocupado] = false;
        }
    }
}
bool verificarLetra(pnodo palabraActual, tarregloBool &palabraOcultada, char letra){
    int i;
    bool pertenece = false;
    for (i=0; i<=palabraOcultada.ocupado; i+=1){
        if (tolower(letra) == palabraActual->dato.palabra[i] || toupper(letra) == palabraActual->dato.palabra[i]){
            palabraOcultada.datos[i] = true;
            pertenece = true;
        }
    }
    return pertenece;
}
bool verificarPalabraAcertada(pnodo palabraActual, tarregloBool palabraOcultada){
    int i;
    bool acerto = true;
    for (i=0; i<=palabraOcultada.ocupado; i+=1){
        if (palabraOcultada.datos[i] != true){
            acerto = false;
        }
    }
    return acerto;
}
void mostrarPalabra(pnodo palabraActual, tarregloBool palabraOcultada){
    int i;
    for (i=0; i<= palabraOcultada.ocupado; i+=1){
        if (palabraOcultada.datos[i] == true)
            cout << palabraActual->dato.palabra[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}
void controlPistas(detallesPartida &config, int jugadorActivo, pnodo palabraActual){
    int opcion;
    cout << "1. Te digo la primera letra de la palabra? (-5 puntos)" << endl;
    cout << "2. Te digo la definicion de la palabra? (-10 puntos)" << endl;
    cout << "Respuesta: ";
    cin >> opcion;
    switch (opcion){
        case 1:
            cout << "PISTA: " << palabraActual->dato.palabra[0] << endl;
            if (jugadorActivo == 1)
                config.jugador1.puntaje -= 5;
            else
                config.jugador2.puntaje -= 5;
            cout << "Se te descontaron 5 puntos" << endl;
            break;
        case 2:
            cout << "PISTA: " << palabraActual->dato.definicion << endl;
            if (jugadorActivo == 1)
                config.jugador1.puntaje -= 10;
            else
                config.jugador2.puntaje -= 10;
            cout << "Se te descontaron 10 puntos" << endl;
            break;
        default:
            cout << "OPCION NO VALIDA, VOLVIENDO" << endl;
            break;
    }
}
void controlPuntaje(detallesPartida &config, int jugadorActivo, pnodo palabraActual){
    if (jugadorActivo == 1){
        if (verificarPalindroma(palabraActual) == true){
            config.jugador1.puntaje += palabraActual->dato.longitud*(3*2);
            cout << "La palabra es palindroma, obtienes un bonus de x2" << endl;
        }
        else{
            if (verificarCaracteresDistintos(palabraActual) == true){
                config.jugador1.puntaje += palabraActual->dato.longitud*(3*3);
                cout << "La palabra tiene todos sus caracteres distintos, obtienes un bonus de x3" << endl;
            }
            else{
                config.jugador1.puntaje += palabraActual->dato.longitud*3;
                cout << "Genial, adivinaste la palabra. Obtienes " << palabraActual->dato.longitud*3 << " puntos" << endl;
            }
        }
        config.jugador1.palabrasAdivinadas += 1;
        if (config.jugador1.palabrasAdivinadas == 3){
            config.jugador1.puntaje += 15;
            cout << "Genial, adivinaste las 3 palabras. Obtienes un bonus 15 puntos" << endl;
        }
        cout << "Tienes un puntaje final de " << config.jugador1.puntaje << " puntos" << endl;
    }
    else{
        if (verificarPalindroma(palabraActual) == true){
            config.jugador2.puntaje += palabraActual->dato.longitud*(3*2);
            cout << "La palabra es palindroma, obtienes un bonus de x2" << endl;
        }
        else{
            if (verificarCaracteresDistintos(palabraActual) == true){
                config.jugador2.puntaje += palabraActual->dato.longitud*(3*3);
                cout << "La palabra tiene todos sus caracteres distintos, obtienes un bonus de x3" << endl;
            }
            else{
                config.jugador2.puntaje += palabraActual->dato.longitud*3;
                cout << "Genial, adivinaste la palabra. Obtienes " << palabraActual->dato.longitud*3 << " puntos" << endl;
            }
        }
        config.jugador2.palabrasAdivinadas += 1;
        if (config.jugador2.palabrasAdivinadas == 3){
            config.jugador2.puntaje += 15;
            cout << "Genial, adivinaste las 3 palabras. Obtienes un bonus 15 puntos" << endl;
        }
        cout << "Tienes un puntaje final de " << config.jugador2.puntaje << " puntos" << endl;
    }
}
bool verificarPalindroma(pnodo palabraActual){
    tcola bicola;
    iniciarCola(bicola);
    bool esPalindroma = true;
    int i;
    for (i=0; i<palabraActual->dato.longitud; i+=1){
        agregarCola(bicola, palabraActual->dato.palabra[i]);
    }
    while(colaVacia(bicola) == false && esPalindroma == true){
        if (quitarCola(bicola, true) != quitarCola(bicola, false)){
            esPalindroma = false;
        }
    }
    return esPalindroma;
}
bool verificarCaracteresDistintos(pnodo palabraActual){
    bool tieneDistintosCaracteres = true;
    tconjunto caracteres;
    crearConjunto(caracteres);
    int i;
    for (i=0; i<palabraActual->dato.longitud && tieneDistintosCaracteres == true; i+=1){
        agregarElementos(caracteres, palabraActual->dato.palabra[i]);
    }
    if (strcmp(caracteres.datos, palabraActual->dato.palabra))
        tieneDistintosCaracteres = false;
    return tieneDistintosCaracteres;
}
