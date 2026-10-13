# Registro de un curso

Ejercicio de C++ con las clases `Estudiante` y `Curso` en un solo archivo: `Curso.cpp`.

Registra de 1 a 40 estudiantes, calcula sus promedios y muestra el promedio maximo y minimo del curso.

- Asistencia menor al 75%: REPROBADO.
- Con al menos 75% de asistencia: APROBADO desde 7; RECUPERACION desde 4; REPROBADO por debajo de 4.
- Notas entre 0 y 10 y asistencia entre 0 y 100.

Para compilar y ejecutar desde la carpeta del proyecto:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Curso.cpp -o curso
./curso
```

Las funciones `leer_entero`, `leer_decimal` y `leer_texto` validan la entrada. Se conserva `sstream` para rechazar valores como `7abc` o `1.5` en un campo entero. Si se cierra la entrada antes de completar los datos, el programa termina con un mensaje de error.
