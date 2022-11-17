#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;

typedef char tcadena[50];
typedef char tcadenaLarga[100];
typedef FILE *parchivo;
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
#include "librerias/listasSimples.hpp"
typedef struct detallesPartida{
    tcadena jugador1;
    tcadena jugador2;
    int dificultad;
};
const int CANT_PALABRAS = 6;
const int MAX = 30;
typedef tpalabra tcontenedor[MAX];
typedef struct tarreglo{
    tcontenedor datos;
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
void seleccionarPalabras(tlista &listaPalabras, tarreglo preListaPalabras);

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
    int opcion;
    detallesPartida config;
    bool jugadoresSeleccionados=false, palabrasCargadas=false;
    do{
        if (jugadoresSeleccionados == true){
            cout << "JUGADORES ACTUALES" << endl;
            cout << "Jugador 1: " << config.jugador1 << endl;
            cout << "Jugador 2: " << config.jugador2 << endl;
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
                if (jugadoresSeleccionados == true && palabrasCargadas == true)
                    iniciarPartida(config);
                else
                    cout << "Debe seleccionar jugadores y el nivel" << endl;
                break;
            case 4:
                cout << "Volviendo al menu anterior" << endl;
                break;
            default:
                cout << "OPCION NO VALIDA" << endl;
                break;
        }
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
    gets(config.jugador1);
    cout << "Indique el nickname del segundo jugador" << endl;
    fflush(stdin);
    gets(config.jugador2);
    if (verificarJugador(jugadores, config.jugador1) == true && verificarJugador(jugadores, config.jugador2)){
        cout << "JUGADORES SELECCIONADOS" << endl;
        jugadoresSeleccionados = true;
    }
    else{
        cout << "ALGUNO DE LOS JUGADORES NO ESTA REGISTRADO, VUELVA A INTENTAR" << endl;
        jugadoresSeleccionados = false;
    }
}
void seleccionarNivel(detallesPartida &config, bool &palabrasSeleccionadas){
    tarreglo preListaPalabras;
    preListaPalabras.ocupado = -1;
    do{
        cout << " - NIVELES DE DIFICULTAD - " << endl;
        cout << "1. Basico" << endl;
        cout << "2. Intermedio" << endl;
        cout << "3. Avanzado" << endl;
        cout << "Respuesta: ";
        cin >> config.dificultad;
        if (config.dificultad != 1 && config.dificultad != 2 && config.dificultad != 3)
            cout << "Ingrese un numero dentro del rango" << endl;
    }while (config.dificultad != 1 && config.dificultad != 2 && config.dificultad != 3);
    /* Seleccionar palabras */
    tlista listaPalabras;
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
    palabrasSeleccionadas = true;
}
void iniciarPartida(detallesPartida config){

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
void seleccionarPalabras(tlista &listaPalabras, tarreglo preListaPalabras){
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