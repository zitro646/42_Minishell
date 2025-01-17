# Minishell

![Texto alternativo](/req/bash_exec.gif)

~~El proyecto fue como pisar legos por amor al arte. 👀~~

## Descripción

Este proyecto consiste en implementar un **shell** funcional llamado `minishell`. El objetivo es crear un intérprete de comandos que imite el comportamiento de un shell básico como Bash, con algunas características específicas. El proyecto incluye la implementación de comandos, control de señales, redirecciones de entrada y salida, pipes, y más. La shell también debe manejar ciertas funciones y características relacionadas con la interacción del usuario y el entorno.

## Requerimientos
![Texto alternativo](/req/requirements.png)



## Funcionalidades Requeridas

### Características Generales

- **Mostrar un prompt** cuando se espera un nuevo comando.
- **Historial de comandos** funcional.
- **Búsqueda y ejecución de comandos** basados en la variable de entorno `PATH` o utilizando una ruta absoluta o relativa.
- **Manejo de señales**: no debe usar más de una variable global para indicar la señal recibida. La variable global solo puede contener el número de la señal recibida.
- **Citas (comillas)**:
  - Comillas simples (`'`) deben evitar que se interpreten los metacaracteres dentro de la secuencia citada.
  - Comillas dobles (`"`) deben evitar que se interpreten los metacaracteres dentro de la secuencia citada, excepto el símbolo `$` (signo de dólar).

### Redirecciones

- **Redirección de entrada (`<`)**: redirige la entrada estándar.
- **Redirección de salida (`>`)**: redirige la salida estándar.
- **Here Document (`<<`)**: debe recibir un delimitador y leer la entrada hasta que se vea una línea con el delimitador. No se debe actualizar el historial.
- **Redirección de salida en modo de anexado (`>>`)**: redirige la salida estándar, pero en modo de anexado.

### Pipex

- Implementar **pipex (`|`)**: la salida de cada comando en la tubería se conecta a la entrada del siguiente comando.

### Variables de Entorno

- Las variables de entorno, denotadas por `$`, deben expandirse a su valor correspondiente.
- **`$?`** debe expandirse al estado de salida del último pipeline en primer plano ejecutado.

### Manejo de Señales

- Implementar el manejo de señales **Ctrl-C**, **Ctrl-D** y **Ctrl-\\** de la siguiente manera:
  - **Ctrl-C** : Muestra un nuevo prompt en una nueva línea.
  - **Ctrl-D** : Sale de la shell.
  - **Ctrl-\\** : No debe hacer nada.

### Comandos Internos (Built-ins)

- Implementar los siguientes comandos internos:
  - `echo` con la opción `-n`.
  - `cd` con una ruta relativa o absoluta.
  - `pwd` sin opciones.
  - `export` sin opciones.
  - `unset` sin opciones.
  - `env` sin opciones ni argumentos.
  - `exit` sin opciones.

## Restricciones

- No se requiere gestionar fugas de memoria causadas por la función `readline()`, pero sí debes evitar fugas de memoria en el código que tú escribas.
- El código debe limitarse a lo que está descrito en los requisitos. Cualquier funcionalidad no mencionada no es obligatoria.
- En caso de dudas sobre el comportamiento, toma como referencia **bash**.

## Archivos a Entregar

- **Makefile** con las reglas: `NAME`, `all`, `clean`, `fclean`, `re`.
- Archivos de código: `*.h`, `*.c`.

## Cómo Compilar y Ejecutar

1. Clona este repositorio en tu máquina.
2. Entra en el directorio del proyecto.
3. Ejecuta el comando `make` para compilar el proyecto.
4. Ejecuta el shell con `./minishell`.

## En caso de error en la ejecucion (fallos comunes)

Este proyecto requiere de brew para usar el readline (deberia de estar instalado en el path) pero sino coincide hay que especificar el path 


## Autores

Este proyecto fue creado por [mortiz-d](https://github.com/zitro646) y [dlerma-c](https://github.com/danlerma)


