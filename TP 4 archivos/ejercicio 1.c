/* 1) Realizar un programa en el cual se ingresen los siguientes datos
Nombre, Apellido y DNI
a) Crear un menu donde se ingresen los datos y los guarde en un
archivo
b) Otro item donde se pueda realizar una busqueda por DNI y
devuelva los datos de Nombre y apellido
c) Salir del mismo */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 50

// Estructura para almacenar los datos
typedef struct {
    char nombre[MAX_CHAR];
    char apellido[MAX_CHAR];
    char dni[MAX_CHAR];
} Persona;

// Funcion para ingresar los datos y guardarlos en un archivo
void ingresarDatos(FILE *archivo) {
	system("cls");
    Persona persona;

    printf("Ingrese el Nombre: ");
    scanf("%s", persona.nombre);
    printf("Ingrese el Apellido: ");
    scanf("%s", persona.apellido);
    printf("Ingrese el DNI: ");
    scanf("%s", persona.dni);

    fprintf(archivo, "%s %s %s\n", persona.nombre, persona.apellido, persona.dni);
    printf("Datos guardados en el archivo.\n");
}

// Funcion para buscar y mostrar los datos por DNI
void buscarPorDNI(FILE *archivo) {
	system("cls");
    char dniBusqueda[MAX_CHAR];
    Persona persona;
    int encontrado = 0;

    printf("Ingrese el DNI a buscar: ");
    scanf("%s", dniBusqueda);

    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %s %s", persona.nombre, persona.apellido, persona.dni) != EOF) {
        if (strcmp(persona.dni, dniBusqueda) == 0) {
            printf("Nombre: %s\nApellido: %s\n", persona.nombre, persona.apellido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos para el DNI ingresado.\n");
    }
}

int main() {
    FILE *archivo;
    int opcion;

    archivo = fopen("datos.txt", "a+"); // Abrir el archivo en modo lectura y escritura

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar datos y guardar en archivo\n");
        printf("2. Buscar por DNI\n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatos(archivo);
                break;
            case 2:
                buscarPorDNI(archivo);
                break;
            case 3:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 3);

    fclose(archivo); // Cerrar el archivo al salir del programa

    return 0;
}

