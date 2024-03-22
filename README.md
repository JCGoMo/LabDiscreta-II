# Matemática Discreta II - 2024

## Informe de Proyecto - Parte 1

### Estudiantes

* Nombre
  * Email:
* Nombre
  * Email:
* Nombre
  * Email:

### Carrera: Licenciatura en Ciencias de la computación

---

## Contenido

...

---

## Notas internas

* No usar librerias externas mas alla de las basicas de C (verificar!)
* No crear algun archivo llamado aux
* No usar getline
* Permitido usar IA o codigos de años anteriores para sacar ideas o fragmentos
* No entregar version con archivos, funciones y prints de testeo (verificar!) ni con los grafos para testear, ni otros archivos como enunciado, cosas de git, make clean, etc (lo usual)

* Compilar con gcc -Wall -Wextra -O3 -std=c99 (ademas van a testear con otras flags, como -fsanitize=address, undefined, para grafos chicos)

### Diferencias al especificar formato de entrada:

> Comparaciones hechas con el enunciado de 2022 (esta bien, o era 2023?)

Los vertices ser ́an 0,1,2,...,n-1. (nota: en muchos ejemplos de la web, los v ́ertices son 1,2,...,n y en otros casos son cualesquiera n enteros de 32 bits. Este a ̃no elejimos 0,1,2,...,n-1 para que sea mas facil cargar el grafo y para disminuir la posibilidad de error con indices de arrays en C)

Ya no especifican si hay algun limite para los enteros (antes decian que eran de max 32 bits sin signo)

Especifican que pueden testear con archivos donde en vez de p edge n m tengan algo similar pero no correcto como p edgee n m, en cuyo caso tambien debemos devolver NULL

### ToDo

* Definir funciones Vecino, AsignarColor, ExtraerColores, ImportarColores (verificar si no han quedado funciones de mas que ya no sirvan)
* Hacer cambios a los archivos originales
* Hay convenciones a respetar en el proyecto? Idioma, comentarios, estilo, etc (DIMACS?)
* Testear mucho
