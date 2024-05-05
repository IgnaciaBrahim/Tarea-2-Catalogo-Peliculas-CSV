# Catálogo de Películas: Búsqueda a través de base de datos.

## Descripción:
Esta aplicación permite cargar un catálogo de películas para así buscar según los criterios de director, calificación, género, id, así como también se pueden buscar las películas que comparten género y década. 

## Instalación, compilación y ejecución:
### Por GitHub:
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar Repl.it para una rápida configuración y ejecución. Sigue estos pasos para comenzar:
1. Ingresa a [Replit](https://repl.it/)
2. Inicia sesión, o crea una cuenta si es que no tienes.
3. Una vez en tu página principal, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: [https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV)
5. Replit clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar el código. 

### Por Replit:
Si no deseas clonar el repositorio;
1. Inicia sesión a tu cuenta de Replit, o crea una cuenta si no la tienes.
2. Luego ingresa a [https://replit.com/@IgnaciaLBrahim/tarea-2-catalogo-peliculas](https://replit.com/@IgnaciaLBrahim/tarea-2-catalogo-peliculas)
3. Selecciona la opción "Fork".
4. Esto creará una copia del proyecto en tu cuenta, por lo que podrás correrla y editarla si deseas, sin modificar el proyecto original.
5. Puedes compilar y correr el proyecto con "Run".

## Funcionalidades

### Funcionando correctamente:
En el programa podrás encontrar un menú con las siguientes funcionalidades:  

`1) Cargar Películas: ` Se cargan las películas del archivo indicado, en este caso siempre serán las películas del CSV "Top1500". 

`2) Buscar por id: `  Según el ID que se ingresa, muestra la película que se conoce por ese ID que se encuentra en el archivo.

`3) Buscar por director: `  Según el nombre del director que se ingresa, muestra la lista de películas que han sido dirigidas por él que se encuentren en el archivo. Si no encuentra, emite un aviso.

`4) Buscar por género: ` Según el género que se ingresa, muestra la lista de películas que pertenecen al género que se encuentran en el archivo. Si no encuentra, emite un aviso.

`5) Buscar por década: ` Según la década que se ingresa, muestra la lista de películas que pertenezcan a la década que se encuentren en el archivo. Si no encuentra, emite un aviso. La década debe ser ingresada como el año donde comienza, por ejemplo, "2000".

`6) Buscar por rango de calificaciones: ` Según el rango de calificaciones que ingresa el usuario, se busca la lista de películas que vaya entre ese rango, incluyendo los valores especificados por el usuario. Si es que no se encuentran películas, se emite un aviso. La calificación debe ser especificada como número, Ej: "4", "5.5". 

`7) Buscar por década y género: ` Se le pide al usuario que ingrese el género que deben tener las películas que busca. Si encuentra ese género en el archivo, se le pide que ingrese la década a la que deben pertenecer esas películas. Si es que no es encuentra, se emite un aviso. De otra forma, muestra las películas que comparten el género y década especificados por el usuario.

`8) Salir: ` Al seleccionar opción 8, el programa deja de correr y se pierden los datos de las películas cargadas.

### Problemas conocidos:
El problema es que siempre debe estar cargado el archivo en replit "Top1500" para la correcta carga de las películas y las demás funcionalidades del programa. Si el archivo no se puede cargar o no es el correcto, no se asegura que funcione. 

También, si en lugar de números se ingresan nombres o viceversa, puede que algunas funcionalidades en vez de emitir avisos no hagan nada. 

### A mejorar:

1) Hacer un programa que pueda leer variados CSVs de películas con el mismo formato.
2) Implementar una interfaz de usuario más amigable en general.
3) Manejar de mejor forma los errores que pueda cometer el usuario al responder las preguntas para obtener los datos que se esperan de él.
4) Permitir el guardado del cargado de películas, ya que cada vez que se ingresa al programa hay que volver a cargarlas, y cuando se sale del programa se pierden los datos.

## Ejemplo de uso e interacción:
Para poder interactuar con el programa, deberás apretar el botón "Run" y luego ir al apartado "Console" para poder ingresar datos:



`1) Cargar Película: `

![Captura de pantalla 2024-05-05 163927](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/3986b5b5-0e43-4dd0-87a9-26badcad8d0d)


![Captura de pantalla 2024-05-05 164048](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/8fb488d5-d9c8-4b9e-9697-94a26d4974b7)


Si seleccionas cargar películas, puedes dedicir si quieres ver sus id/título. Se implementó así ya que son 1500 películas.



`2) Buscar por id: `


![Captura de pantalla 2024-05-05 165149](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/3dd78513-9b05-4084-a97e-949bea058f29)


Si ingresas un ID válido, mostrará la película que le corresponde. Intenta mirar el archivo CSV y buscar un id, ya que es difícil memorizarlo.



`3) Buscar por director: `


![Captura de pantalla 2024-05-05 165234](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/eb5bea89-3a3a-4f65-944d-3c66da4e881b)


Si ingresas por ejemplo "Quentin Tarantino", mostrará las películas que haya dirigido él que se encuentren en el archivo. Si no se encuentra el director o lo escribiste mal, te indicará que no se encuentra en la base de datos.



`4) Buscar por género: `


![Captura de pantalla 2024-05-05 165311](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/d455e125-1c87-4692-8600-1fe7694a9908)


Si ingresas por ejemplo "Animation", mostrará las películas que pertenezcan a ese género. Si no se encuentra  en los datos o lo escribiste mal, te indicará que no se encuentra en la base de datos.



`5) Buscar por década: `


![Captura de pantalla 2024-05-05 165335](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/20e27da0-4ff7-4d39-9b92-8f8619839d5b)


Si ingresas por ejemplo "2010", mostrará las películas que pertenezcan a esa década. Si no se encuentra en los datos o la escribiste mal, te indicará que no se encuentra en la base de datos. No intentes ingresar "20" o "10", ya que hay películas del 1900 y del 2000, por lo que solo permite que ingreses "1970", "2010".



`6) Buscar por rango de calificaciones: `


![Captura de pantalla 2024-05-05 165426](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/8b23d06e-b73a-4422-b7d5-c12e2c86feb3)


Si ingresas por ejemplo "4.1", y "5.6", mostrará todas las películas que estén calificadas dentro de ese rango. Si no se encuentran películas o escribirste un rango inválido, te indicará que no hay películas que estén dentro de esas calificaciones.



`7) Buscar por década y género: `


![Captura de pantalla 2024-05-05 165447](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/d3cffd17-2aa5-45d5-8320-38dcd9ffd5c8)


Si ingresas por ejemplo "Crime" y luego "2010", mostrará todas las películas que compartan ese género y década. Emitirá avisos en caso de no encontrar alguno de los requisitos.



`8) Salir: ` 


![Captura de pantalla 2024-05-05 165513](https://github.com/IgnaciaBrahim/Tarea-2-Catalogo-Peliculas-CSV/assets/137849174/4d601fb3-31e0-43ab-b6d6-795554065ec1)


Al seleccionar opción 8, el programa deja de correr y se perderán los datos de las películas. Para usarlo de nuevo, deberás seleccionar siempre la opción 1 antes de comenzar a ocupar el programa.


