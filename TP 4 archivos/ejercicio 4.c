/* 4) Modificar dicho programa de manera que me muestre los datos de manera ordenada
Según se desee por nombre y apellido o por DNI */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 50
#define MAX_PERSONAS 100

// Estructura para almacenar los datos
typedef struct {
    char nombre[MAX_CHAR];
    char apellido[MAX_CHAR];
    char dni[MAX_CHAR];
} Persona;

// Función para comparar dos personas por nombre y apellido
int compararPorNombreYApellido(const void *a, const void *b) {
    Persona *persona1 = (Persona *)a;
    Persona *persona2 = (Persona *)b;

    int comparacion = strcmp(persona1->apellido, persona2->apellido);
    if (comparacion == 0) {
        comparacion = strcmp(persona1->nombre, persona2->nombre);
    }

    return comparacion;
}

// Función para comparar dos personas por DNI
int compararPorDNI(const void *a, const void *b) {
    Persona *persona1 = (Persona *)a;
    Persona *persona2 = (Persona *)b;

    return strcmp(persona1->dni, persona2->dni);
}

int i;

// Función para mostrar los datos de un arreglo de personas
void mostrarDatosOrdenados(Persona *personas, int cantidad) {
    for (i = 0; i < cantidad; i++) {
        printf("Nombre: %s\nApellido: %s\nDNI: %s\n\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
}

// Función para ordenar y mostrar los datos por nombre y apellido
void mostrarDatosOrdenadosPorNombreYApellido(FILE *archivo) {
    Persona personas[MAX_PERSONAS];
    int cantidad = 0;

    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %s %s", personas[cantidad].nombre, personas[cantidad].apellido, personas[cantidad].dni) != EOF) {
        cantidad++;
    }

    qsort(personas, cantidad, sizeof(Persona), compararPorNombreYApellido);

    mostrarDatosOrdenados(personas, cantidad);
}

// Función para ordenar y mostrar los datos por DNI
void mostrarDatosOrdenadosPorDNI(FILE *archivo) {
    Persona personas[MAX_PERSONAS];
    int cantidad = 0;

    rewind(archivo); // Volver al inicio del archivo

    while (fscanf(archivo, "%s %s %s", personas[cantidad].nombre, personas[cantidad].apellido, personas[cantidad].dni) != EOF) {
        cantidad++;
    }

    qsort(personas, cantidad, sizeof(Persona), compararPorDNI);

    mostrarDatosOrdenados(personas, cantidad);
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
        printf("4. Mostrar datos ordenados por nombre y apellido\n");
        printf("5. Mostrar datos ordenados por DNI\n");
        printf("6. Salir\n");
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
                mostrarDatosOrdenadosPorNombreYApellido(archivo);
                break;
            case 5:
                mostrarDatosOrdenadosPorDNI(archivo);
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    fclose(archivo); // Cerrar el archivo al salir del programa

    return 0;
}
