/* 6) Realizar un programa que realice las siguientes acciones
a. Guarde el registro del nombre y el puntaje de un jugador (solicitando el ingreso
de los datos del usuario)
b. Muestre el resultado de los 10 mejores jugadores ordenados por mayor
puntaje.
c. Realice y muestre una búsqueda de un Nombre y devuelva sus resultados
NOTA: el registro debe permanecer aunque se apague la PC. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 50
#define MAX_JUGADORES 10

// Estructura para almacenar los datos de un jugador
typedef struct {
    char nombre[MAX_CHAR];
    int puntaje;
} Jugador;

// Función para ingresar los datos de un jugador y guardarlos en el archivo
void ingresarJugador(FILE *archivo) {
	system("cls");
    Jugador jugador;

    printf("Ingrese el nombre del jugador: ");
    scanf("%s", jugador.nombre);
    printf("Ingrese el puntaje del jugador: ");
    scanf("%d", &jugador.puntaje);

    fprintf(archivo, "%s %d\n", jugador.nombre, jugador.puntaje);
    printf("Jugador registrado con éxito.\n");
}

// Función para comparar jugadores por puntaje para ordenar
int compararPorPuntaje(const void *a, const void *b) {
    const Jugador *jugadorA = (const Jugador *)a;
    const Jugador *jugadorB = (const Jugador *)b;

    return jugadorB->puntaje - jugadorA->puntaje;
}

int i;

// Función para mostrar los 10 mejores jugadores ordenados por puntaje
void mostrarMejoresJugadores(FILE *archivo) {
	system("cls");
    Jugador jugadores[MAX_JUGADORES];
    int numJugadores = 0;

    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %d", jugadores[numJugadores].nombre, &jugadores[numJugadores].puntaje) != EOF) {
        numJugadores++;
    }

    qsort(jugadores, numJugadores, sizeof(Jugador), compararPorPuntaje);

    printf("Los 10 mejores jugadores son:\n");
    for (i = 0; i < numJugadores && i < 10; i++) {
        printf("%d. Nombre: %s - Puntaje: %d\n", i + 1, jugadores[i].nombre, jugadores[i].puntaje);
    }
}

// Función para buscar un jugador por nombre
void buscarJugador(FILE *archivo) {
	system("cls");
    char nombreBusqueda[MAX_CHAR];
    Jugador jugador;
    int encontrado = 0;

    printf("Ingrese el nombre del jugador a buscar: ");
    scanf("%s", nombreBusqueda);

    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %d", jugador.nombre, &jugador.puntaje) != EOF) {
        if (strcmp(jugador.nombre, nombreBusqueda) == 0) {
            printf("Jugador encontrado - Nombre: %s - Puntaje: %d\n", jugador.nombre, jugador.puntaje);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron resultados para el nombre ingresado.\n");
    }
}

int main() {
    FILE *archivo;
    int opcion;

    archivo = fopen("jugadores.txt", "a+"); // Abrir el archivo en modo lectura y escritura

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar jugador y guardar en archivo\n");
        printf("2. Mostrar los 10 mejores jugadores\n");
        printf("3. Buscar jugador por nombre\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarJugador(archivo);
                break;
            case 2:
                mostrarMejoresJugadores(archivo);
                break;
            case 3:
                buscarJugador(archivo);
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    fclose(archivo); // Cerrar el archivo al salir del programa

    return 0;
}
