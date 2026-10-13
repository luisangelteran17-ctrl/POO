# Registro de un curso

Ejercicio con las clases `Estudiante` y `Curso` en `Curso.cpp`. Solo incluye `<iostream>` y `<vector>`.

Solo se validan la cantidad de estudiantes (1 a 40) y las dos notas (0 a 10). Si se ingresan letras o valores fuera de esos rangos, se solicita nuevamente.

El codigo, PAO, paralelo y asistencia se leen directamente, sin validar sus rangos. Los nombres, apellidos y la asignatura se leen como una palabra, sin controlar espacios ni contenido.

Los textos se guardan en vectores de caracteres para no necesitar `<string>`. No hay punteros declarados, `exit`, `EXIT_FAILURE`, `stringstream` ni `numeric_limits`.

Se conservan las reglas del ejercicio: menos de 75% de asistencia implica REPROBADO; con al menos 75%, se aprueba desde 7, se va a RECUPERACION desde 4 y se reprueba por debajo de 4. El maximo y minimo se calculan en un solo recorrido.

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Curso.cpp -o curso
./curso
```
