#include <iostream>
#include <vector>
using namespace std;

// Lee una palabra, sin validar el nombre ni permitir espacios.
vector<char> leer_palabra()
{
    vector<char> texto;
    char caracter;
    cin >> ws;

    while (cin.get(caracter) && caracter != ' ' && caracter != '\t' &&
           caracter != '\n' && caracter != '\r')
    {
        texto.push_back(caracter);
    }
    return texto;
}

void mostrar_palabra(const vector<char>& texto)
{
    for (size_t i = 0; i < texto.size(); i++)
    {
        cout << texto[i];
    }
}

// Retira el resto de una entrada numerica y detecta caracteres sobrantes.
bool terminar_linea()
{
    char caracter;
    bool valida = true;
    while (cin.get(caracter) && caracter != '\n')
    {
        if (caracter != ' ' && caracter != '\t' && caracter != '\r')
        {
            valida = false;
        }
    }
    return valida;
}

int leer_cantidad()
{
    int cantidad;
    while (true)
    {
        cout << "Ingrese la cantidad de estudiantes (1-40): ";
        cin >> cantidad;
        if (cin.fail())
        {
            if (cin.eof()) return 0;
            cin.clear();
            terminar_linea();
        }
        else
        {
            bool lineaValida = terminar_linea();
            if (lineaValida && cantidad >= 1 && cantidad <= 40)
            {
                return cantidad;
            }
        }
        cout << "Cantidad invalida. Debe estar entre 1 y 40.\n";
    }
}

double leer_nota()
{
    double nota;
    while (true)
    {
        cin >> nota;
        if (cin.fail())
        {
            if (cin.eof()) return -1;
            cin.clear();
            terminar_linea();
        }
        else
        {
            bool lineaValida = terminar_linea();
            if (lineaValida && nota >= 0 && nota <= 10)
            {
                return nota;
            }
        }
        cout << "Nota invalida. Ingrese una nota entre 0 y 10: ";
    }
}

class Estudiante
{
private:
    int codigo;
    vector<char> nombre;
    vector<char> apellido;
    double notaPrimerSemiciclo;
    double notaSegundoSemiciclo;
    double asistencia;

public:
    Estudiante()
    {
        codigo = 0;
        notaPrimerSemiciclo = 0;
        notaSegundoSemiciclo = 0;
        asistencia = 0;
    }

    bool leer_datos()
    {
        cout << "Ingrese el codigo del estudiante: ";
        cin >> codigo;
        cout << "Ingrese el nombre: ";
        nombre = leer_palabra();
        cout << "Ingrese el apellido: ";
        apellido = leer_palabra();

        cout << "Ingrese la nota del primer semiciclo: ";
        notaPrimerSemiciclo = leer_nota();
        if (notaPrimerSemiciclo < 0) return false;

        cout << "Ingrese la nota del segundo semiciclo: ";
        notaSegundoSemiciclo = leer_nota();
        if (notaSegundoSemiciclo < 0) return false;

        cout << "Ingrese el porcentaje de asistencia: ";
        cin >> asistencia;
        return true;
    }

    double calcular_promedio()
    {
        return (notaPrimerSemiciclo + notaSegundoSemiciclo) / 2;
    }

    void clasificar()
    {
        double promedio = calcular_promedio();
        if (asistencia < 75)
        {
            cout << "REPROBADO";
        }
        else if (promedio >= 7)
        {
            cout << "APROBADO";
        }
        else if (promedio >= 4)
        {
            cout << "RECUPERACION";
        }
        else
        {
            cout << "REPROBADO";
        }
    }

    void mostrar_datos_estudiante(int numero)
    {
        cout << "\nDATOS DEL ESTUDIANTE " << numero << '\n';
        cout << "---------------------------------\n";
        cout << "Codigo:         " << codigo << '\n';
        cout << "Estudiante:     ";
        mostrar_palabra(nombre);
        cout << " ";
        mostrar_palabra(apellido);
        cout << '\n';
        cout << "Nota 1:         " << notaPrimerSemiciclo << '\n';
        cout << "Nota 2:         " << notaSegundoSemiciclo << '\n';
        cout << "Nota acumulada: " << calcular_promedio() << '\n';
        cout << "Asistencia:     " << asistencia << "%\n";
        cout << "Estado:         ";
        clasificar();
        cout << '\n';
    }
};

class Curso
{
private:
    vector<char> asignatura;
    int pao;
    int paralelo;
    vector<Estudiante> estudiante;
    int numeroEstudiantes;

public:
    Curso()
    {
        pao = 0;
        paralelo = 0;
        numeroEstudiantes = 0;
    }

    bool ingresar_datos()
    {
        numeroEstudiantes = 0;
        cout << "Ingrese el nombre de la asignatura: ";
        asignatura = leer_palabra();
        cout << "Ingrese el PAO: ";
        cin >> pao;
        cout << "Ingrese el paralelo: ";
        cin >> paralelo;

        int cantidad = leer_cantidad();
        if (cantidad == 0) return false;
        estudiante.resize(cantidad);

        for (int i = 0; i < cantidad; i++)
        {
            cout << "\nESTUDIANTE " << i + 1 << '\n';
            cout << "---------------------------\n";
            if (!estudiante[i].leer_datos()) return false;
            numeroEstudiantes++;
        }
        return true;
    }

    void mostrar_notas_extremas()
    {
        if (numeroEstudiantes == 0) return;
        double maxima = estudiante[0].calcular_promedio();
        double minima = maxima;

        for (int i = 1; i < numeroEstudiantes; i++)
        {
            double promedio = estudiante[i].calcular_promedio();
            if (promedio > maxima) maxima = promedio;
            if (promedio < minima) minima = promedio;
        }

        cout << "\nRESUMEN DE NOTAS DEL CURSO\n";
        cout << "----------------------------------\n";
        cout << "Promedio maximo: " << maxima << '\n';
        cout << "Promedio minimo: " << minima << '\n';
    }

    void mostrar_datos()
    {
        cout << "\nDATOS DEL CURSO\n";
        cout << "----------------------------------\n";
        cout << "Asignatura:            ";
        mostrar_palabra(asignatura);
        cout << '\n';
        cout << "PAO:                   " << pao << '\n';
        cout << "Paralelo:              " << paralelo << '\n';
        cout << "Numero de estudiantes: " << numeroEstudiantes << '\n';

        for (int i = 0; i < numeroEstudiantes; i++)
        {
            estudiante[i].mostrar_datos_estudiante(i + 1);
        }
        mostrar_notas_extremas();
    }
};

int main()
{
    Curso curso;
    if (!curso.ingresar_datos())
    {
        cout << "\nEntrada interrumpida.\n";
        return 1;
    }
    curso.mostrar_datos();
    return 0;
}
