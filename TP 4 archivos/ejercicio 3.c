/* Agregarle validación de datos de manera que no se repitan cuando sea necesario. */

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

// Función para verificar si una persona ya existe en el archivo
int personaExiste(FILE *archivo, Persona *persona) {
    Persona temp;
    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %s %s", temp.nombre, temp.apellido, temp.dni) != EOF) {
        if (strcmp(temp.dni, persona->dni) == 0) {
            return 1; // La persona ya existe
        }
    }

    return 0; // La persona no existe
}

// Función para ingresar los datos y guardarlos en un archivo
void ingresarDatos(FILE *archivo) {
    system("cls");
    Persona persona;

    printf("Ingrese el Nombre: ");
    scanf("%s", persona.nombre);
    printf("Ingrese el Apellido: ");
    scanf("%s", persona.apellido);
    printf("Ingrese el DNI: ");
    scanf("%s", persona.dni);

    if (personaExiste(archivo, &persona)) {
        printf("La persona ya existe en el archivo.\n");
        return;
    }

    fprintf(archivo, "%s %s %s\n", persona.nombre, persona.apellido, persona.dni);
    printf("Datos guardados en el archivo.\n");
}

// Función para buscar y mostrar los datos por DNI
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
            printf("Nombre: %s\nApellido: %s\nDNI: %s\n", persona.nombre, persona.apellido, persona.dni);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos para el DNI ingresado.\n");
    }
}

// Función para buscar y mostrar los datos por nombre y apellido
void buscarPorNombreYApellido(FILE *archivo) {
    system("cls");
    char nombreBusqueda[MAX_CHAR];
    char apellidoBusqueda[MAX_CHAR];
    Persona persona;
    int encontrado = 0;

    printf("Ingrese el nombre a buscar: ");
    scanf("%s", nombreBusqueda);
    printf("Ingrese el apellido a buscar: ");
    scanf("%s", apellidoBusqueda);

    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %s %s", persona.nombre, persona.apellido, persona.dni) != EOF) {
        if (strcmp(persona.nombre, nombreBusqueda) == 0 && strcmp(persona.apellido, apellidoBusqueda) == 0) {
            printf("Nombre: %s\nApellido: %s\nDNI: %s\n", persona.nombre, persona.apellido, persona.dni);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos para el nombre y apellido ingresados.\n");
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
        printf("3. Buscar por nombre y apellido\n");
        printf("4. Salir\n");
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
                buscarPorNombreYApellido(archivo);
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
