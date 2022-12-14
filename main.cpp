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
#include "librerias/arbol.hpp"
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
};
typedef struct detallesPartida{
    detallesJugador jugador1;
    detallesJugador jugador2;
    int dificultad;
    pnodo listaPalabras;
    int jugadorActivo;
    bool estaAdivinada;
    int intentosRestantes;
};
const int CANT_PALABRAS = 6;
const int MAX = 30;
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
typedef tjugador tcontenedorJugadores[100];
typedef struct tarregloJugadores{
    tcontenedorJugadores datos;
    int ocupado;
};
#include "librerias/listasSimples.hpp"
void cargarDatosJugador(tjugador &j);
void cargarDatosPalabra(tpalabra &p);

void gestionJugadores(parchivo jugadores);
void gestionPalabras(parchivo palabras);
void jugar(parchivo jugadores);
void rankingJugadores(parchivo jugadores);

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
void iniciarPartida(detallesPartida config, parchivo jugadores);
void preSeleccionarPalabras(tarreglo &preListaPalabras, int criterio);
void seleccionarPalabras(pnodo &listaPalabras, tarreglo preListaPalabras);
void probarLetra(detallesPartida &config, pnodo &palabraActual, tarregloBool &palabraOcultada);
void ocultarPalabra(pnodo palabraActual, tarregloBool &palabraOcultada);
bool verificarLetra(pnodo palabraActual, tarregloBool &palabraOcultada, char letra);
bool verificarPalabraAcertada(pnodo palabraActual, tarregloBool palabraOcultada);
void mostrarPalabra(pnodo palabraActual, tarregloBool palabraOcultada);
void controlPistas(detallesPartida &config, int jugadorActivo, pnodo palabraActual);
void arriesgarSolucion(detallesPartida &config, pnodo palabraActual);
void controlPuntaje(detallesPartida &config, int jugadorActivo, pnodo palabraActual);
bool verificarPalindroma(pnodo palabraActual);
bool verificarCaracteresDistintos(pnodo palabraActual);
void guardarRegistro(parchivo jugadores, detallesJugador jugadorGanador, bool gano);

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
                jugar(jugadores);
                break;
            case 4:
                rankingJugadores(jugadores);
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
                if (verificarJugador(jugadores, nickname))
                    modificarJugador(jugadores, nickname);
                else
                    cout << "EL NICK PROPORCIONADO NO ESTA REGISTRADO" << endl;
                break;
            case 4:
                listarJugadores(jugadores);
                break;
            case 5:
                cout << "Indique nickname: ";
                fflush(stdin);
                gets(nickname);
                if (verificarJugador(jugadores, nickname))
                    eliminarJugador(jugadores,nickname);
                else
                    cout << "EL NICK PROPORCIONADO NO ESTA REGISTRADO" << endl;
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
void jugar(parchivo jugadores){
    /*
    Procedimiento en donde muestro el men?? para jugar
    incluyendo controles para verificar si los jugadores
    fueron seleccionados y si las palabras tambi??n fueron
    cargadas, adem??s declaro mi registro "config" la cual
    me ayudar?? a llevar todos los datos de la partida.
    */
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
                if (jugadoresSeleccionados == true && palabrasCargadas == true){
                    iniciarPartida(config, jugadores);
                    palabrasCargadas = false;
                }
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
        system("pause");
        system("cls");
    }while (opcion != 4);
}
void rankingJugadores(parchivo jugadores){
    /*
    Aqui genero el arbol obteniendo la lista de todos
    los jugadores y creo la estructura del arbol para
    poder representarla
    */
    int orden;
    pnodoArbol nuevo, arbol;
    iniciarArbol(arbol);
    tarregloJugadores listaJugadores;
    listaJugadores.ocupado = -1;
    tjugador j;
    jugadores = fopen("datos/jugadores.bat", "rb");
    if (jugadores != NULL){
        while (!feof(jugadores)){
            fread(&j, sizeof(j), 1, jugadores);
            if (!feof(jugadores)){
                crearNodoArbol(nuevo, j);
                insertarNodo(arbol, nuevo);
            }
        }
    }
    fclose(jugadores);
    cout << "Como desea mostrar el orden?" << endl;
    cout << "1. Descendente" << endl;
    cout << "2. Ascendente" << endl;
    cin >> orden;
    if (orden == 1 || orden == 2){
        cout << "ID     NICKNAME        PG      PUNTAJE" << endl;
        mostrarArbol(arbol, orden);
    }
    else
        cout << "Ingrese un valor valido" << endl;
}

/* - - Gestion de Jugadores - - */
void cargarDatosJugador(tjugador &j){
    /*
    Procedimiento encargado de pedir los datos
    necesarios para el registro del jugador
    */
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
    /*
    Procedimiento encargado de registrar la carga
    de datos de un jugador en el archivo binario de jugadores.
    */
    tjugador j;
    /*Devolver el id*/
    int ultimoId;
    jugadores = fopen("datos/jugadores.bat", "rb");
    if (jugadores != NULL){
        while(!feof(jugadores)){
            fread(&j, sizeof(j), 1, jugadores);
            ultimoId = j.id;
        }
    }
    else{
        jugadores = fopen("datos/jugadores.bat", "wb");
        ultimoId = 0;
    }
    fclose(jugadores);
    /*Carga de datos*/
    int cantidad;
    jugadores = fopen("datos/jugadores.bat", "ab+");
    cout << "Cuantos jugadores registrara? ";
    cin >> cantidad;
    while (cantidad > 0){
        cargarDatosJugador(j);
        j.id = ultimoId + 1;
        if (verificarJugador(jugadores, j.nickname) == false)
            fwrite(&j, sizeof(j), 1, jugadores);
        else
            cout << "ESTE JUGADOR YA ESTA REGISTRADO" << endl;
        cantidad -= 1;
    }
    fclose(jugadores);
}
void consultarJugador(parchivo jugadores, tcadena nickname){
    /*
    Procedimiento que dado un nickname recibido por parametro
    devuelve toda la informaci??n relacionada a este.
    */
    tjugador j;
    bool existe = false;
    jugadores = fopen("datos/jugadores.bat", "rb");
    if (jugadores != NULL){
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
    }
    if (existe == false)
        cout << "EL NICK PROPORCIONADO NO ESTA REGISTRADO" << endl;
    fclose(jugadores);
}
void modificarJugador(parchivo jugadores, tcadena nickname){
    /*
    Procedimiento que dado un nickname permite modificar la
    informaci??n sujeta a este, los campos que se pueden
    modificar son nombre y apellido.
    */
    tjugador j;
    bool existe = false;
    jugadores = fopen("datos/jugadores.bat", "rb+");
    if (jugadores != NULL){
        while (!feof(jugadores) && existe == false){
            fread(&j, sizeof(j), 1, jugadores);
            if (!feof(jugadores)){
                if (strcmp(j.nickname, nickname) == 0){
                    existe = true;
                    cout << "Ingrese el nuevo nombre: ";
                    fflush(stdin);
                    gets(j.nombre);
                    cout << "Ingrese el nuevo apellido: ";
                    fflush(stdin);
                    gets(j.apellido);
                    fseek(jugadores,-sizeof(j), 1);
                    fwrite(&j, sizeof(j), 1, jugadores);
                    cout << "DATOS MODIFICADOS!" << endl;
                }
            }
        }
    }
    if (existe == false)
        cout << "EL NICK PROPORCIONADO NO ESTA REGISTRADO" << endl;
    fclose(jugadores);
}
void listarJugadores(parchivo jugadores){
    /*
    Procedimiento que dado el archivo de datos de las jugadores, 
    lista cada uno de los registrados mostrando su informaci??n.
    */
    tjugador j;
    jugadores = fopen("datos/jugadores.bat", "rb");
    if (jugadores != NULL){
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
    }
    fclose(jugadores);
}
void eliminarJugador(parchivo jugadores, tcadena nickname){
    /*
    Procedimiento que dado un nickname busca por una coincidencia
    del mismo en el archivo de datos de jugadores, si hay coincidencia
    se procede a la baja del registro del jugador que posea el respectivo
    nickname, de lo contrario no se produce ning??n cambio.
    */
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
        if (remove("datos/jugadores.bat") == 0){
            rename("datos/temporal.bat","datos/jugadores.bat");
            cout << j.nickname << " A SIDO ELIMINADO DE LA LISTA DE JUGADORES" << endl;
        }
        else{
            cout << "PROBLEMAS, INTENTE MAS TARDE" << endl;
        }
    }
}
bool verificarJugador(parchivo jugadores, tcadena nickname){
    /*
    Funci??n que dado un nickname determina si existe alg??n registro
    del mismo en el archivo de datos de jugadores, retornando
    verdadero en caso de coincidencia o falso en caso contrario.
    */
    tjugador j;
    bool existe = false;
    jugadores = fopen("datos/jugadores.bat", "rb");
    if (jugadores != NULL){
        while (!feof(jugadores)){
            fread(&j, sizeof(j), 1, jugadores);
            if (!feof(jugadores)){
                if (strcmp(j.nickname, nickname) == 0)
                    existe = true;
            }
        }
    }
    fclose(jugadores);
    return existe;
}

/* - - Gestion de Palabras - - */
void cargarDatosPalabra(tpalabra &p){
    /*
    Procedimiento que permite la carga de datos
    de una palabra que se quiera registrar.
    */
    cout << "PALABRA: ";
    fflush(stdin);
    gets(p.palabra);
    cout << "DEFINICION: ";
    fflush(stdin);
    gets(p.definicion);
    p.longitud = strlen(p.palabra);
}
void registrarPalabra(parchivo palabras){
    /*
    Procedimiento que permite registrar la carga
    de datos de una palabra en el archivo de
    datos de palabras.
    */
    tpalabra p;
    /*Devolver el id*/
    int ultimoId;
    palabras = fopen("datos/palabras.bat", "rb");
    if (palabras != NULL){
        while(!feof(palabras)){
            fread(&p, sizeof(p), 1, palabras);
            ultimoId = p.id;
        }
    }
    else{
        palabras = fopen("datos/palabras.bat", "wb");
        ultimoId = 0;
    }
    fclose(palabras);
    /*Carga de datos*/
    palabras = fopen("datos/palabras.bat", "ab+");
    cargarDatosPalabra(p);
    p.id = ultimoId + 1;
    if (verificarPalabra(palabras, p.palabra) == false)
        fwrite(&p, sizeof(p), 1, palabras);
    else
        cout << "ESTA PALABRA YA ESTA REGISTRADA \n DESCARTANDO DATOS" << endl;
    fclose(palabras);
}
void consultarPalabra(parchivo palabras, tcadena palabra){
    /*
    Procedimiento que dado una palabra verifica si esta esta
    registrada en el archivo de datos de palabras, si hay coincidencia
    se muestra la informaci??n de dicha palabra. Esta informaci??n es
    sobre la definici??n de la misma, la longitud y su id.
    */
    tpalabra p;
    bool existe = false;
    palabras = fopen("datos/palabras.bat", "rb");
    if (palabras != NULL){
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
    }
    if (existe == false)
        cout << "LA PALABRA PROPORCIONADA NO ESTA REGISTRADA" << endl;
    fclose(palabras);
}
void listarPalabras(parchivo palabras){
    /*
    Procedimiento que muestra la informaci??n de
    todas las palabras que se almacenan en el
    archivo de datos de palabras.
    */
    tpalabra p;
    palabras = fopen("datos/palabras.bat", "rb");
    if (palabras != NULL){
        while (!feof(palabras)){
            fread(&p, sizeof(p), 1, palabras);
            if (!feof(palabras)){
                cout << "ID: " << p.id << endl;
                cout << "PALABRA: " << p.palabra << endl;
                cout << "DEFINICION: " << p.definicion << endl;
                cout << "LONGITUD: " << p.longitud << endl;
            }
        }
    }
    fclose(palabras);
}
bool verificarPalabra(parchivo palabras, tcadena palabra){
    /*
    Funci??n que dado una palabra permite determinar si esta
    pertenece al archivo de datos de palabras. Retorna verdadero
    cuando haya una coincidencia de lo contrario devuelve falso.
    */
    tpalabra p;
    bool existe = false;
    palabras = fopen("datos/palabras.bat", "rb");
    if (palabras != NULL){
        while (!feof(palabras)){
            fread(&p, sizeof(p), 1, palabras);
            if (!feof(palabras)){
                if (strcmp(p.palabra, palabra) == 0)
                    existe = true;
            }
        }
    }
    fclose(palabras);
    return existe;
}

/* - - Jugar - - */
void elegirJugadores(detallesPartida &config, bool &jugadoresSeleccionados){
    /*
    Procedimiento que permite cargar, en la variable config, la configuraci??n de los jugadores
    elegidos para el juego. Para elegir los jugadores el usuario tendr?? 
    que indicar el nickname de su cuenta.
    Para verificar que los jugadores seleccionados existan se reutiliza la funci??n
    "verificarJugador", en caso de que los dos jugadores seleccionados existan
    la variable "jugadoresSeleccionados" toma el valor de verdadero para mayor control,
    en caso de que alguno de los jugadores selccionados no exista la varible antes 
    mencionada toma el valor de falso y el usuario tendr?? que volver a intentarlo.
    */
    parchivo jugadores;
    cout << "Indique el nickname del primer jugador" << endl;
    fflush(stdin);
    gets(config.jugador1.nickname);
    cout << "Indique el nickname del segundo jugador" << endl;
    fflush(stdin);
    gets(config.jugador2.nickname);
    if (verificarJugador(jugadores, config.jugador1.nickname) == true && verificarJugador(jugadores, config.jugador2.nickname) && strcmp(config.jugador1.nickname, config.jugador2.nickname) != 0){
        cout << "JUGADORES SELECCIONADOS" << endl;
        jugadoresSeleccionados = true;
        config.jugador1.puntaje = 0;
        config.jugador1.palabrasAdivinadas = 0;
        config.jugador2.puntaje = 0;
        config.jugador2.palabrasAdivinadas = 0;
    }
    else{
        cout << "ALGUNO DE LOS JUGADORES NO ESTA REGISTRADO, VUELVA A INTENTAR" << endl;
        cout << "TENGA EN CUENTA QUE NO PUEDE ENFRENTAR A SI MISMO" << endl;
        jugadoresSeleccionados = false;
    }
}
void seleccionarNivel(detallesPartida &config, bool &palabrasSeleccionadas){
    /*
    Procedimiento que permite cargar, en la variable config, la configuraci??n de las palabras destinadas
    al tablero de juego, dependiendo del nivel que se elegi las palabras tendr??n
    cierta longitud m??xima. Para lograr una selecci??n de palabras aleatorias
    se opto por hacer una lista de preselelecci??n de las mismas, esta lista (vector)
    contrendr?? a todas aquellas palabras que sean candidatas para el nivel elegido
    y luego ser??n elegidas al azar para la lista final, formandose asi una lista de
    6 palabras escogidas al azar que ser?? el tablero de juego.
    */
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
    if (preListaPalabras.ocupado >= 5){
        seleccionarPalabras(listaPalabras, preListaPalabras);
        config.listaPalabras = listaPalabras;
        palabrasSeleccionadas = true;
        cout << "La lista se genero con exitosamente" << endl;
    }
    else{
        cout << "No existen palabras suficientes para generar la lista, por favor seleccione otra dificultad o agregue mas palabras" << endl;
    }
}
void iniciarPartida(detallesPartida config, parchivo jugadores){
    /*
    Este procedimiento se centra en el funcionamiento del juego, gracias a la
    variable config, que es donde esta guardada toda la configuraci??n necesaria
    para que el juego fluya de la mejor manera y proporcine datos adecuados para
    el control y validaci??n de aspectos claves por lo tanto esta es la variable
    mas importante de todo el modulo para el correcto funcionamiento del mismo.

    En esta variable config se encuentra la siguiente informaci??n:
     - Datos de los jugadores de la partida como su nickname, la cantidad de palabras adivinadas 
     y el puntaje.
     - El tablero de juego (lista de polabras a adivinar).
     - El nivel elegido de la partida.
     - El jugador activo, la cual nos servir?? para controlar la intercalaci??n de turnos asi como
     tambi??n el control del puntaje e intentos. el valor 1 es para el jugador 1 y el valor 2 para el jugador 2.
     - La cantidad de intentos restantes del jugador activo, ??til para dar paso a la intercalaci??n de
     turnos una vez la cantidad llegue a 0.
     - Un booleano que nos indicar?? si la palabra fue acertada o no, ??til para dar paso a la intercalaci??n
     de turnos y el puntaje asignado al jugador que acerto la palabra.
    
    Tambi??n se declarar??n variables importantes como "palabraActual" que nos indica la palabra que se esta jugando 
    (esta variable ir?? recorriendo la lista de palabras a medida que estas sean adivinadas o el jugador se quede sin
    intentos) y "palabraOcultada" que se trata de un arreglo de booleanos para dar indicativo con valores verdaderos
    y falsos los caracteres que se deben mostrar a medida que estos sean acertados.

    */
    system("cls");
    int opcion=0;
    config.jugadorActivo = 1;
    pnodo palabraActual;
    tarregloBool palabraOcultada;
    bool tieneIntentos = true;
    // El for recorre todo la lista de palabras y se detiene cuando llega al final o la opcion es 4 (abandonar la partida)
    for (palabraActual=config.listaPalabras; palabraActual!=NULL && opcion!=4; palabraActual = palabraActual->siguiente){
        config.estaAdivinada = false;
        ocultarPalabra(palabraActual, palabraOcultada);
        config.intentosRestantes = palabraActual->dato.longitud/2;
        do{
            // Dependiendo de el valor de jugador activo se mostrar?? la informaci??n de uno o del otro.
            if (config.jugadorActivo == 1){
                cout << "JUGANDO: " << config.jugador1.nickname << endl;
                cout << "PUNTAJE: " << config.jugador1.puntaje << endl;
                cout << "INTENTOS DISPONIBLES: " << config.intentosRestantes << endl;
            }
            else{
                cout << "JUGANDO: " << config.jugador2.nickname << endl;
                cout << "PUNTAJE: " << config.jugador2.puntaje << endl;
                cout << "INTENTOS DISPONIBLES: " << config.intentosRestantes << endl;
            }
            // Se va mostrando en tiempo los caracteres que se van acertando.
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
                    controlPistas(config, config.jugadorActivo, palabraActual);
                    break;
                case 3:
                    arriesgarSolucion(config, palabraActual);
                    break;
                case 4:
                    cout << "Volviendo al menu anterior" << endl;
                    break;
                default:
                    cout << "OPCION NO VALIDA" << endl;
                    break;
            }
            // Verificaci??n de si el jugador activo aun tiene intentos.
            tieneIntentos = config.intentosRestantes > 0;
            if (tieneIntentos == false)
               cout << "Se te acabaron los intentos :(" << endl;
            // Verificaci??n de si la palabra fue adivinada y si es asi se procede al c??lculo del puntaje.
            if (config.estaAdivinada == true){
                controlPuntaje(config, config.jugadorActivo, palabraActual);
            }
            // Aqui es donde se produce el intercambio de turnos.
            if (config.estaAdivinada == true || tieneIntentos == false){
                if (config.jugadorActivo == 1){
                    config.jugadorActivo = 2;
                }
                else{
                    config.jugadorActivo = 1;
                }
            }
            system("pause");
            system("cls");
            /*
            El ciclo while termina cuando: 
             - La opcion es 4 (abandonar partida).
             - La palabra fue adivinada, dando paso asi a la siguiente palabra.
             - El jugador ya no tiene intentos, dando paso asi a la siguiente palabra.
            */
        }while (opcion != 4 && config.estaAdivinada != true && tieneIntentos != false);
    }
    /*
    Una vez finalizado el ciclo for (el tablero se jugo por completo), se anuncia
    los resultados finales de la misma.
    */
    cout << " - - - PARTIDA FINALIZADA - - - " << endl;
    if (config.jugador1.palabrasAdivinadas == 0 && config.jugador2.palabrasAdivinadas == 0){
        cout << "No se adivino ninguna palabra, no hay un ganador" << endl;
    }
    else{
        if (config.jugador1.puntaje == config.jugador2.puntaje){
            cout << "El resultado de la partida es un empate" << endl;
            guardarRegistro(jugadores, config.jugador1, false);
            guardarRegistro(jugadores, config.jugador2, false);
        }
        else{
            if (config.jugador1.puntaje > config.jugador2.puntaje){
                cout << "GANADOR: " << config.jugador1.nickname << endl;
                guardarRegistro(jugadores, config.jugador1, true);
            }
            else{
                cout << "GANADOR: " << config.jugador2.nickname << endl;
                guardarRegistro(jugadores, config.jugador2, true);
            }
            cout << "Puntaje jugador 1: " << config.jugador1.puntaje << endl;
            cout << "Puntaje jugador 2: " << config.jugador2.puntaje << endl;
        }
    }
}

void preSeleccionarPalabras(tarreglo &preListaPalabras, int criterio){
    /*
    Procedimiento que genera una preselecci??n de palabras destinadas al
    tablero de juego, devolviendo el resultado en la variable "preListaPalabras"
    Esta preselecci??n se genera recorriendo el archivo de datos de palabras y
    guardando en un arreglo a aquellas que sean candidatas para el nivel elegido.
    */
    parchivo palabras;
    tpalabra p;
    palabras = fopen("datos/palabras.bat", "rb");
    if (palabras != NULL){
        while (!feof(palabras)){
            fread(&p, sizeof(p), 1, palabras);
            if (!feof(palabras)){
                if (p.longitud <= criterio){
                    preListaPalabras.ocupado += 1;
                    preListaPalabras.datos[preListaPalabras.ocupado] = p;
                }
            }
        }
    }
    fclose(palabras);
}
void seleccionarPalabras(pnodo &listaPalabras, tarreglo preListaPalabras){
    /*
    Este procedimiento toma una preselecci??n de palabras para generar la
    lista de palabras final. La preselecci??n de palabras se trata de un arreglo
    asi que generando indices aleatorios se obtiene una combinaci??n de palabras
    adecuada para el juego, por cada indice generado se comprueba de que esta no exista
    en la lista final, para evitar repeticiones, y si no esta en la lista final
    esta se agrega a la lista final y asi hasta completar el n??mero de palabras deseadas para el
    tablero.
    */
    pnodo i, nuevo;
    int indice, cantidad = CANT_PALABRAS;
    bool existe;
    while (cantidad > 0){
        existe = false;
        indice =  1 + rand() % (preListaPalabras.ocupado - 0);
        // Comprobar que no se repitan palabras
        if (listaPalabras != NULL)
            for (i=listaPalabras; i != NULL; i=i->siguiente){
                if (strcmp(i->dato.palabra, preListaPalabras.datos[indice].palabra) == 0)
                    existe = true;
            }
        // Agregar la palabra
        if (existe == false){
        crearNodo(nuevo, preListaPalabras.datos[indice]);
        agregarInicio(listaPalabras, nuevo);
        cantidad -= 1;
        }
    }
    //mostrarLista(listaPalabras);
}
void probarLetra(detallesPartida &config, pnodo &palabraActual, tarregloBool &palabraOcultada){
    /*
    Procedimiento que solicita al jugador la letra que se supone adecuada para la
    palabra en juego, esta es evaluada si correcta, en caso de que sea correcta la
    palabra oculta (recordemos que es un vector de booleanos) en el indice al que pertenece 
    el caracter cambia su valor a verdadero indicando que el caracter puede mostrarse y 
    asi lograr ver el progreso de la palabra en juego. En caso de que no sea correcto al
    jugador se le descontar?? un intento.
    Tambi??n se agrega un control adicional para comprobar si la palabra oculta
    (vector de boleanos) tiene todos sus indices en verdadero lo cual de ser asi
    nos indicaria que la palabra fue adivinada y que debe pasarse a la siguiente.
    */
    char letraJugada;
    cout << "Introduce una letra: ";
    cin >> letraJugada;
    if (verificarLetra(palabraActual, palabraOcultada, letraJugada) == true){
        cout << "Genial, acertaste una letra" << endl;
    }
    else{
        cout << "No acertaste una letra :(" << endl;
            config.intentosRestantes -= 1;
    }
    if (verificarPalabraAcertada(palabraActual, palabraOcultada) == true){
        cout << "Acertaste la palabra" << endl;
        config.estaAdivinada = true;
    }
}
void ocultarPalabra(pnodo palabraActual, tarregloBool &palabraOcultada){
    /*
    Procedimiento que toma a la palabra que esta en juego y crea un arreglo
    compuesta por booleanos, este arreglo tiene la misma longitud de la palabra
    en juego utilizandola como auxiliar para determinar que caracteres se han
    acertado, colocando un valor verdadero en el indice correspondiente.
    */
    palabraOcultada.ocupado = -1;
    if (palabraActual != NULL){
        for (int i=0; i<palabraActual->dato.longitud; i+=1){
            palabraOcultada.ocupado += 1;
            palabraOcultada.datos[palabraOcultada.ocupado] = false;
        }
    }
}
bool verificarLetra(pnodo palabraActual, tarregloBool &palabraOcultada, char letra){
    /*
    Funci??n que dado una letra determina si esta pertenece en la palabra que esta en juego,
    si esta pertenece a la palabra entonces en el vector de booleanos, mencionado en modulos anteriores,
    determinar?? a que posici??nes pertenece la letra acertada cambiando su valor a verdadero en
    los correspondientes indices y devolviendo verdadero como resultado de la funci??n.
    En caso de que la letra no pertenezca a la palabra la funci??n retornara falso.
    */
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
    /*
    Funci??n que verifica si la palabra fue acertada, para esto toma el vector
    de boleanos y verifica si todas sus posiciones tienen el valor verdadero.
    De ser asi retornar?? verdadero y en caso contrario falso.
    */
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
    /*
    Este procedimiento muestra el progreso de la palabra que esta en juego,
    tomando el vector de boleanos si sus posiciones son falsas imprime un
    "_" para representar que la letra en esa posicion a??n no fue acertada
    y en cambio en las posicion que contengan un valor verdadero mostrar??
    el caracter correspondiente, logrando de esta manera poder mostrar un
    progreso en la palabra jugada como se menciono antes.
    */
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
    /*
    Procedimiento encargado de proporcionar las pistas al jugador cuando este las
    requiera, haciendo uso de la variable "config" que contiene a "jugadorActivo"
    se puede saber a que jugador se debe descontar el puntaje por la pista dada.
    */
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
void arriesgarSolucion(detallesPartida &config, pnodo palabraActual){
    tcadena palabraArriesgada;
    cout << "Ya la tienes? Dime la palabra: ";
    fflush(stdin);
    gets(palabraArriesgada);
    if (strcmp(palabraArriesgada, palabraActual->dato.palabra) == 0){
        cout << "Adivinaste la palabra!" << endl;
        config.estaAdivinada = true;
    }
    else{
        config.intentosRestantes = 0;
        cout << "Esa no era la palabra, perdiste :(" << endl;
    }
}
void controlPuntaje(detallesPartida &config, int jugadorActivo, pnodo palabraActual){
    /*
    Este procedimiento se encarga de calcular el puntaje final por la palabra adivinada
    teniendo en cuenta que el puntaje se calcula de manera en que cada letra de la 
    palabra vale 3 puntos, duplicandose en caso de que la palabra sea palindroma o
    triplicandose en caso de que todos sus caracteres sean distintos.
    Teniendo en cuenta la variable config la cual nos ayudar?? a saber quien es el jugador
    activo para poder realizar la correcta suma de puntaje.
    */
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
    /*
    Funci??n que utilizando el TDA Cola toma la palabra en juego para verificar
    si esta es palindroma, de ser asi la funci??n retornar?? verdadero, de lo 
    contrario retornar?? falso.
    */
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
    /*
    Funci??n que utilizando el TDA Conjunto verifica si una
    palabra tiene todos sus caracteres distintos, para esto se
    agregan cada uno de los caracteres de la palabra a un conjunto
    creado. Si este conjunto creado no es igual a la palabra
    original entonces tiene caracteres repetidos devolviendo falso
    como resultado de la funci??n, en caso contrario devolver??
    verdadero.
    */
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
void guardarRegistro(parchivo jugadores, detallesJugador jugador, bool gano){
    /*
    Procedimiento que recibe el registro del jugador ganador de la partida
    y suma su puntaje obtenido y suma una partida ganada en el archivo de datos
    de jugadores.
    */
    tjugador j;
    jugadores = fopen("datos/jugadores.bat", "rb+");
    bool registrado = false;
    while (!feof(jugadores) && registrado == false){
        fread(&j, sizeof(j), 1, jugadores);
        if (strcmp(j.nickname, jugador.nickname) == 0){
            if (gano == true)
                j.partidasGanadas += 1;
            j.puntaje += jugador.puntaje;
            fseek(jugadores, -sizeof(j), 1);
            fwrite(&j, sizeof(j),1, jugadores);
            registrado = true;
        }
    }
    cout << "Se ha registrado tu partida " << jugador.nickname << endl;
    fclose(jugadores);
}