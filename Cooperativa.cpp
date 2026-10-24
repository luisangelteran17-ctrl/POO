#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Bus
{
private:
    string nombrePropietario;
    string apellidoPropietario;
    string numeroBus;
    int cantidadAsientos;
    string placa;

public:
    Bus()
    {
        nombrePropietario = "";
        apellidoPropietario = "";
        numeroBus = "";
        cantidadAsientos = 0;
        placa = "";
    }

    void leer_nombre_propietario()
    {
        cout << "Ingrese el nombre del propietario: ";
        cin >> nombrePropietario;
    }

    void leer_apellido_propietario()
    {
        cout << "Ingrese el apellido del propietario: ";
        cin >> apellidoPropietario;
    }

    void leer_numero_bus()
    {
        cout << "Ingrese el numero del bus: ";
        cin >> numeroBus;
    }

    void leer_cantidad_asientos()
    {
        cout << "Ingrese la cantidad de asientos: ";
        cin >> cantidadAsientos;
    }

    void leer_placa()
    {
        cout << "Ingrese la placa: ";
        cin >> placa;
    }

    void leer()
    {
        leer_nombre_propietario();
        leer_apellido_propietario();
        leer_numero_bus();
        leer_cantidad_asientos();
        leer_placa();
    }

    string get_nombre_propietario() const
    {
        return nombrePropietario;
    }

    string get_numero_bus() const
    {
        return numeroBus;
    }

    int getCantidadAsientos() const
    {
        return cantidadAsientos;
    }

    string get_placa() const
    {
        return placa;
    }

    void set_numero_bus(string numero)
    {
        numeroBus = numero;
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
    int cantidadBuses;
    vector<Bus> buses;

public:
    Cooperativa()
    {
        nombre = "";
        cantidadBuses = 0;
    }

    void leer_nombre()
    {
        cout << "Ingrese el nombre de la cooperativa: ";
        cin >> nombre;
    }

    void leer_cantidad_buses()
    {
        do
        {
            cout << "Ingrese la cantidad de buses (1-100): ";
            cin >> cantidadBuses;
        } while (cantidadBuses < 1 || cantidadBuses > 100);
    }

    void leer_buses()
    {
        buses.resize(cantidadBuses);

        for (int i = 0; i < cantidadBuses; i++)
        {
            cout << "\nBUS " << i + 1 << endl;
            buses[i].leer();
        }
    }

    void leer()
    {
        leer_nombre();
        leer_cantidad_buses();
        leer_buses();
        leer_numero_cooperativa();
    }

    void leer_numero_cooperativa()
    {
        string numeroCooperativa;
        cout << "\nIngrese el numero de la cooperativa: ";
        cin >> numeroCooperativa;
        actualizar_numeros(numeroCooperativa);
    }

    void mostrar() const
    {
        cout << "\nCOOPERATIVA: " << nombre << endl;
        cout << "BUSES CON 20 ASIENTOS O MAS" << endl;

        for (int i = 0; i < cantidadBuses; i++)
        {
            if (buses[i].getCantidadAsientos() >= 20)
                buses[i].mostrar();
        }

        consultar_buses_propietario();
        consultar_bus_placa();
    }

    void consultar_buses_propietario() const
    {
        string nombrePropietario;
        cout << "\nIngrese el nombre del propietario a buscar: ";
        cin >> nombrePropietario;
        mostrar_buses_propietario(nombrePropietario);
    }

    void consultar_bus_placa() const
    {
        string placa;
        cout << "\nIngrese la placa del bus a buscar: ";
        cin >> placa;
        mostrar_bus_placa(placa);
    }

    void actualizar_numeros(string numeroCooperativa)
    {
        for (int i = 0; i < cantidadBuses; i++)
        {
            buses[i].set_numero_bus(numeroCooperativa + buses[i].get_numero_bus());
        }
    }

    void mostrar_buses_propietario(string nombreBuscado) const
    {
        for (int i = 0; i < cantidadBuses; i++)
        {
            if (buses[i].get_nombre_propietario() == nombreBuscado)
                buses[i].mostrar();
        }
    }

    void mostrar_bus_placa(string placaBuscada) const
    {
        for (int i = 0; i < cantidadBuses; i++)
        {
            if (buses[i].get_placa() == placaBuscada)
                buses[i].mostrar();
        }
    }
};

int main()
{
    Cooperativa cooperativa;
    cooperativa.leer();
    cooperativa.mostrar();
    return 0;
}
