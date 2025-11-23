# Proyecto de Estructuras Dinámicas de Datos 2025C

Este proyecto es una implementación en C++ de un sistema de gestión de linaje real basado en estructuras de datos dinámicas (Árboles Binarios) sin el uso de librerías de terceros.

El programa permite cargar un linaje desde un archivo CSV, visualizar la línea de sucesión y calcular automáticamente quién debe heredar el trono basándose en reglas estrictas de primogenitura, edad y género.

## Características

* **Carga de Datos:** Lectura y parseo manual de archivos `.csv` para construir un Árbol Binario en memoria.
* **Visualización:** Muestra la línea de sucesión actual mediante un recorrido recursivo.
* **Motor de Sucesión:** Algoritmo de búsqueda en profundidad que determina el heredero correcto priorizando:
    * Hijos (Rama izquierda) antes que Hermanos (Rama derecha).
    * Varones menores de 70 años.
    * Mujeres (si no hay varones aptos).
    * Retiro forzoso del Rey al cumplir 71 años o morir.
* **Edición:** Capacidad de modificar atributos de los nobles (edad, estado vital) en tiempo de ejecución.

## Estructura del Proyecto

El proyecto sigue una estructura estandarizada para separar código fuente y ejecutables:

royal_project/
│
├── README.md           # Este archivo
├── src/
│   └── main.cpp        # Código fuente único (C++)
└── bin/
    ├── royal_app.exe   # Ejecutable (generado tras compilar)
    └── royal_data.csv  # Base de datos inicial

## Cómo Compilar

**Si el main.exe no existe en la carpeta bin usar:**

g++ src/main.cpp -o bin/main.exe

**Si ya el main.exe existe en la carpeta bin usar:**

./bin/main.exe


