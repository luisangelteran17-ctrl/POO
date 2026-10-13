#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Lee una linea completa y termina si se cierra la entrada.
string leer_linea(const string& mensaje)
{
    string linea;
    cout << mensaje;

    if (!getline(cin, linea))
    {
        cerr << "\nNo se pudieron leer mas datos.\n";
        exit(EXIT_FAILURE);
    }

    return linea;
}

int leer_entero(const string& mensaje, int minimo, int maximo,
                const string& mensajeError)
{
    while (true)
    {
        string linea = leer_linea(mensaje);
        istringstream entrada(linea);
        int valor;
        char caracterExtra;

        if ((entrada >> valor) && !(entrada >> caracterExtra) &&
            valor >= minimo && valor <= maximo)
        {
            return valor;
        }

        cout << mensajeError << '\n';
    }
}

double leer_decimal(const string& mensaje, double minimo, double maximo,
                    const string& mensajeError)
{
    while (true)
    {
        string linea = leer_linea(mensaje);
        istringstream entrada(linea);
        double valor;
        char caracterExtra;

        if ((entrada >> valor) && !(entrada >> caracterExtra) &&
            valor >= minimo && valor <= maximo)
        {
            return valor;
        }

        cout << mensajeError << '\n';
    }
}

string leer_texto(const string& mensaje)
{
    string texto;

    while (true)
    {
        texto = leer_linea(mensaje);

        if (texto.find_first_not_of(" \t\r\n") != string::npos)
        {
            return texto;
        }

        cout << "El texto no puede estar vacio." << '\n';
    }
}

// Estudiante

class Estudiante
{
private:
    int codigo;
    string nombre;
    string apellido;
    double notaPrimerSemiciclo;
    double notaSegundoSemiciclo;
    double asistencia;

    // Cada metodo lee un solo dato
    void leer_codigo()
    {
        codigo = leer_entero(
            "Ingrese el codigo: ",
            1,
            INT_MAX,
            "Codigo invalido. Ingrese un entero positivo."
        );
    }

    void leer_nombre()
    {
        nombre = leer_texto("Ingrese el nombre: ");
    }

    void leer_apellido()
    {
        apellido = leer_texto("Ingrese el apellido: ");
    }

    void leer_nota_primer_semiciclo()
    {
        notaPrimerSemiciclo = leer_decimal(
            "Ingrese la nota del primer semiciclo: ",
            0.0,
            10.0,
            "Nota invalida. Debe estar entre 0 y 10."
        );
    }

    void leer_nota_segundo_semiciclo()
    {
        notaSegundoSemiciclo = leer_decimal(
            "Ingrese la nota del segundo semiciclo: ",
            0.0,
            10.0,
            "Nota invalida. Debe estar entre 0 y 10."
        );
    }

    void leer_asistencia()
    {
        asistencia = leer_decimal(
            "Ingrese el porcentaje de asistencia: ",
            0.0,
            100.0,
            "Asistencia invalida. Debe estar entre 0 y 100."
        );
    }

public:
    Estudiante()
    {
        codigo = 0;
        notaPrimerSemiciclo = 0;
        notaSegundoSemiciclo = 0;
        asistencia = 0;
    }

    // Coordina la lectura de los datos del estudiante
    void leer()
    {
        leer_codigo();
        leer_nombre();
        leer_apellido();
        leer_nota_primer_semiciclo();
        leer_nota_segundo_semiciclo();
        leer_asistencia();
    }

    double calcular_promedio() const
    {
        return (notaPrimerSemiciclo + notaSegundoSemiciclo) / 2.0;
    }

    string clasificar() const
    {
        double promedio = calcular_promedio();

        if (asistencia < 75)
        {
            return "REPROBADO";
        }

        if (promedio >= 7)
        {
            return "APROBADO";
        }

        if (promedio >= 4)
        {
            return "RECUPERACION";
        }

        return "REPROBADO";
    }

    // Muestra solamente los datos de un estudiante
    void mostrar_datos(size_t numero) const
    {
        cout << "\nDATOS DEL ESTUDIANTE "
                  << numero << '\n';
        cout << "---------------------------------" << '\n';
        cout << "Codigo:         " << codigo << '\n';
        cout << "Estudiante:     " << nombre
                  << " " << apellido << '\n';
        cout << "Nota 1:         " << notaPrimerSemiciclo << '\n';
        cout << "Nota 2:         " << notaSegundoSemiciclo << '\n';
        cout << "Nota acumulada: " << calcular_promedio() << '\n';
        cout << "Asistencia:     " << asistencia << "%" << '\n';
        cout << "Estado:         " << clasificar() << '\n';
    }
};

// Curso

class Curso
{
private:
    string asignatura;
    int pao;
    int paralelo;

    // Vector dinamico de estudiantes
    vector<Estudiante> estudiantes;

    void leer_asignatura()
    {
        asignatura = leer_texto("Ingrese el nombre de la asignatura: ");
    }

    void leer_pao()
    {
        pao = leer_entero(
            "Ingrese el PAO: ",
            1,
            INT_MAX,
            "PAO invalido. Ingrese un entero positivo."
        );
    }

    void leer_paralelo()
    {
        paralelo = leer_entero(
            "Ingrese el paralelo: ",
            1,
            INT_MAX,
            "Paralelo invalido. Ingrese un entero positivo."
        );
    }

    int leer_cantidad_estudiantes()
    {
        return leer_entero(
            "Ingrese la cantidad de estudiantes (1-40): ",
            1,
            40,
            "Cantidad invalida. Debe estar entre 1 y 40."
        );
    }

    // Ajusta el vector y lee cada estudiante por su posicion
    void leer_estudiantes(int cantidad)
    {
        estudiantes.clear();
        estudiantes.resize(cantidad);

        for (int i = 0; i < cantidad; i++)
        {
            cout << "\nESTUDIANTE " << i + 1 << '\n';
            cout << "---------------------------" << '\n';

            estudiantes[i].leer();
        }
    }

    void mostrar_datos_curso() const
    {
        cout << "\nDATOS DEL CURSO" << '\n';
        cout << "----------------------------------" << '\n';
        cout << "Asignatura:            " << asignatura << '\n';
        cout << "PAO:                   " << pao << '\n';
        cout << "Paralelo:              " << paralelo << '\n';
        cout << "Numero de estudiantes: "
                  << estudiantes.size() << '\n';
    }

    void mostrar_estudiantes() const
    {
        for (size_t i = 0; i < estudiantes.size(); i++)
        {
            estudiantes[i].mostrar_datos(i + 1);
        }
    }

public:
    Curso()
    {
        pao = 0;
        paralelo = 0;
    }

    // Coordina la lectura de los datos del curso
    void leer()
    {
        leer_asignatura();
        leer_pao();
        leer_paralelo();

        int cantidad = leer_cantidad_estudiantes();

        leer_estudiantes(cantidad);
    }

    // Devuelve el promedio mas alto del curso
    double calcular_nota_maxima() const
    {
        if (estudiantes.empty())
        {
            return 0.0;
        }

        double maxima = estudiantes[0].calcular_promedio();

        for (size_t i = 1; i < estudiantes.size(); i++)
        {
            double promedio = estudiantes[i].calcular_promedio();

            if (promedio > maxima)
            {
                maxima = promedio;
            }
        }

        return maxima;
    }

    // Devuelve el promedio mas bajo del curso
    double calcular_nota_minima() const
    {
        if (estudiantes.empty())
        {
            return 0.0;
        }

        double minima = estudiantes[0].calcular_promedio();

        for (size_t i = 1; i < estudiantes.size(); i++)
        {
            double promedio = estudiantes[i].calcular_promedio();

            if (promedio < minima)
            {
                minima = promedio;
            }
        }

        return minima;
    }

    void mostrar_notas_extremas() const
    {
        if (estudiantes.empty())
        {
            cout << "\nNo hay estudiantes registrados." << '\n';
            return;
        }

        cout << "\nRESUMEN DE NOTAS DEL CURSO" << '\n';
        cout << "----------------------------------" << '\n';

        cout << "Promedio maximo: "
                  << calcular_nota_maxima() << '\n';

        cout << "Promedio minimo: "
                  << calcular_nota_minima() << '\n';
    }

    // Coordina la visualizacion de toda la informacion
    void mostrar_datos() const
    {
        mostrar_datos_curso();
        mostrar_estudiantes();
        mostrar_notas_extremas();
    }
};

// Programa principal

int main()
{
    cout << fixed << setprecision(2);

    Curso curso;

    curso.leer();
    curso.mostrar_datos();

    return 0;
}
