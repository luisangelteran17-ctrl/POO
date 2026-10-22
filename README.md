# Registro de un curso

Programa C++ con clases `Estudiante` y `Curso`, atributos privados y constructores que inicializan numeros en 0 y cadenas en "". Conserva el vector dinamico de hasta 40 estudiantes y los reportes de promedio maximo y minimo.

Permite ingresar asignatura, nivel y paralelo; registrar codigo, nombre, apellido, dos parciales de 0 a 10 y asistencia de 0 a 100; mostrar el curso y sus estudiantes clasificados; y mostrar los estudiantes con segundo parcial mayor o igual a 7 mediante un getter const.

Se conservan las reglas del proyecto: asistencia menor a 75% implica REPROBADO. Con asistencia de al menos 75%, acumulada >=14 implica APROBADO, acumulada >=8 implica SUSPENSO y menor a 8 implica REPROBADO. La acumulada es la suma de los dos parciales (sobre 20). Estos limites equivalen a los promedios 7 y 4 anteriores; el nuevo enunciado no especifica otros limites.

Se aceptan nombres y asignaturas con espacios y paralelos como A o 1. Las lecturas numericas rechazan texto, valores fuera de rango y entradas incompletas. El fin de entrada termina el programa sin bucles infinitos.

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Curso.cpp -o curso
./curso
```

Se mantiene el nombre Curso.cpp porque falta el formato de nombre de entrega en el enunciado recibido.
