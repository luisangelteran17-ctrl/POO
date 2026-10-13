# Registro de un curso

El programa usa las clases `Estudiante` y `Curso`. Cada dato se ingresa en su propio metodo, y las validaciones de notas se reutilizan en `leer_nota`.

`Curso` almacena los estudiantes en un `vector`, valida que la cantidad este entre 1 y 40 y calcula la nota maxima y minima del curso. Las notas deben estar entre 0 y 10. Los nombres se ingresan como una palabra.

La clasificacion requiere al menos 75% de asistencia: APROBADO desde 7, RECUPERACION desde 4 y REPROBADO por debajo de 4.

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Curso.cpp -o curso
./curso
```
