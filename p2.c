#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TAMA 100

typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *CrearNodo(int id);
Nodo *CrearListaVacia();
void InsertarNodo(Nodo **Start, Nodo *NuevoNodo);
void agregarTareas(Nodo **Start);
void mostrarTareas(Nodo **Start);
void moverTareas(Nodo **Pendientes, Nodo **Realizadas, int id);
void EliminarNodo(Nodo **Start, int id);
void LiberarLista(Nodo **Start);

int main()
{

    Nodo *TareasPendientes, *TareasRealizadas;

    // Nodo *TareasPendientes = (Nodo *)malloc(sizeof(Nodo *));
    // Nodo *TareasRealizadas = (Nodo *)malloc(sizeof(Nodo *));

    int idM, seguirM = 0;

    TareasPendientes = CrearListaVacia();
    TareasRealizadas = CrearListaVacia();

    // Agregar tareas

    agregarTareas(&TareasPendientes);

    mostrarTareas(&TareasPendientes);

    // Mover tareas

    do
    {
        puts("\n\nIngrese el ID de la tarea realizada a mover: ");
        scanf("%d", &idM);

        moverTareas(&TareasPendientes, &TareasRealizadas, idM);

        printf("\nQuiere mover otra tarea?      1.SI   |   2.NO  : ");
        scanf("%d", &seguirM);
    } while (seguirM == 1);

    puts("\n-TAREAS PENDIENTES-");
    mostrarTareas(&TareasPendientes);
    puts("\n\n-TAREAS REALIZADAS-");
    mostrarTareas(&TareasRealizadas);

    // Liberar listas de tareas

    LiberarLista(&TareasPendientes);
    LiberarLista(&TareasRealizadas);

    return 0;
}

Nodo *CrearNodo(int id)
{
    Nodo *Nnodo = (Nodo *)malloc(sizeof(Nodo));
    int duracion;
    char *descripcion = (char *)malloc(TAMA * sizeof(char));

    printf("\n---Tarea nro %d---\n\n", id);

    Nnodo->T.TareaID = id;

    fflush(stdin);
    puts("Ingrese la descripcion: ");
    gets(descripcion);
    Nnodo->T.Descripcion = (char *)malloc((strlen(descripcion) + 1) * sizeof(char));

    strcpy(Nnodo->T.Descripcion, descripcion);

    puts("Ingrese la duracion: ");
    scanf("%d", &duracion);

    Nnodo->T.Duracion = duracion;

    Nnodo->Siguiente = NULL;

    // free(descripcion);

    return Nnodo;
}

Nodo *CrearListaVacia()
{
    return NULL;
}

void InsertarNodo(Nodo **Start, Nodo *NuevoNodo)
{
    NuevoNodo->Siguiente = *Start;
    *Start = NuevoNodo;
}

void agregarTareas(Nodo **Start)
{
    int seguir = 1, id = 1000;

    do
    {
        Nodo *tarea = CrearNodo(id);
        InsertarNodo(Start, tarea);

        printf("\nQuiere agregar una nueva tarea?      1.SI   |   2.NO  : ");
        scanf("%d", &seguir);
        id++;
    } while (seguir == 1);
}

void mostrarTareas(Nodo **Start)
{
    Nodo *nuevo = *Start;

    while (nuevo != NULL)
    {
        printf("\n\n---Tarea nro %d---\n\n", nuevo->T.TareaID);

        puts("Descripcion: ");
        puts(nuevo->T.Descripcion);

        printf("Duracion: ");
        printf("%d", nuevo->T.Duracion);

        nuevo = nuevo->Siguiente;
    }
}

void EliminarNodo(Nodo **Start, int id)
{
    Nodo **aux = Start;

    while (*aux != NULL && (*aux)->T.TareaID != id)
    {
        aux = &(*aux)->Siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        free(temp);
    }
}

void moverTareas(Nodo **Pendientes, Nodo **Realizadas, int id)
{
    Nodo *actual = *Pendientes;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id)
    {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual != NULL)
    {
        if (anterior != NULL)
        {
            anterior->Siguiente = actual->Siguiente;
        }
        else
        {
            *Pendientes = actual->Siguiente;
        }

        InsertarNodo(Realizadas, actual);
    }
    else
    {
        printf("\nLA TAREA CON EL ID %d NO EXISTE\n", id);
    }
}

void LiberarLista(Nodo **Start)
{
    Nodo *actual = *Start;
    Nodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->Siguiente;
        free(actual->T.Descripcion);
        free(actual);
        actual = siguiente;
    }

    *Start = NULL;
}