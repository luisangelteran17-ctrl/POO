#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <climits>
#include <cctype>
using namespace std;

// Validaciones compartidas: cada lectura consume una linea completa.
string leer_texto(const string& mensaje)
{
    string texto;
    char caracter;
    do
    {
        cout << mensaje;
        texto = "";
        while (cin.get(caracter) && caracter != '\n')
            texto += caracter;
        if (!cin && texto.empty())
            throw runtime_error("Entrada finalizada.");

        int inicio = 0;
        int fin = static_cast<int>(texto.length());
        while (inicio < fin && isspace(static_cast<unsigned char>(texto[inicio])))
            inicio++;
        while (fin > inicio && isspace(static_cast<unsigned char>(texto[fin - 1])))
            fin--;
        texto = texto.substr(inicio, fin - inicio);
        if (texto.empty())
            cout << "El texto no puede estar vacio." << endl;
    } while (texto.empty());
    return texto;
}

int leer_entero(const string& mensaje, int minimo, int maximo)
{
    while (true)
    {
        string texto = leer_texto(mensaje);
        istringstream entrada(texto);
        int valor = 0;
        char sobrante;
        if ((entrada >> valor) && !(entrada >> sobrante)
            && valor >= minimo && valor <= maximo)
            return valor;
        cout << "Ingrese un entero entre " << minimo << " y " << maximo << "." << endl;
    }
}

string leer_numero(const string& mensaje)
{
    while (true)
    {
        string numero = leer_texto(mensaje);
        if (numero.find_first_not_of("0123456789") == string::npos)
            return numero;
        cout << "Ingrese solamente digitos." << endl;
    }
}

string convertir_mayusculas(string texto)
{
    for (char& caracter : texto)
        caracter = static_cast<char>(toupper(static_cast<unsigned char>(caracter)));
    return texto;
}

class Bus
{
private:
    string nombrePropietario;
    string apellidoPropietario;
    string numeroBus;
    int cantidadAsientos;
    string placa;
    string numeroOriginal;

public:
    Bus()
    {
        nombrePropietario = "";
        apellidoPropietario = "";
        numeroBus = "";
        cantidadAsientos = 0;
        placa = "";
        numeroOriginal = "";
    }

    void leer_nombre_propietario()
    {
        nombrePropietario = leer_texto("Ingrese el nombre del propietario: ");
    }

    void leer_apellido_propietario()
    {
        apellidoPropietario = leer_texto("Ingrese el apellido del propietario: ");
    }

    void leer_numero_bus()
    {
        numeroOriginal = leer_numero("Ingrese el numero original del bus: ");
        numeroBus = numeroOriginal;
    }

    void leer_cantidad_asientos()
    {
        cantidadAsientos = leer_entero("Ingrese la cantidad de asientos: ", 1, INT_MAX);
    }

    void leer_placa()
    {
        placa = convertir_mayusculas(leer_texto("Ingrese la placa: "));
    }

    void leer()
    {
        leer_nombre_propietario();
        leer_apellido_propietario();
        leer_numero_bus();
        leer_cantidad_asientos();
        leer_placa();
    }

    int getCantidadAsientos() const
    {
        return cantidadAsientos;
    }

    string get_nombre_propietario() const
    {
        return nombrePropietario;
    }

    string get_placa() const
    {
        return placa;
    }

    string get_numero_original() const
    {
        return numeroOriginal;
    }

    void actualizar_numero(const string& numeroCooperativa)
    {
        // Ejemplo del enunciado: cooperativa 40 + bus 10 = 4010.
        numeroBus = numeroCooperativa + numeroOriginal;
    }

    void mostrar() const
    {
        cout << "\nPropietario: " << nombrePropietario << " " << apellidoPropietario << endl;
        cout << "Numero del bus: " << numeroBus << endl;
        cout << "Cantidad de asientos: " << cantidadAsientos << endl;
        cout << "Placa: " << placa << endl;
    }
};

class Cooperativa
{
private:
    string nombre;
    vector<Bus> buses;

    bool bus_repetido(const Bus& candidato) const
    {
        for (const Bus& bus : buses)
        {
            if (bus.get_placa() == candidato.get_placa()
                || bus.get_numero_original() == candidato.get_numero_original())
                return true;
        }
        return false;
    }

public:
    Cooperativa()
    {
        nombre = "";
    }

    void leer_nombre()
    {
        nombre = leer_texto("Ingrese el nombre de la cooperativa: ");
    }

    void leer_buses()
    {
        int cantidad = leer_entero("Ingrese la cantidad de buses (1-100): ", 1, 100);
        buses.clear();
        buses.reserve(cantidad);
        for (int i = 0; i < cantidad; i++)
        {
            Bus bus;
            bool repetido;
            do
            {
                cout << "\nBUS " << i + 1 << endl;
                bus.leer();
                repetido = bus_repetido(bus);
                if (repetido)
                    cout << "La placa o el numero ya estan registrados. Ingrese nuevamente el bus." << endl;
            } while (repetido);
            buses.push_back(bus);
        }
    }

    void leer()
    {
        leer_nombre();
        leer_buses();
    }

    void mostrar() const
    {
        cout << "\nCOOPERATIVA: " << nombre << endl;
        cout << "BUSES CON 20 ASIENTOS O MAS" << endl;
        bool encontrados = false;
        for (const Bus& bus : buses)
        {
            if (bus.getCantidadAsientos() >= 20)
            {
                bus.mostrar();
                encontrados = true;
            }
        }
        if (!encontrados)
            cout << "Ningun bus cumple la condicion." << endl;
    }

    void actualizar_numeros(const string& numeroCooperativa)
    {
        if (numeroCooperativa.empty()
            || numeroCooperativa.find_first_not_of("0123456789") != string::npos)
        {
            cout << "El numero de cooperativa debe contener solamente digitos." << endl;
            return;
        }
        for (Bus& bus : buses)
            bus.actualizar_numero(numeroCooperativa);
        cout << "Numeros actualizados." << endl;
    }

    void mostrar_buses_propietario(const string& nombreBuscado) const
    {
        bool encontrados = false;
        string nombreComparado = convertir_mayusculas(nombreBuscado);
        for (const Bus& bus : buses)
        {
            if (convertir_mayusculas(bus.get_nombre_propietario()) == nombreComparado)
            {
                bus.mostrar();
                encontrados = true;
            }
        }
        if (!encontrados)
            cout << "No se encontraron buses de ese propietario." << endl;
    }

    void mostrar_bus_placa(const string& placaBuscada) const
    {
        string placaComparada = convertir_mayusculas(placaBuscada);
        for (const Bus& bus : buses)
        {
            if (bus.get_placa() == placaComparada)
            {
                bus.mostrar();
                return;
            }
        }
        cout << "No se encontro un bus con esa placa." << endl;
    }
};

int main()
{
    try
    {
        Cooperativa cooperativa;
        cooperativa.leer();
        int opcion;
        do
        {
            cout << "\n1. Mostrar buses con 20 asientos o mas" << endl;
            cout << "2. Actualizar los numeros de todos los buses" << endl;
            cout << "3. Buscar buses por nombre del propietario" << endl;
            cout << "4. Buscar bus por placa" << endl;
            cout << "0. Salir" << endl;
            opcion = leer_entero("Seleccione una opcion: ", 0, 4);
            switch (opcion)
            {
                case 1:
                    cooperativa.mostrar();
                    break;
                case 2:
                    cooperativa.actualizar_numeros(leer_numero("Ingrese el numero de cooperativa: "));
                    break;
                case 3:
                    cooperativa.mostrar_buses_propietario(leer_texto("Ingrese el nombre del propietario: "));
                    break;
                case 4:
                    cooperativa.mostrar_bus_placa(leer_texto("Ingrese la placa: "));
                    break;
                case 0:
                    cout << "Programa finalizado." << endl;
                    break;
            }
        } while (opcion != 0);
    }
    catch (const runtime_error& error)
    {
        cout << "\n" << error.what() << endl;
    }
    return 0;
}
