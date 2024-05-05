#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Las películas tienen varios directores o uno solo entonces los cree como lista.
typedef struct {
  char id[100];
  char title[100];
  List * genres;
  List * director;
  float rating;
  int year;
} Film;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("Bienvenid@, has entrado al menú principal del catálogo de películas.\n");
  puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  puts("     Base de Datos de Películas");
  puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

  puts("Selecciona una opción del menú:\n");
  puts("1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por director");
  puts("4) Buscar por género");
  puts("5) Buscar por década");
  puts("6) Buscar por rango de calificaciones");
  puts("7) Buscar por década y género");
  puts("8) Salir");
}

//Esta función se utiliza para inicializar mapas con claves de tipo string.
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

//Esta función se utiliza para inicializar mapas con claves de tipo entero. 
int is_equal_int(void *key1, void *key2) 
{
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

List *split_string(const char *string, const char *sep) 
{
  List *result = list_create(); //Queremos poblar lista director/genero.
  char *token = strtok((char *)string, sep); //Buscamos hasta la coma.

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++;
      //Avanzamos token hasta que ya no sea espacio.
    }

    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1; // -1 porque no cuenta '\0'
    while ((*end == ' ' && end > token) || (*end == '\n' && end > token)) 
    {
      //Agregé el end == salto de linea ya que si el director es uno solo no tiene end " ", y no se borra ese salto de linea que pertenece al CSV y luego nunca se pueden buscar esos directores.
      *end = '\0';
      end--;
      //Borra los espacios y actualiza el final
    }

    // Copiar el token sin espacio en un nuevo string
    char *new_token = strdup(token);
    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token);
    // Obtener el siguiente token
    token = strtok(NULL, sep);
  }

  return result; //Lista
}
//Carga películas desde un archivo CSV y las almacena en un mapa por ID.
void cargar_peliculas(Map *pelis_byid) 
{
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }
  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); 

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    Film *pelicula = (Film *)malloc(sizeof(Film)); //reserva

    //Asignaciones del struct Film:
    strcpy(pelicula->id, campos[1]);    
    strcpy(pelicula->title, campos[5]); 
    //Separadores de los datos en genero y director:
    char * sep = ",";
    pelicula->genres = split_string(campos[11], sep);
    pelicula->director = split_string(campos[14], sep);
    pelicula->year = atoi(campos[10]);
    pelicula->rating = atof(campos[8]);

    //Ya preparamos la struct film para insertarlo en el mapa:
    map_insert(pelis_byid, pelicula->id, pelicula);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas

  //Vamos a ver si la persona quiere ver las películas cargadas:
  char opcion;
  while(1)
  {
    printf("¿Desea ver las películas cargadas? (s/n): ");
    scanf(" %c", &opcion);
    switch(opcion)
    {
      case 's':
        printf("Catalogo de peliculas\n\n");
        //Recorrido
        MapPair *par = map_first(pelis_byid);
        while (par != NULL) 
        {
          Film *peli = par->value;
          printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
          printf("ID: %s\nTítulo: %s\nAño: %d\n", peli->id, peli->title, peli->year);
          par = map_next(pelis_byid); // Avanza al siguiente par en el mapa
        }
        printf("\n\n");
        return;
      case 'n':
        printf("No se mostrarán las películas cargadas.\n\n");
        return;
      default:
        printf("Opción inválida. Vuelva a insertar una opción válida.\n\n");
        break;
      }
  }
}

//Tomamos el mapa llenado por la carga de los archivos (ID) y llenamos los mapas que tienen como clave un valor numerico, que coinciden en que tienen en su "value" una lista. Podría haber reutilizado código haciendo otra funcion de llenado dentro de esta. :)
void poblar_mapas_numericos(Map *id , Map *cal, Map *dec)
{
  MapPair * par = map_first(id);
  //Recorrido del mapa ID  
  while (par != NULL)
  {
    Film *peli = par->value; //valor del par es FILM.
    //Primero llenamos el de decada
    int *decada = (int *)malloc(sizeof(int));
    *decada = (peli->year) - ((peli->year) % 10); 
    //Calculo de década :) 2009 - 9 por ej
    MapPair * dec_par = map_search(dec, decada);
    if(dec_par == NULL)
    {
      //No existe la decada en el mapa, creamos la lista de películas que va en el value:
      List * list_dec_map = list_create();
      //Insertamos la película en dicha lista
      list_pushBack(list_dec_map, peli);
      //Insertamos al mapa la decada y la lista de películas
      map_insert(dec, decada, list_dec_map);
    }
    else
    {
      //Ya existe la lista así que la preparamos para poner el Film en el final:
      List * list_dec_aux = dec_par->value;
      list_pushBack(list_dec_aux, peli);
    }
    
    //Ahora llenamos el mapa de calificaciones:
    float * calif = (float *)malloc(sizeof(float)); //Reservamos memoria ya que acepta punteros
    *calif = peli->rating; //Desreferencia para obtener el valor.
    MapPair * cal_par = map_search(cal, calif);
    if(cal_par == NULL)
    {
      //No está en el mapa:
      List * list_cal_map = list_create();
      list_pushBack(list_cal_map, peli);
      map_insert(cal, calif, list_cal_map);
    }
    else
    {
      //Ya está en el mapa:
      List * list_cal_aux = cal_par->value; // el value es una lista como establecí anteriormente así que usamos auxiliar para hacer push_back:
      list_pushBack(list_cal_aux, peli);
    }
    par = map_next(id); //Siguiente película!
  }
}

//A través del mapa llenado por la carga de los archivos (ID) llenamos los mapas que tienen como clave una cadena, que coinciden en que tienen en su "value" una lista.
void poblar_mapas_cadena(Map *id, Map *gen, Map *dir)
{
  MapPair * par = map_first(id);
  //Recorrido del mapa ID
  while (par != NULL)
  {
    Film *peli = par->value; //valor del par es FILM.
    //Primero vamos a agregar al mapa de generos. 
    //Como es una lista de generos la que tiene la pelicula, debemos recorrerla e insertar la película en cada genero al que pertenezca.
    char * genero = list_first(peli->genres);
    while(genero != NULL)
    {
      MapPair * gen_par = map_search(gen, genero);
    //Si la clave no existe, creamos la lista de Films que irán en el v alue del mapa por generos, hacemos pushback a la pelicula en la lista e insertamos el genero a el mapa.
      if(gen_par == NULL)
      {
        List * list_gen_map = list_create();
        list_pushBack(list_gen_map, peli);
        map_insert(gen, genero, list_gen_map);
      }
      else
      {
        //Significa que ya existe el genero, entonces solo hacemos pushback en la lista de Films del value. 
        //Como gen_par es el par "posicion" en donde debería ir agregado la pelicula, hacemos pushback a su value.
        List * list_gen_aux = gen_par->value;
        list_pushBack(list_gen_aux, peli);
      }
      genero = list_next(peli->genres);
    }
    
    // Ahora hacemos lo mismo para el mapa de directores:
    char *director = list_first(peli->director);
    while (director != NULL)
    {
      MapPair *dir_par = map_search(dir, director);
      if (dir_par == NULL)
      {
        // No existe esa clave en el mapa, creamos la lista de películas y la insertamos.
        List *list_dir = list_create();
        list_pushBack(list_dir, peli);
        map_insert(dir, director, list_dir);
      }
      else
      {
        // Ya existe esa clave en el mapa, simplemente agregamos la película a la lista de películas del director.
        List *list_dir_aux = dir_par->value;
        list_pushBack(list_dir_aux, peli);
      }
      director = list_next(peli->director);
    }
    // Avanzamos a la próxima película del mapa ID después de haber agregado a los dos mapas:
    par = map_next(id);
    }
}

//Busca el Key ID y muestra su película.
void buscar_por_id(Map *pelis_byid) {
  char id[10]; // Buffer para almacenar el ID de la película

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la película: ");
  scanf("%9s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(pelis_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la película
  if (pair != NULL) {
    Film *peli =
        pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título y el año de la película
    printf("Título: %s, Año: %d\n", peli->title, peli->year);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con id %s no existe\n", id);
  }
}

//Pide al usuario ingresar un género (key) y muestra todas las películas pertenecientes al género.
void buscar_por_gen(Map *mapa) {
  char genero[21]; 

  // Solicitamos al usuario el género para buscarlo:
  printf("\nIngrese el género que desea buscar: ");
  scanf(" %20[^\n]s", genero); 

  // Busca el par clave-valor en el mapa usando el genero, si se encuentra imprimimos la lista. Si no, informamos al usuario que no existe tal género en la base de datos.
  MapPair *pair = map_search(mapa, genero);
  if (pair != NULL) 
  {
    //Encontró el par, y como value es una lista utilizamos el TDA List para imprimir la lista de películas.
    printf("\nMostrando las películas pertenecientes al género %s:\n\n", genero);
    List *aux = pair->value;
    Film *peli = (Film *)list_first(aux);
    while (peli != NULL)
    {
      printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      printf("Título: %s\nAño: %d\n", peli->title, peli->year);
      peli = list_next(aux);
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\n");
  }
  else 
  {
    printf("El género %s no existe en la base de datos\n", genero);
  }
}

//Pide al usuario ingresar una década y encuentra y muestra las películas que pertenecen a esa década:
void buscar_por_dec(Map *mapa)
{
  int *decada = (int *)malloc(sizeof(int));
  printf("\nIngrese la década que desea buscar: ");
  scanf(" %d", decada);
  //Buscamos la decada en el mapa, si no existe informamos al usuario que no existe tal dec
  MapPair *pair = map_search(mapa, decada);
  printf("\nMostrando las películas de la década del %d:\n\n", *decada);
  if (pair != NULL)
  {

    //Encontró el par, y como value es una lista utilizamos el TDA List para imprimirla
    List * aux = pair->value;
    Film *peli = (Film *)list_first(aux);
    while (peli != NULL)
      {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Título: %s\nAño: %d\n", peli->title, peli->year);
        peli = list_next(aux);
        
      }
    printf("\n\n");
  }
  else
  {
    printf("No existe la década %d en la base de datos\n",*(decada));
  }
  free(decada);
}

//Pide al usuario que ingrese el nombre de un director/a y muestra todas las películas dirigidas por él/ella.
void buscar_por_dir(Map *mapa) 
{
  char director[30]; 

  // Solicitamos al usuario el género para buscarlo:
  printf("\nIngrese al director/a que desea buscar: ");
  scanf(" %29[^\n]s", director); 

  // Busca el par clave-valor en el mapa usando el genero, si se encuentra imprimimos la lista. Si no, informamos al usuario que no existe tal género en la base de datos.
  MapPair *pair = map_search(mapa, director);
  if (pair != NULL) 
  {
    //Encontró el par, y como value es una lista utilizamos el TDA List para imprimir la lista de películas.
    printf("\nMostrando las películas dirigidas por %s:\n\n", director);
    List *aux = pair->value;
    Film *peli = (Film *)list_first(aux);
    while (peli != NULL)
    {
      printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      printf("Título: %s\nAño: %d\n", peli->title, peli->year);
      peli = list_next(aux);
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\n");
  }
  else 
  {
    printf("No existen películas del director/a %s en la base de datos\n", director);
  }
}

//Buscamos en el mapa de generos el que solicita el usuario/a, y luego dentro de la lista de películas de ese genero, verificamos si se encuentra en la decada especificada.
void buscar_por_dec_gen(Map *mapa)
{
  int decada;
  char genero[20];

  printf("\nIngrese el género de la/las películas que desea buscar: \n");
  scanf(" %s", genero);

  //Busco el genero
  MapPair *pair = map_search(mapa, genero);
  int contador = 0;
  if (pair != NULL) 
  {
    //lista de peliculas del genero
    List *aux = pair->value;
    Film *peli = (Film *)list_first(aux);
    printf("\nIngrese la década de la/las películas que desea buscar: \n");
    scanf("%d", &decada);
    //Recorremos la lista en busca de peliculas pertenecientes a la decada y genero ingresados. Si no se encuentran, debemos informar que no hay para que no muestre la pantalla vacía:
    
    printf("\nMostrando las películas pertenecientes al género %s' de la década %d\n\n", genero, decada);
    while (peli != NULL)
    {
      if((decada <= (peli->year)) && ((peli->year) <= (decada + 9)))
      {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Título: %s\nAño: %d\n", peli->title, peli->year);
        contador++;
      }
      peli = list_next(aux);
    }

    if (contador == 0)
    {
      printf("No existen películas que pertenezcan al género %s y a la década %d\n", genero, decada);
    }
    else
    {
      printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      printf("\n\n");
    }
    
  }
  else
  {
    printf("El género %s no existe en la base de datos\n", genero);
  }
}

//Se le pide al usuario ingresar un rango de calificaciones y luego se muestran las películas que se encuentren en ese rango incluyendo los límites.
void buscar_por_cal(Map * mapa)
{
  float lim_inf;
  float lim_sup;
  printf("\nCalificaciones de las películas que desea buscar: \n");

  //Como se pide un rango de calificaciones, se le solicita el rango al usuario (inferior - superior)
  printf("\nIngrese el límite inferior del rango :\n");
  scanf("%f", &lim_inf);
  printf("\nIngrese el límite superior del rango :\n");
  scanf("%f", &lim_sup);

  //Luego imprimiremos las que estén dentro de ese rango incluyendo los límites:
  printf("\nMostrando las películas con calificación entre %.1f y %.1f:\n\n", lim_inf, lim_sup);
  int contador = 0;
  //Por si no hay películas en ese rango
  MapPair *par = map_first(mapa);
  while(par != NULL)
  {
    List * aux = par->value;
    Film * peli = (Film *)list_first(aux);

    //Recorremos el mapa de de calificaciones e imprimimos si encontramos películas ahí:
    while (peli != NULL)
    {
      if((peli->rating >= lim_inf) && (peli->rating <= lim_sup))
      {
        contador++;
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Título: %s\nAño: %d\nCalificación: %.1f\n", peli->title, peli->year, peli->rating);
      }
      peli = list_next(aux);
    }
    par = map_next(mapa);
  }
  if (contador == 0)
  {
    printf("No existen peliculas entre las calificaciones %.1f y %.1f. Por favor, prueba otro rango válido.", lim_inf, lim_sup);
  }
  printf("\n\n");
}

int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario

  // Creamos todos los mapas necesarios para las opciones del menú. 2 de ellos almacenan value tipo List *:
  Map *pelis_by_id = map_create(is_equal_str);
  Map *pelis_by_gen = map_create(is_equal_str);
  Map *pelis_by_dec = map_create(is_equal_int);
  Map *pelis_by_cal = map_create(is_equal_int);
  Map *pelis_by_dir = map_create(is_equal_str);

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_by_id);
      poblar_mapas_numericos(pelis_by_id, pelis_by_cal, pelis_by_dec);
      poblar_mapas_cadena(pelis_by_id, pelis_by_gen, pelis_by_dir);
      break;
    case '2':
      buscar_por_id(pelis_by_id);
      break;
    case '3':
      buscar_por_dir(pelis_by_dir);
      break;
    case '4':
      buscar_por_gen(pelis_by_gen);
      break;
    case '5':
      buscar_por_dec(pelis_by_dec);
      break;
    case '6':
      buscar_por_cal(pelis_by_cal);
      break;
    case '7':
      buscar_por_dec_gen(pelis_by_gen);
      break;
    case '8':
      printf("Saliendo del programa...\n");
      break;
    default:
      printf("Opción inválida. Intente nuevamente.\n");
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');
  //Liberamos memoria:
  free(pelis_by_id);
  free(pelis_by_gen);
  free(pelis_by_dec);
  free(pelis_by_cal);
  free(pelis_by_dir);
  return 0;
}