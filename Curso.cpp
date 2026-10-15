#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
        double nota;
        do
        {
            cin >> nota;
            if (nota < 0 || nota > 10)
            {
                cout << "Nota invalida, Ingrese una nota entre 0 y 10: ";
            }
        } while (nota < 0 || nota > 10);
        return nota;
    }

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
        cin >> asistencia;
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

    double calcular_nota_acumulada()
    {
        return notaPrimerSemiciclo + notaSegundoSemiciclo;
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
        if (promedio >= 4) return "SUSPENSO";
        return "REPROBADO";
    }

    void mostrar_datos_estudiante(int numero)
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
    int pao;
    int paralelo;
    int numeroEstudiantes;
    vector<Estudiante> estudiantes;

public:
    Curso()
    {
        asignatura = "";
        pao = 0;
        paralelo = 0;
        numeroEstudiantes = 0;
    }

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
        do
        {
            cout << "Ingrese la cantidad de estudiantes (1-40): ";
            cin >> numeroEstudiantes;
            if (numeroEstudiantes < 1 || numeroEstudiantes > 40)
            {
                cout << "Cantidad invalida, Debe estar entre 1 y 40" << endl;
            }
        } while (numeroEstudiantes < 1 || numeroEstudiantes > 40);
    }

    void leer_estudiantes()
    {
        estudiantes.resize(numeroEstudiantes);

        for (int i = 0; i < numeroEstudiantes; i++)
        {
            cout << "\nESTUDIANTE " << i + 1 << endl;;
            estudiantes[i].leer_datos();
        }
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

    void mostrar_estudiantes_menor_nota(double minima)
    {
        cout << "\nESTUDIANTES CON MENOR NOTA ACUMULADA" << endl;
        for (int i = 0; i < numeroEstudiantes; i++)
        {
            if (estudiantes[i].calcular_promedio() == minima)
                estudiantes[i].mostrar_datos_estudiante(i + 1);
        }
    }

    void mostrar_estudiantes_mayor_nota(double maxima)
    {
        cout << "\nESTUDIANTES CON MAYOR NOTA ACUMULADA" << endl;
        for (int i = 0; i < numeroEstudiantes; i++)
        {
            if (estudiantes[i].calcular_promedio() == maxima)
                estudiantes[i].mostrar_datos_estudiante(i + 1);
        }
    }

    void mostrar_datos()
    {
        double minima = calcular_nota_minima();
        double maxima = calcular_nota_maxima();

        cout << "\nDATOS DEL CURSO" << endl;;
        cout << "----------------------------------" << endl;
        cout << "Asignatura:              " << asignatura << endl;
        cout << "PAO:                     " << pao << endl;
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
    Curso curso;
    curso.ingresar_datos();
    curso.mostrar_datos();
    return 0;
}
