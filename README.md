# Registro de un curso

Ejercicio de C++ basado en el codigo del PDF RE7.EQUIPO 3, con las clases `Estudiante` y `Curso` en `Curso.cpp`.

Usa un arreglo fijo de 40 estudiantes, ciclos `for`, condiciones `if` y funciones propias para leer enteros, decimales y textos. No usa punteros, `template`, `vector`, `stringstream`, `numeric_limits` ni `exit`.

Las funciones de lectura usan `cin`, `getline`, `cin.fail()`, `cin.eof()` y `cin.clear()`. `clear()` permite recuperar la entrada despues de escribir letras donde se espera un numero; `getline` retira el resto de esa linea y permite nombres con espacios. Se rechazan numeros fuera de rango, enteros con decimales, valores fuera del tipo `int` y entradas como `7abc`.

- Cantidad de estudiantes: de 1 a 40. Si se ingresa 45, se solicita nuevamente.
- Codigo, PAO y paralelo: enteros positivos.
- Notas: entre 0 y 10. Asistencia: entre 0 y 100.
- Asistencia menor al 75%: REPROBADO.
- Con al menos 75% de asistencia: APROBADO desde 7; RECUPERACION desde 4; REPROBADO por debajo de 4.

Se conservan el promedio y la clasificacion de cada estudiante, ademas del resumen de notas de la version anterior. El promedio maximo y minimo se obtienen en un solo recorrido. Si la entrada se cierra, los metodos de lectura devuelven un resultado que permite a `main` terminar sin bucles infinitos ni mostrar datos incompletos.

Para compilar y ejecutar:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Curso.cpp -o curso
./curso
```
