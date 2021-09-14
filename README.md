# Trabajo Práctico N°1 de Lenguajes de Programación III
Integrantes:
- Carin Martinez
- Paola Olmedo
- Matias Franco
- Willian Gonzalez
# Comenzando
Para empezar, descargamos el proyecto o clonamos el repositorio en una carpeta de su preferencia.

# Pre-requisitos
Para compilar y ejecutar el proyecto se necesita:
- Un sistema operativo GNU/Linux
- GCC y G++ instalados en su sistema

# Instalación 
Verificar que GCC (el GNU Compiler Collection) esté instalado en el sistema con el siguiente comando en una terminal:
$ gcc --version
En caso que no este instalado, se utiliza el siguiente comando para instalar gcc y g++:
$ sudo apt install build-essential
Instalar la libreria libtiff para el listing 2.9 con:
$ sudo apt-get install libtiff5-dev

# Compilación
Para compilar todos los listings, abra la terminal en la carpeta TP-LP3- que obtuvo del repositorio e ingrese el siguiente comando:
$ make
Para compilar un listing en específico, ejecutar el siguiente comando:
$ make listing-<numero del capitulo>.<numero de listing>
Los programas creados se guardaran en la carpeta bin, separados por capitulos.

# Clean up
Para eliminar los archivos .o en OBJ y todos los programas compilados en BIN, ejecute:
$ make clean
  
# Ejecutando los listings

  # Capitulo 1
  # Listing 1.1 / 1.2 / 1.3 :

El argumento de reciproco debe ser un numero entero.

$ ./reciprocal numero_entero

Ejemplo:

$ ./reciprocal 5

$ the reciprocal of 5 is 0.2
  
