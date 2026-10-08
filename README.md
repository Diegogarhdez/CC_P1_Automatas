# CC_P1_Automatas
## Diego García Hernández

### Complejidad Computacional
### Práctica 1: Programar un simulador de un autómata con pila

La implementación por la que he optado ha sido la del automata por vaciado de pila.

## Ejecución

1. Colocarse en el directorio build

* ```cd build```

2. ejecutar el cmake

* ```cmake .. ```

3. ejecutar el make

* ```make ```

4. ejecutar el programa indicando la configuración, si se desea la traza y el fichero de cadenas

* ```./P1_Automata_pila -config APv-1.txt -trace n -in cadenas1.txt```

Si se indican solo los nombres de archivo, el programa busca primero en el directorio actual y después en `../tests` o `tests`. También se pueden indicar rutas explícitas, por ejemplo `tests/APv-1.txt`.

Las opciones implementadas son:

* ```-config <fichero>```
* ```-trace <y/n>```
* ```-in <fichero>```