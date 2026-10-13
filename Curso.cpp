#include <iostream>
#include <string>
using namespace std;

// Comprueba si una linea esta vacia o solo tiene espacios.
bool solo_espacios(string texto)
{
    for (size_t i = 0; i < texto.length(); i++)
    {
        if (texto[i] != ' ' && texto[i] != '\t' && texto[i] != '\r')
        {
            return false;
        }
    }
    return true;
}

// maximo = 0 permite cualquier entero positivo que quepa en un int.
int leer_entero(string mensaje, int maximo = 0)
{
    int valor;
    string resto;

    while (true)
    {
        cout << mensaje;
        cin >> valor;

        if (cin.fail())
        {
            if (cin.eof()) return 0;
            cin.clear();
            getline(cin, resto);
        }
        else
        {
            getline(cin, resto);
            if (solo_espacios(resto) && valor > 0 &&
                (maximo == 0 || valor <= maximo))
            {
                return valor;
            }
        }

        cout << "Ingrese un entero positivo";
        if (maximo > 0)
        {
            cout << " entre 1 y " << maximo;
        }
        cout << ".\n";
    }
}

double leer_decimal(string mensaje, double maximo)
{
    double valor;
    string resto;

    while (true)
    {
        cout << mensaje;
        cin >> valor;

        if (cin.fail())
        {
            if (cin.eof()) return -1;
            cin.clear();
            getline(cin, resto);
        }
        else
        {
            getline(cin, resto);
            if (solo_espacios(resto) && valor >= 0 && valor <= maximo)
            {
                return valor;
            }
        }

        cout << "Ingrese un numero entre 0 y " << maximo << ".\n";
    }
}

string leer_texto(string mensaje)
{
    string texto;

    while (true)
    {
        cout << mensaje;
        if (!getline(cin, texto))
        {
            return "";
        }
        if (!solo_espacios(texto))
        {
            return texto;
        }
        cout << "El texto no puede estar vacio.\n";
    }
}

class Estudiante
{
private:
    int codigo;
    string nombre;
    string apellido;
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
        codigo = leer_entero("Ingrese el codigo del estudiante: ");
        if (codigo == 0) return false;

        nombre = leer_texto("Ingrese el nombre: ");
        if (nombre == "") return false;

        apellido = leer_texto("Ingrese el apellido: ");
        if (apellido == "") return false;

        notaPrimerSemiciclo = leer_decimal("Ingrese la nota del primer semiciclo: ", 10);
        if (notaPrimerSemiciclo < 0) return false;

        notaSegundoSemiciclo = leer_decimal("Ingrese la nota del segundo semiciclo: ", 10);
        if (notaSegundoSemiciclo < 0) return false;

        asistencia = leer_decimal("Ingrese el porcentaje de asistencia: ", 100);
        if (asistencia < 0) return false;

        return true;
    }

    double calcular_promedio()
    {
        return (notaPrimerSemiciclo + notaSegundoSemiciclo) / 2;
    }

    string clasificar()
    {
        double promedio = calcular_promedio();
        if (asistencia < 75) return "REPROBADO";
        if (promedio >= 7) return "APROBADO";
        if (promedio >= 4) return "RECUPERACION";
        return "REPROBADO";
    }

    void mostrar_datos_estudiante(int numero)
    {
        cout << "\nDATOS DEL ESTUDIANTE " << numero << '\n';
        cout << "---------------------------------\n";
        cout << "Codigo:         " << codigo << '\n';
        cout << "Estudiante:     " << nombre << " " << apellido << '\n';
        cout << "Nota 1:         " << notaPrimerSemiciclo << '\n';
        cout << "Nota 2:         " << notaSegundoSemiciclo << '\n';
        cout << "Nota acumulada: " << calcular_promedio() << '\n';
        cout << "Asistencia:     " << asistencia << "%\n";
        cout << "Estado:         " << clasificar() << '\n';
    }
};

class Curso
{
private:
    string asignatura;
    int pao;
    int paralelo;
    Estudiante estudiante[40];
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
        asignatura = leer_texto("Ingrese el nombre de la asignatura: ");
        if (asignatura == "") return false;

        pao = leer_entero("Ingrese el PAO: ");
        if (pao == 0) return false;

        paralelo = leer_entero("Ingrese el paralelo: ");
        if (paralelo == 0) return false;

        int cantidad = leer_entero("Ingrese la cantidad de estudiantes (1-40): ", 40);
        if (cantidad == 0) return false;

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
        if (numeroEstudiantes == 0)
        {
            cout << "\nNo hay estudiantes registrados.\n";
            return;
        }

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
        cout << "Asignatura:            " << asignatura << '\n';
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
        cout << "\nEntrada interrumpida. No se completaron los datos del curso.\n";
        return 1;
    }
    curso.mostrar_datos();
    return 0;
}
