#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <cmath>
#include <stdexcept>
using namespace std;

// Lectura reutilizable: rechaza letras, valores fuera del rango y entradas parciales.
template <typename T>
T leer_numero(T minimo, T maximo)
{
    string linea;
    T valor;
    while (getline(cin, linea))
    {
        istringstream entrada(linea);
        if (entrada >> valor && (entrada >> ws).eof() &&
            isfinite(static_cast<double>(valor)) && valor >= minimo && valor <= maximo)
            return valor;
        cout << "Valor invalido. Ingrese un valor entre " << minimo << " y " << maximo << ": ";
    }
    throw runtime_error("Entrada finalizada.");
}

string leer_texto()
{
    string texto;
    while (getline(cin, texto))
    {
        if (texto.find_first_not_of(" \t\r") != string::npos) return texto;
        cout << "El texto no puede estar vacio. Ingrese nuevamente: ";
    }
    throw runtime_error("Entrada finalizada.");
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
        nombre = "";
        apellido = "";
        notaPrimerSemiciclo = 0.0;
        notaSegundoSemiciclo = 0.0;
        asistencia = 0.0;
    }

    double leer_nota()
    {
        return leer_numero(0.0, 10.0);
    }

    void leer_codigo()
    {
        cout << "Ingrese el codigo del estudiante: ";
        codigo = leer_numero(1, numeric_limits<int>::max());
    }

    void leer_nombre()
    {
        cout << "Ingrese el nombre: ";
        nombre = leer_texto();
    }

    void leer_apellido()
    {
        cout << "Ingrese el apellido: ";
        apellido = leer_texto();
    }

    void leer_nota_primer_semiciclo()
    {
        cout << "Ingrese la nota del primer semiciclo: ";
        notaPrimerSemiciclo = leer_nota();
    }

    void leer_nota_segundo_semiciclo()
    {
        cout << "Ingrese la nota del segundo semiciclo: ";
        notaSegundoSemiciclo = leer_nota();
    }

    void leer_asistencia()
    {
        cout << "Ingrese el porcentaje de asistencia: ";
        asistencia = leer_numero(0.0, 100.0);
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

    double get_nota_segundo_parcial() const
    {
        return notaSegundoSemiciclo;
    }

    double calcular_nota_acumulada() const
    {
        return notaPrimerSemiciclo + notaSegundoSemiciclo;
    }

    double calcular_promedio() const
    {
        return (notaPrimerSemiciclo + notaSegundoSemiciclo) / 2;
    }

    string clasificar() const
    {
        double acumulada = calcular_nota_acumulada();

        if (asistencia < 75) return "REPROBADO";
        if (acumulada >= 14) return "APROBADO";
        if (acumulada >= 8) return "SUSPENSO";
        return "REPROBADO";
    }

    void mostrar_datos_estudiante(int numero) const
    {
        cout << "\nDATOS DEL ESTUDIANTE " << numero << endl;
        cout << "---------------------------------" << endl;
        cout << "Codigo:        " << codigo << endl;
        cout << "Estudiante:    " << nombre << " " << apellido << endl;
        cout << "Nota 1:        " << notaPrimerSemiciclo << endl;
        cout << "Nota 2:        " << notaSegundoSemiciclo << endl;
        cout << "Nota acumulada: " << calcular_nota_acumulada() << endl;
        cout << "Promedio:      " << calcular_promedio() << endl;
        cout << "Asistencia:    " << asistencia << "%" << endl;
        cout << "Estado:        " << clasificar() << endl;
    }
};

class Curso
{
private:
    string asignatura;
    int nivel;
    string paralelo;
    int numeroEstudiantes;
    vector<Estudiante> estudiantes;

public:
    Curso()
    {
        asignatura = "";
        nivel = 0;
        paralelo = "";
        numeroEstudiantes = 0;
    }

    void leer_asignatura()
    {
        cout << "Ingrese el nombre de la asignatura: ";
        asignatura = leer_texto();
    }

    void leer_nivel()
    {
        cout << "Ingrese el nivel: ";
        nivel = leer_numero(1, numeric_limits<int>::max());
    }

    void leer_paralelo()
    {
        cout << "Ingrese el paralelo: ";
        paralelo = leer_texto();
    }

    void leer_cantidad_estudiantes()
    {
        cout << "Ingrese la cantidad de estudiantes (1-40): ";
        numeroEstudiantes = leer_numero(1, 40);
    }

    void leer_estudiantes()
    {
        estudiantes.resize(numeroEstudiantes);

        for (int i = 0; i < numeroEstudiantes; i++)
        {
            cout << "\nESTUDIANTE " << i + 1 << endl;
            estudiantes[i].leer_datos();
        }
    }

    void ingresar_datos()
    {
        leer_asignatura();
        leer_nivel();
        leer_paralelo();
        leer_cantidad_estudiantes();
        leer_estudiantes();
    }

    double calcular_nota_maxima()
    {
        if (estudiantes.empty()) return 0.0;
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
        if (estudiantes.empty()) return 0.0;
        double minima = estudiantes[0].calcular_promedio();
        for (int i = 1; i < numeroEstudiantes; i++)
        {
            double promedio = estudiantes[i].calcular_promedio();
            if (promedio < minima) minima = promedio;
        }
        return minima;
    }

    void mostrar_estudiantes_menor_nota(double minima)
    {
        cout << "\nESTUDIANTES CON MENOR PROMEDIO" << endl;
        for (int i = 0; i < numeroEstudiantes; i++)
        {
            if (estudiantes[i].calcular_promedio() == minima)
                estudiantes[i].mostrar_datos_estudiante(i + 1);
        }
    }

    void mostrar_estudiantes_mayor_nota(double maxima)
    {
        cout << "\nESTUDIANTES CON MAYOR PROMEDIO" << endl;
        for (int i = 0; i < numeroEstudiantes; i++)
        {
            if (estudiantes[i].calcular_promedio() == maxima)
                estudiantes[i].mostrar_datos_estudiante(i + 1);
        }
    }

    void mostrar_estudiantes_segundo_parcial() const
    {
        cout << "\nESTUDIANTES CON SEGUNDO PARCIAL >= 7" << endl;
        bool encontrados = false;
        for (int i = 0; i < numeroEstudiantes; i++)
        {
            if (estudiantes[i].get_nota_segundo_parcial() >= 7)
            {
                estudiantes[i].mostrar_datos_estudiante(i + 1);
                encontrados = true;
            }
        }
        if (!encontrados) cout << "Ningun estudiante cumple la condicion." << endl;
    }

    void mostrar_datos()
    {
        double minima = calcular_nota_minima();
        double maxima = calcular_nota_maxima();

        cout << "\nDATOS DEL CURSO" << endl;
        cout << "----------------------------------" << endl;
        cout << "Asignatura:              " << asignatura << endl;
        cout << "Nivel:                   " << nivel << endl;
        cout << "Paralelo:                " << paralelo << endl;
        cout << "Numero de estudiantes:   " << numeroEstudiantes << endl;
        cout << "Promedio mas alto:       " << maxima << endl;
        cout << "Promedio mas bajo:       " << minima << endl;

        for (int i = 0; i < numeroEstudiantes; i++)
        {
            estudiantes[i].mostrar_datos_estudiante(i + 1);
        }

        mostrar_estudiantes_menor_nota(minima);
        mostrar_estudiantes_mayor_nota(maxima);
    }
};

int main()
{
    try
    {
        Curso curso;
        curso.ingresar_datos();
        curso.mostrar_datos();
        curso.mostrar_estudiantes_segundo_parcial();
    }
    catch (const runtime_error& error)
    {
        cerr << error.what() << endl;
        return 1;
    }
    return 0;
}
