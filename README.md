# Ping concurrente en C++ (Sistemas Operativos)

Programa en C++ que hace ping en paralelo a una lista de direcciones IP y muestra un resumen del estado de cada una.

![C++](https://img.shields.io/badge/C%2B%2B-11-00599C?style=flat&logo=cplusplus&logoColor=white)
![Estado](https://img.shields.io/badge/estado-ejercicio%20académico-lightgrey?style=flat)
![Licencia](https://img.shields.io/badge/licencia-MIT-blue?style=flat)
![Último commit](https://img.shields.io/github/last-commit/ViceAguilera/Tarea-Sist.-Operativo-?style=flat)

<!-- Demo: agrega una captura o GIF en docs/demo.gif y descomenta la línea siguiente -->
<!-- <p align="center"><img src="docs/demo.gif" alt="Demostración del programa de ping concurrente" width="800"></p> -->

## Tabla de contenidos

- [Descripción](#descripción)
- [Estado del proyecto](#estado-del-proyecto)
- [Características](#características)
- [Tecnologías](#tecnologías)
- [Requisitos](#requisitos)
- [Instalación](#instalación)
- [Uso](#uso)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Licencia](#licencia)
- [Autor](#autor)

## Descripción

Ejercicio académico del ramo de Sistemas Operativos sobre hilos y exclusión mutua. El programa lee un archivo de texto con una IP por línea, lanza un hilo por cada una que ejecuta `ping -q -c <N>` y guarda la salida en `logs/<ip>.txt`. Al terminar, lee los logs y presenta una tabla con paquetes transmitidos, recibidos, perdidos y estado (UP/DOWN).

## Estado del proyecto

**Ejercicio académico.** Tarea del ramo de Sistemas Operativos, entregada y sin mantenimiento posterior.

## Características

- Un hilo (`std::thread`) por dirección IP.
- Mutex POSIX (`pthread_mutex_t`) alrededor de la ejecución del comando.
- Reporte final por IP: transmitidos, recibidos, perdidos y estado.
- Carpeta `logs/` con ejemplos de salida (`5.5.5.5`, `7.7.7.7`, `8.8.8.8`, `9.9.9.9`).

## Tecnologías

- C++ con `std::thread` y pthreads
- `make` y `g++`
- Comando `ping` de Linux

## Requisitos

- Linux (usa `ping -q -c` y rutas con `/`).
- `g++` con soporte para hilos y `make`.

## Instalación

```bash
make
```

## Uso

```bash
./programa <archivo_con_ips.txt> <numero_de_paquetes>
```

El archivo debe contener una IP por línea y la carpeta `logs/` debe existir. Para limpiar los binarios: `make clean`.

## Estructura del proyecto

```
Programa.cpp   # Código fuente
makefile       # Compilación
logs/          # Salidas de ping por IP
```

## Licencia

Distribuido bajo la licencia MIT. Ver [LICENSE](LICENSE).

## Autor

**Vicente Aguilera Arias** — [Portafolio](https://portfolio.iamsirius.cl) · [GitHub](https://github.com/ViceAguilera) · [LinkedIn](https://www.linkedin.com/in/vicenteaguilera/)
