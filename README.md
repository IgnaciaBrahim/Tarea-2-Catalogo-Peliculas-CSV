# Catálogo de Películas: Búsqueda a través de base de datos.

## Descripción:
Esta aplicación permite cargar un catálogo de películas para así buscar según los criterios de director, calificación, género, id, así como también se pueden buscar las películas que comparten género y década. 

## Instalación, compilación y ejecución:
### Por GitHub:
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar Repl.it para una rápida configuración y ejecución. Sigue estos pasos para comenzar:
1. Ingresa a [Replit](https://repl.it/)
2. Inicia sesión, o crea una cuenta si es que no tienes.
3. Una vez en tu página principal, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: [https://github.com/username/sistema-gestion-pacientes.git.](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1.git)
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

![Captura de pantalla 2024-04-21 180426](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/6624cf3e-8f0e-49f3-b82a-76ad20cb9482)

`1) Registrar paciente: `

![Captura de pantalla 2024-04-21 180053](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/88ddd2fd-a17f-4957-bb01-78ebdfe9e843)

Se ingresa a la paciente "Ana", paciente que acaba de ingresar al hospital. Su prioridad se asigna automáticamente a baja.

`2) Asignar prioridad: `

![Captura de pantalla 2024-04-21 180120](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/23caaf7e-5de8-4288-844b-197f4c445d00)

A la misma paciente, Ana, se le reasigna a la prioridad "ALTO", ya que su caso era grave. Así, se asegura que la atenderán pronto.

`3) Mostrar la lista de espera: `

![Captura de pantalla 2024-04-21 180151](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/4a12db5c-8c93-4e1d-8c92-3440bcdd379c)

Se muestra la lista de espera, en la que por el momento solo se encuentra la paciente Ana.

`5) Mostrar pacientes por prioridad: `

Si seleccionamos la prioridad "ALTO", podremos ver que Ana se encuentra en esa prioridad.

![Captura de pantalla 2024-04-21 180246](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/4a5f0d2d-3256-48c8-9c0a-b688f7f0743a)

`4) Atender al siguiente paciente: `

Se visualiza la lista de espera del hospital, en donde Ana es la única paciente y está primero en la lista. Al atenderla, se elimina de la lista de pacientes.

![Captura de pantalla 2024-04-21 180307](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/5798b5b6-5775-4c3d-b8b5-c4a009019ab9)

`6) Salir: `

![Captura de pantalla 2024-04-21 180321](https://github.com/IgnaciaBrahim/Gestion-Hospitalaria-Tarea-1/assets/137849174/8417d4c4-a1fe-42e2-b49a-c1efa6d4bf8d)

Para salir del sistema, se selecciona la opción 6. No se podrá volver a acceder a los datos que se habían ingresado antes.
