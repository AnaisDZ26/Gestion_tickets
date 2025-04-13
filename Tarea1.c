// Incluir bibliotecas necesarias
#include "TDAs/list.h"  
#include "TDAs/queue.h"
#include "TDAs/list.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>  // Para funciones como toupper e isdigit
#include <time.h>   // Para obtener la hora actual del sistema

typedef struct {
    int ID;
    char descripcion[2001]; // Hasta 2000 caracteres
    char prioridad[6];  // Hasta 5 caracteres ya que las opciones son alta, media y baja
    int hora;   // Almacena la hora del registro
    int min;
    int seg;
} tipo_Ticket;

/* Función para mostrar el menu de oppciones*/

void mostrar_menu(){
    puts("==================================");
    puts("Seleccione alguna de las opciones");
    puts("==================================");
    puts("1._ Registrar ticket");
    puts("2._ Asignar prioridad a ticket");
    puts("3._ Ver lista de tickets pendientes");
    puts("4._ Procesar ticket prioritario");
    puts("5._ Buscar ticket por ID");
    puts("6._ Salir");
    puts("");
}

/*  Registra un ticket cual tiene prioridad baja por defecto
    Tambien guarda la hora, minutos y segundos en la que se 
    hizo el registro. */

void Registrar_ticket(Queue *cola_baja){
    tipo_Ticket *ticket_usuario = (tipo_Ticket *) malloc (sizeof(tipo_Ticket));
    // Solicita ID numerica al usuario.
    puts ("Ingrese su ID : ");
    scanf ("%d", &ticket_usuario->ID);
    // Solicita la descripcion del problema
    puts("Descripcion del problema : ");
    scanf (" %[^\n]", ticket_usuario->descripcion);
    // Se le asigna la prioridad baja al ticket ingresado
    strcpy(ticket_usuario->prioridad, "BAJA");
    
    // Se obtiene la hora del sistema y se guardan en la variable ticket
    time_t tiempo = time(NULL);
    struct tm hora_actual = *localtime(&tiempo);
    ticket_usuario->hora = hora_actual.tm_hour;
    ticket_usuario->min = hora_actual.tm_min;
    ticket_usuario->seg = hora_actual.tm_sec;

    // Se inserta al inicio de la cola de prioridad baja
    queue_insert(cola_baja, ticket_usuario);
}

void Cambiar_prioridad(Queue *cola_alta, Queue *cola_media, Queue *cola_baja){
    /* Se crea una ID temporal con la intencion de ver si coincide con la ID guardada
    anteriormente en la cola. Se hara una cola temporal ya que se recorrera la cola con 
    los tickets de prioridad baja, se iran borrando de esta para iterar e ir guardando
    en la cola temporal, cuando el bucle este finalizado, los tickets cuya prioridad
    sigue siendo baja, volveran a la cola original que es la "cola_baja" */
    // Detalle de que no se puede cambiar de prioridad mas de una vez
    
    int ID_temp;
    printf("\nIngrese su ID : ");
    scanf ("%d", &ID_temp);

    // Se ingresa la nueva prioridad
    char nueva_prioridad[6];
    puts ("A que prioridad desea cambiar su ticket ?");
    scanf (" %[^\n]", nueva_prioridad);

    // Poniendonos en el caso de que el usuario asigno su nueva prioridad en minuscula
    for (int i = 0 ; nueva_prioridad[i] ; i++){
        nueva_prioridad[i] = toupper(nueva_prioridad[i]);
    }

    Queue *temporal = queue_create(NULL);
    tipo_Ticket *usuario;
    /*  Variable creada para evitar pasar por las coindiciones en caso de que no se encuentre
        coincidencias al momento de verificar la ID*/
    bool coincidencia = false;

    while ((usuario = queue_remove(cola_baja)) != NULL){
        if (usuario->ID == ID_temp){
            coincidencia = true;
            /*  Dependiendo de la prioridad nueva que se desea asignar se realiza el cambio de
            cola_baja a cola_alta o cola_media*/
            if (strcmp(nueva_prioridad, "ALTA") == 0){
                strcpy(usuario->prioridad, "ALTA");
                queue_insert(cola_alta, usuario);
                puts ("El cambio de prioridad a alta ha sido realizado con exito !!");
                puts("");
            } else if (strcmp(nueva_prioridad, "MEDIA") == 0){
                strcpy(usuario->prioridad, "MEDIA");
                queue_insert(cola_media, usuario);
                puts ("El cambio de prioridad a media ha sido realizado con exito !!");
                puts("");
            } else if (strcmp(nueva_prioridad, "BAJA") == 0){
                queue_insert(temporal, usuario);
                puts ("Su ticket ya se encuentra en prioridad baja !!");
                puts("");
            } else {
                // En caso de que el usuario no ingrese una prioridad igual a alta, media o baja
                puts ("Ingrese una prioridad valida e intentelo de nuevo");
                puts("");
                queue_insert(temporal, usuario);
            }
        } else {
            //  En caso de que el ID no coincida siga recorriendo el bucle 
            // Y se guarda de igual manera en la cola temporal
            queue_insert(temporal, usuario);
        }
    }
    // Coindicion en caso de que no se encuentre la ID que el usuario ingreso
    if (!coincidencia){
        puts ("No se ha encontrado un ticket con el ID ingresado, intentelo nuevamente");
        puts("");
    }
    // Bucle para que los tickets ingresados a la cola temporal, vuelvan a su cola original
    while ((usuario = queue_remove(temporal)) != NULL){
        queue_insert(cola_baja, usuario);
    }
    queue_clean(temporal);
}

/* La funcion unificar_todas, se hizo con la intencion de facilitar el proceso
de iteracion, como en las funciones en las cuales se deben mostrar los tickets
por prioridad o en las funciones donde se debe buscar ticket por ticket hasta 
encontrar la ID solicitada */

List *unificar_todas(Queue *cola_alta, Queue *cola_media, Queue *cola_baja){
    List *lista_total = list_create();
    tipo_Ticket *aux_ticket;

    /*Se extraen los tickets en orden por prioridad, primero alta, luego media y
    finalmente alta y se insertan en la lista que unifica todas las colas*/
    while ((aux_ticket = queue_remove(cola_alta)) != NULL)
        list_pushBack(lista_total, aux_ticket);
    while ((aux_ticket = queue_remove(cola_media)) != NULL)
        list_pushBack(lista_total, aux_ticket);
    while ((aux_ticket = queue_remove(cola_baja)) != NULL)
        list_pushBack(lista_total, aux_ticket);

    return lista_total;
}

/*  Restaura los tickets de la lista anteriormente creada y los ingresa segun
    su prioridad, ya que en la funcion main todo se maneja colas*/

void restaurar_colas(List *lista_total, Queue *cola_alta, Queue *cola_media, Queue *cola_baja){
    tipo_Ticket *aux_ticket = list_first(lista_total);
    while (aux_ticket != NULL){
        if (strcmp(aux_ticket->prioridad, "ALTA") == 0)
            queue_insert(cola_alta, aux_ticket);
        else if (strcmp(aux_ticket->prioridad, "MEDIA") == 0)
            queue_insert(cola_media, aux_ticket);
        else
            queue_insert(cola_baja, aux_ticket);
        // Pasamos al siguente ticket hasta que sea igual a NULL
        aux_ticket = list_next(lista_total);
    }
    list_clean(lista_total);
}

/*  Muestra una lista de tickets pendientes ordenados segun prioridad y hora de ingreso, mostrando el ID,
descripcion, hora y prioridad de todos los tickets*/

void Mostrar_tickets(Queue *cola_alta, Queue *cola_media, Queue *cola_baja){
    List *lista_general = unificar_todas(cola_alta, cola_media, cola_baja);
    tipo_Ticket *ticket = list_first(lista_general);
    puts ("===== Tickets Pendientes ====");
    while (ticket != NULL){
        printf ("ID del usuario: %d\n", ticket->ID);
        printf ("Descripcion : %s\n", ticket->descripcion);
        printf ("Prioridad : %s\n", ticket->prioridad);
        printf ("Hora del registro : %02d:%02d:%02d\n\n", ticket->hora, ticket->min, ticket->seg);

        ticket = list_next(lista_general);
    }
    restaurar_colas(lista_general, cola_alta, cola_media, cola_baja);
}

/*  La funcion procesar_siguiente mas que nada muestra el ticket con mayor prioridad y mas antiguo
luego lo muestra y elimina de la lista total de tickets*/

void Procesar_siguiente(Queue *cola_alta, Queue *cola_media, Queue *cola_baja){
    List *lista_total = unificar_todas(cola_alta, cola_media, cola_baja);
    tipo_Ticket *ticket_aux = list_first(lista_total);
    
    if (ticket_aux != NULL){
        puts ("== Ticket procesado ==");
        printf ("ID del usuario: %d\n", ticket_aux->ID);
        printf ("Descripcion : %s\n", ticket_aux->descripcion);
        printf ("Prioridad : %s\n", ticket_aux->prioridad);
        printf ("Hora del registro : %02d:%02d:%02d\n\n", ticket_aux->hora, ticket_aux->min, ticket_aux->seg);
        list_popFront(lista_total);
    }
    else {
        puts("No hay tickets pendientes !!");
    }
    restaurar_colas(lista_total, cola_alta, cola_media, cola_baja);
}

/*  La funcion Buscar_ID busca y muestra el ticket segun la ID solicitada por el usuario*/

void Buscar_ID(Queue *cola_alta, Queue *cola_media, Queue *cola_baja){
    List *lista_general = unificar_todas(cola_alta, cola_media, cola_baja);
    tipo_Ticket *ticket_aux = list_first(lista_general);
    bool coincidencia = false;
    // Se solicita la ID que se desea buscar
    int ID_buscada;
    printf("\nIngrese la ID que desea encontrar : ");
    scanf (" %d", &ID_buscada);

    while (ticket_aux != NULL){
        if (ticket_aux->ID == ID_buscada){
            printf ("ID del usuario: %d\n", ticket_aux->ID);
            printf ("Descripcion : %s\n", ticket_aux->descripcion);
            printf ("Prioridad : %s\n", ticket_aux->prioridad);
            printf ("Hora del registro : %02d:%02d:%02d\n\n", ticket_aux->hora, ticket_aux->min, ticket_aux->seg);
            coincidencia = true;
            break;  // Sale del ciclo en caso de que se encuentre la ID solicitada
        }
        ticket_aux = list_next(lista_general);
        
    }
    if (!coincidencia){
        puts("\nNo se ha encontrado ningun ticket con la ID ingresada, intentelo nuevamente.\n");
    }
    restaurar_colas(lista_general, cola_alta, cola_media, cola_baja);
}

int main(){
    // Crear 3 colas con sus respectivas prioridades
    Queue *P_BAJA = queue_create(NULL);
    Queue *P_MEDIA = queue_create(NULL);
    Queue *P_ALTA = queue_create(NULL);
    // En caso de que el usuario ingrese una opcion no valida
    char opcion_test[11];
    int opcion_real;
    do {
        mostrar_menu();
        scanf ("%10s", opcion_test);
        // Si el primer caracter de la opcion seleccionada no es un digito
        if (!isdigit(opcion_test[0])){
            // Se printea un mensaje de alerta
            puts("Ingrese una opcion valida\n");
            continue;
        }
        opcion_real = atoi(opcion_test);

        switch (opcion_real){
            case 1:
                Registrar_ticket(P_BAJA);
                puts ("\nSu ticket ha sido registrado con exito !!");
                puts("");
                break;
            case 2:
                Cambiar_prioridad(P_ALTA, P_MEDIA, P_BAJA);
                break;
            case 3:
                Mostrar_tickets(P_ALTA, P_MEDIA, P_BAJA);
                break;
            case 4:
                Procesar_siguiente(P_ALTA, P_MEDIA, P_BAJA);
                break;
            case 5:
                Buscar_ID(P_ALTA, P_MEDIA, P_BAJA);
                break;
            case 6:
                puts("Vuelva pronto !!");
                break;
            default:
                puts("Ingrese una opcion valida !!");
                break;
            }

    } while (opcion_real != 6);
    // Liberar memoria
    queue_clean(P_ALTA);
    queue_clean(P_MEDIA);
    queue_clean(P_BAJA);

    return 0;
}