## Sistema de gestión de tickets para un servicio tecnico

La intención de este sistema es procesar tickets eficientemente según el orden de llegada, priorizando además la urgencia indicada por el usuario (alta, media o baja). Esto permite resolver primero los tickets de mayor prioridad, dejando en segundo plano los de menor urgencia.

## Cómo compilar y ejecutar el sistema
Este sistema ha sido desarrollado en lenguaje C, como alternativa puede ejecutarse en **Visual Studio Code**, junto con una extension de 
 C/C++ como **C/C++ Extension Pack de Microsoft**. Para comenzar a utilizar este sistema de gestion debe seguir los siguientes pasos:

- Tener instalado [Visual Studio Code]( https://code.visualstudio.com/).- Instalar la extension antes recomendada (**C/C++**).
- Tener instalado un **complidador de C** (como **gcc**). Si el usuario esta utilizando Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/).

 ## Para compilar y ejecutar el codigo del sistema
- Descarga y **descomprime** el archivo ***.zip*** en una carpeta de tu elección.
- Abre el proyecto en Visual Studio Code
- Inicia Visual Studio Code.
    - Selecciona **Archivo -> Abrir carpeta...** y elige la carpeta donde descomprimiste el proyecto.
- Compila el código
    - Abre el archivo principal (**Tarea1.c**).
    - Abre la terminal integrada (**Terminal -> Nueva terminal**).
    - En la terminal, compila el programa con el siguiente comando :
        ```
        gcc Tarea1.c -o Tarea1.exe
        ```
- Ejecuta el programa
    Una vez compilado, puedes ejecutar la aplicación con:
        ```
        ./Tarea1.exe
        ```

## Funcionalidades del programa

## Funcionando correctamente :
- Registrar el ticket con su respectiva **ID**, cuyos caracteres **Deben ser numericos**, inscribir la **descripcion** explicando el problema por el cual se esta registrando el ticket cuyo limite de caracteres es de 2000. Automaticamente se le asigna con prioridad baja y se apunta la hora en la cual se creo el ticket.
- Asignar prioridad a voluntad del usuario a un ticket determinado.
- Mostrar los tickets éndientes con su ID, descripcion, prioridad, y hora, ordenados según su prioridad y la hora del registro.
- Procesar el ticket con mayor prioridad, presentando todos los datos anteriormente eliminados.
- Buscar un ticket con una ID en especifico, y mostrando un mensaje en caso de que el ID este mal ingresado o no se encuentra en la lista de pendientes.
- Salir del sistema, esta opción elimina todos los tickets ingresados y "reinicia" el sistema.

## Problemas conocidos :
- La ID solamente admite números enteros.
- El límite de los caracteres de la descripción son 2000, si el usuario ingresa mas caracteres, puede ocurrir un error.
- La prioridad solo se puede cambiar una vez.
- Si el programa se cierra, se eliminan todos los tickets.

## A mejorar :
- La ID recibe cadena de caracteres en lugar de restringirlo a solo datos númericos.
- Evitar IDs duplicados
- Puede llegar a ser muy repetitivo o molesto que el menú se muestre despues de cada proceso.
- Que el usuario pueda cambiar de prioridad cada vez que lo prefiera.

## == Ejemplo de uso ==
**Paso 1: Registrar un nuevo ticket**
Se inicia registrando un nuevo ticket al sistema.
```
Opcion seleccionada: 1._ Registrar ticket
Ingrese su ID :
1234
Descripcion del problema :
Tuve un problema con x cosa.

Su ticket ha sido registrado con exito !!
```
El sistema registra la ID 1234 y la descripcion del problema, con una prioridad inicial baja y la hora en la cual el ticket fue registrado. La prioridad se puede modificar.

**Paso 2: Asignar prioridad al ticket**
Si el usuario piensa que su ticket debe ser categorizado con una prioridad mas alta, puede modificarlo a gusto.
```
Opción seleccionada : 2._ Asignar prioridad a ticket
Ingrese su ID : 1234
A que prioridad desea cambiar su ticket ?
Media

El cambio de prioridad a media ha sido realizado con exito !!
```
De esta manera el sistema realiza el cambio de prioridad a gusto del usuario.

**Paso 3: Ver la lista de tickets pendientes**
El usuario puede visualizar la lista completa de tickets pendientes.
```
Opción seleccionada: 3._ Ver lista de tickets pendientes
===== Tickets Pendientes ====
ID del usuario: 1234
Descripcion : Tuve un problema con x cosa.
Prioridad : MEDIA
Hora del registro : 00:55:58
```
Esta opcion presenta los tickets ingresados (que en este caso es uno), y se puede ver su ID, descripcion, prioridad asignada, y la hora del registro.

**Paso 4: Procesar un ticket**
Se procesa el ticket basandose tanto en su prioridad, como en la hora en la que el ticket fue ingresado.
```
Opción seleccionada: 4._ Procesar ticket prioritario
== Ticket procesado ==
ID del usuario: 1234
Descripcion : Tuve un problema con x cosa.
Prioridad : MEDIA
Hora del registro : 00:55:58
```
Esta opcion muestra el ticket que se esta procesando y se elimina del sistema.

**Paso 5: Buscar ticket por ID solicitada**
El usuario ingresa el ID que desea buscar.
```
Opción seleccionada: 5._ Buscar ticket por ID
Ingrese la ID que desea encontrar : 1234
ID del usuario: 1234
Descripcion : Tuve un problema con x cosa.
Prioridad : MEDIA
Hora del registro : 00:55:58
```
Se muestra en detalle los datos del registro cuya ID fue solicitada.

**Paso 6: Salir del sistema**
El usuario desea salir del programa.
```
Opción seleccionada: 6._ Salir
Vuelva pronto !!
```
Elimina todos los datos guardados anteriormente en el sistema.

**Codigo desarrollado por Anais Diaz**