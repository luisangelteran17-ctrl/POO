#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Lee un entero dentro del rango indicado.
int leer_entero(string mensaje, int minimo, int maximo)
{
    int valor;
    cout << mensaje;
    cin >> valor;

    while (cin.fail() || valor < minimo || valor > maximo)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Valor invalido. Ingrese un numero entre "
             << minimo << " y " << maximo << ": ";
        cin >> valor;
    }
    return valor;
}

// Lee una nota entre 0 y 10.
double leer_nota(string mensaje)
{
    double nota;
    cout << mensaje;
    cin >> nota;

    while (cin.fail() || nota < 0 || nota > 10)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Nota invalida. Ingrese una nota entre 0 y 10: ";
        cin >> nota;
    }
    return nota;
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

    void leer_codigo()
    {
        cout << "Ingrese el codigo del estudiante: ";
        cin >> codigo;
    }

    void leer_nombre()
    {
        cout << "Ingrese el nombre: ";
        cin >> nombre;
    }

    void leer_apellido()
    {
        cout << "Ingrese el apellido: ";
        cin >> apellido;
    }

    void leer_nota_primer_semiciclo()
    {
        notaPrimerSemiciclo = leer_nota("Ingrese la nota del primer semiciclo: ");
    }

    void leer_nota_segundo_semiciclo()
    {
        notaSegundoSemiciclo = leer_nota("Ingrese la nota del segundo semiciclo: ");
    }

    void leer_asistencia()
    {
        cout << "Ingrese el porcentaje de asistencia: ";
        cin >> asistencia;
    }

public:
    Estudiante()
    {
        codigo = 0;
        notaPrimerSemiciclo = 0;
        notaSegundoSemiciclo = 0;
        asistencia = 0;
    }

    void leer_datos()
    {
        leer_codigo();
        leer_nombre();
        leer_apellido();
        leer_nota_primer_semiciclo();
        leer_nota_segundo_semiciclo();
        leer_asistencia();
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
    int numeroEstudiantes;
    vector<Estudiante> estudiantes;

    void leer_asignatura()
    {
        cout << "Ingrese el nombre de la asignatura: ";
        cin >> asignatura;
    }

    void leer_pao()
    {
        cout << "Ingrese el PAO: ";
        cin >> pao;
    }

    void leer_paralelo()
    {
        cout << "Ingrese el paralelo: ";
        cin >> paralelo;
    }

    void leer_cantidad_estudiantes()
    {
        numeroEstudiantes = leer_entero(
            "Ingrese la cantidad de estudiantes (1-40): ", 1, 40);
    }

    void leer_estudiantes()
    {
        estudiantes.resize(numeroEstudiantes);

        for (int i = 0; i < numeroEstudiantes; i++)
        {
            cout << "\nESTUDIANTE " << i + 1 << '\n';
            cout << "---------------------------\n";
            estudiantes[i].leer_datos();
        }
    }

public:
    Curso()
    {
        pao = 0;
        paralelo = 0;
        numeroEstudiantes = 0;
    }

    void ingresar_datos()
    {
        leer_asignatura();
        leer_pao();
        leer_paralelo();
        leer_cantidad_estudiantes();
        leer_estudiantes();
    }

    double calcular_nota_maxima()
    {
        double maxima = estudiantes[0].calcular_promedio();
        for (int i = 1; i < numeroEstudiantes; i++)
        {
            double promedio = estudiantes[i].calcular_promedio();
            if (promedio > maxima) maxima = promedio;
        }
        return maxima;
    }

    double calcular_nota_minima()
    {
        double minima = estudiantes[0].calcular_promedio();
        for (int i = 1; i < numeroEstudiantes; i++)
        {
            double promedio = estudiantes[i].calcular_promedio();
            if (promedio < minima) minima = promedio;
        }
        return minima;
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
            estudiantes[i].mostrar_datos_estudiante(i + 1);
        }

        cout << "\nRESUMEN DE NOTAS DEL CURSO\n";
        cout << "Promedio maximo: " << calcular_nota_maxima() << '\n';
        cout << "Promedio minimo: " << calcular_nota_minima() << '\n';
    }
};

int main()
{
    Curso curso;
    curso.ingresar_datos();
    curso.mostrar_datos();
    return 0;
}
