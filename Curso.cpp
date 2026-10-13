
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>

// Funcion reutilizable para leer numeros dentro de un rango
template <typename T>
T leer_valor_en_rango(const std::string& mensaje,
                      T minimo,
                      T maximo,
                      const std::string& mensajeError)
{
    std::string linea;
    T valor;
    char caracterExtra;

    while (true)
    {
        std::cout << mensaje;
        std::getline(std::cin, linea);

        std::istringstream entrada(linea);

        if ((entrada >> valor) &&
            !(entrada >> caracterExtra) &&
            valor >= minimo &&
            valor <= maximo)
        {
            return valor;
        }

        std::cout << mensajeError << std::endl;
    }
}

// Funcion reutilizable para leer textos con espacios
std::string leer_texto(const std::string& mensaje)
{
    std::string texto;

    while (true)
    {
        std::cout << mensaje;
        std::getline(std::cin, texto);

        if (texto.find_first_not_of(" \t\r\n") != std::string::npos)
        {
            return texto;
        }

        std::cout << "El texto no puede estar vacio." << std::endl;
    }
}


// ==================================================
// CLASE ESTUDIANTE
// ==================================================

class Estudiante
{
private:
    int codigo;
    std::string nombre;
    std::string apellido;
    double notaPrimerSemiciclo;
    double notaSegundoSemiciclo;
    double asistencia;

    // Cada metodo lee un solo dato
    void leer_codigo()
    {
        codigo = leer_valor_en_rango<int>(
            "Ingrese el codigo: ",
            1,
            std::numeric_limits<int>::max(),
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
        notaPrimerSemiciclo = leer_valor_en_rango<double>(
            "Ingrese la nota del primer semiciclo: ",
            0.0,
            10.0,
            "Nota invalida. Debe estar entre 0 y 10."
        );
    }

    void leer_nota_segundo_semiciclo()
    {
        notaSegundoSemiciclo = leer_valor_en_rango<double>(
            "Ingrese la nota del segundo semiciclo: ",
            0.0,
            10.0,
            "Nota invalida. Debe estar entre 0 y 10."
        );
    }

    void leer_asistencia()
    {
        asistencia = leer_valor_en_rango<double>(
            "Ingrese el porcentaje de asistencia: ",
            0.0,
            100.0,
            "Asistencia invalida. Debe estar entre 0 y 100."
        );
    }

public:
    Estudiante()
        : codigo(0),
          nombre(""),
          apellido(""),
          notaPrimerSemiciclo(0.0),
          notaSegundoSemiciclo(0.0),
          asistencia(0.0)
    {
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

    std::string clasificar() const
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
    void mostrar_datos(std::size_t numero) const
    {
        std::cout << "\nDATOS DEL ESTUDIANTE "
                  << numero << std::endl;
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Codigo:         " << codigo << std::endl;
        std::cout << "Estudiante:     " << nombre
                  << " " << apellido << std::endl;
        std::cout << "Nota 1:         " << notaPrimerSemiciclo << std::endl;
        std::cout << "Nota 2:         " << notaSegundoSemiciclo << std::endl;
        std::cout << "Nota acumulada: " << calcular_promedio() << std::endl;
        std::cout << "Asistencia:     " << asistencia << "%" << std::endl;
        std::cout << "Estado:         " << clasificar() << std::endl;
    }
};


// ==================================================
// CLASE CURSO
// ==================================================

class Curso
{
private:
    std::string asignatura;
    int pao;
    int paralelo;

    // Vector dinamico de estudiantes
    std::vector<Estudiante> estudiantes;

    void leer_asignatura()
    {
        asignatura = leer_texto("Ingrese el nombre de la asignatura: ");
    }

    void leer_pao()
    {
        pao = leer_valor_en_rango<int>(
            "Ingrese el PAO: ",
            1,
            std::numeric_limits<int>::max(),
            "PAO invalido. Ingrese un entero positivo."
        );
    }

    void leer_paralelo()
    {
        paralelo = leer_valor_en_rango<int>(
            "Ingrese el paralelo: ",
            1,
            std::numeric_limits<int>::max(),
            "Paralelo invalido. Ingrese un entero positivo."
        );
    }

    int leer_cantidad_estudiantes()
    {
        return leer_valor_en_rango<int>(
            "Ingrese la cantidad de estudiantes (1-40): ",
            1,
            40,
            "Cantidad invalida. Debe estar entre 1 y 40."
        );
    }

    // Ingresa los estudiantes y reserva memoria una sola vez
    void leer_estudiantes(int cantidad)
    {
        estudiantes.clear();
        estudiantes.reserve(cantidad);

        for (int i = 0; i < cantidad; i++)
        {
            std::cout << "\nESTUDIANTE " << i + 1 << std::endl;
            std::cout << "---------------------------" << std::endl;

            estudiantes.emplace_back();
            estudiantes.back().leer();
        }
    }

    void mostrar_datos_curso() const
    {
        std::cout << "\nDATOS DEL CURSO" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Asignatura:            " << asignatura << std::endl;
        std::cout << "PAO:                   " << pao << std::endl;
        std::cout << "Paralelo:              " << paralelo << std::endl;
        std::cout << "Numero de estudiantes: "
                  << estudiantes.size() << std::endl;
    }

    void mostrar_estudiantes() const
    {
        for (std::size_t i = 0; i < estudiantes.size(); i++)
        {
            estudiantes[i].mostrar_datos(i + 1);
        }
    }

public:
    Curso()
        : asignatura(""), pao(0), paralelo(0)
    {
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

        for (std::size_t i = 1; i < estudiantes.size(); i++)
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

        for (std::size_t i = 1; i < estudiantes.size(); i++)
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
            std::cout << "\nNo hay estudiantes registrados." << std::endl;
            return;
        }

        std::cout << "\nRESUMEN DE NOTAS DEL CURSO" << std::endl;
        std::cout << "----------------------------------" << std::endl;

        std::cout << "Promedio maximo: "
                  << calcular_nota_maxima() << std::endl;

        std::cout << "Promedio minimo: "
                  << calcular_nota_minima() << std::endl;
    }

    // Coordina la visualizacion de toda la informacion
    void mostrar_datos() const
    {
        mostrar_datos_curso();
        mostrar_estudiantes();
        mostrar_notas_extremas();
    }
};


// ==================================================
// FUNCION PRINCIPAL
// ==================================================

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    Curso curso;

    curso.leer();
    curso.mostrar_datos();

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>

// Funcion reutilizable para leer numeros dentro de un rango
template <typename T>
T leer_valor_en_rango(const std::string& mensaje,
                      T minimo,
                      T maximo,
                      const std::string& mensajeError)
{
    std::string linea;
    T valor;
    char caracterExtra;

    while (true)
    {
        std::cout << mensaje;
        std::getline(std::cin, linea);

        std::istringstream entrada(linea);

        if ((entrada >> valor) &&
            !(entrada >> caracterExtra) &&
            valor >= minimo &&
            valor <= maximo)
        {
            return valor;
        }

        std::cout << mensajeError << std::endl;
    }
}

// Funcion reutilizable para leer textos con espacios
std::string leer_texto(const std::string& mensaje)
{
    std::string texto;

    while (true)
    {
        std::cout << mensaje;
        std::getline(std::cin, texto);

        if (texto.find_first_not_of(" \t\r\n") != std::string::npos)
        {
            return texto;
        }

        std::cout << "El texto no puede estar vacio." << std::endl;
    }
}


// ==================================================
// CLASE ESTUDIANTE
// ==================================================

class Estudiante
{
private:
    int codigo;
    std::string nombre;
    std::string apellido;
    double notaPrimerSemiciclo;
    double notaSegundoSemiciclo;
    double asistencia;

    // Cada metodo lee un solo dato
    void leer_codigo()
    {
        codigo = leer_valor_en_rango<int>(
            "Ingrese el codigo: ",
            1,
            std::numeric_limits<int>::max(),
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
        notaPrimerSemiciclo = leer_valor_en_rango<double>(
            "Ingrese la nota del primer semiciclo: ",
            0.0,
            10.0,
            "Nota invalida. Debe estar entre 0 y 10."
        );
    }

    void leer_nota_segundo_semiciclo()
    {
        notaSegundoSemiciclo = leer_valor_en_rango<double>(
            "Ingrese la nota del segundo semiciclo: ",
            0.0,
            10.0,
            "Nota invalida. Debe estar entre 0 y 10."
        );
    }

    void leer_asistencia()
    {
        asistencia = leer_valor_en_rango<double>(
            "Ingrese el porcentaje de asistencia: ",
            0.0,
            100.0,
            "Asistencia invalida. Debe estar entre 0 y 100."
        );
    }

public:
    Estudiante()
        : codigo(0),
          nombre(""),
          apellido(""),
          notaPrimerSemiciclo(0.0),
          notaSegundoSemiciclo(0.0),
          asistencia(0.0)
    {
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

    std::string clasificar() const
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
    void mostrar_datos(std::size_t numero) const
    {
        std::cout << "\nDATOS DEL ESTUDIANTE "
                  << numero << std::endl;
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Codigo:         " << codigo << std::endl;
        std::cout << "Estudiante:     " << nombre
                  << " " << apellido << std::endl;
        std::cout << "Nota 1:         " << notaPrimerSemiciclo << std::endl;
        std::cout << "Nota 2:         " << notaSegundoSemiciclo << std::endl;
        std::cout << "Nota acumulada: " << calcular_promedio() << std::endl;
        std::cout << "Asistencia:     " << asistencia << "%" << std::endl;
        std::cout << "Estado:         " << clasificar() << std::endl;
    }
};


// ==================================================
// CLASE CURSO
// ==================================================

class Curso
{
private:
    std::string asignatura;
    int pao;
    int paralelo;

    // Vector dinamico de estudiantes
    std::vector<Estudiante> estudiantes;

    void leer_asignatura()
    {
        asignatura = leer_texto("Ingrese el nombre de la asignatura: ");
    }

    void leer_pao()
    {
        pao = leer_valor_en_rango<int>(
            "Ingrese el PAO: ",
            1,
            std::numeric_limits<int>::max(),
            "PAO invalido. Ingrese un entero positivo."
        );
    }

    void leer_paralelo()
    {
        paralelo = leer_valor_en_rango<int>(
            "Ingrese el paralelo: ",
            1,
            std::numeric_limits<int>::max(),
            "Paralelo invalido. Ingrese un entero positivo."
        );
    }

    int leer_cantidad_estudiantes()
    {
        return leer_valor_en_rango<int>(
            "Ingrese la cantidad de estudiantes (1-40): ",
            1,
            40,
            "Cantidad invalida. Debe estar entre 1 y 40."
        );
    }

    // Ingresa los estudiantes y reserva memoria una sola vez
    void leer_estudiantes(int cantidad)
    {
        estudiantes.clear();
        estudiantes.reserve(cantidad);

        for (int i = 0; i < cantidad; i++)
        {
            std::cout << "\nESTUDIANTE " << i + 1 << std::endl;
            std::cout << "---------------------------" << std::endl;

            estudiantes.emplace_back();
            estudiantes.back().leer();
        }
    }

    void mostrar_datos_curso() const
    {
        std::cout << "\nDATOS DEL CURSO" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Asignatura:            " << asignatura << std::endl;
        std::cout << "PAO:                   " << pao << std::endl;
        std::cout << "Paralelo:              " << paralelo << std::endl;
        std::cout << "Numero de estudiantes: "
                  << estudiantes.size() << std::endl;
    }

    void mostrar_estudiantes() const
    {
        for (std::size_t i = 0; i < estudiantes.size(); i++)
        {
            estudiantes[i].mostrar_datos(i + 1);
        }
    }

public:
    Curso()
        : asignatura(""), pao(0), paralelo(0)
    {
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

        for (std::size_t i = 1; i < estudiantes.size(); i++)
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

        for (std::size_t i = 1; i < estudiantes.size(); i++)
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
            std::cout << "\nNo hay estudiantes registrados." << std::endl;
            return;
        }

        std::cout << "\nRESUMEN DE NOTAS DEL CURSO" << std::endl;
        std::cout << "----------------------------------" << std::endl;

        std::cout << "Promedio maximo: "
                  << calcular_nota_maxima() << std::endl;

        std::cout << "Promedio minimo: "
                  << calcular_nota_minima() << std::endl;
    }

    // Coordina la visualizacion de toda la informacion
    void mostrar_datos() const
    {
        mostrar_datos_curso();
        mostrar_estudiantes();
        mostrar_notas_extremas();
    }
};


// ==================================================
// FUNCION PRINCIPAL
// ==================================================

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    Curso curso;

    curso.leer();
    curso.mostrar_datos();

    return 0;
}
