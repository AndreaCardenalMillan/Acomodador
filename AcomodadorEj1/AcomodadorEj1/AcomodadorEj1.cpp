#include <iostream>
#include <vector>
#include <ctime>  
#include <cstdlib> 

using namespace std;

// ----- CLASE BUTACA -----

class Butaca {
public:
    Butaca(int fila, int asiento) : fila(fila), asiento(asiento), ocupada(false) {
        //Constructor de butaca
    }

    int getFila() const {
        return fila;
    }

    int getAsiento() const {
        return asiento;
    }

    bool estaOcupada() const {
        return ocupada;
    }

    void ocupar() {
        ocupada = true;
    }

    void desocupar() {
        ocupada = false;
    }

private:
    int fila;
    int asiento;
    bool ocupada;
};

// ----- CLASE CINE TEATRO -----

class CineTeatro {
public:

    //constructor de Cine Teatro
    CineTeatro(int filas, int asientosPorFila) : filas(filas), asientosPorFila(asientosPorFila) {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < asientosPorFila; j++) {
                butacas.push_back(Butaca(i + 1, j + 1));
            }
        }

        inicializarButacasOcupadasRandom();
    }


    void mostrarButacasDisponibles() const {

        for (int fila = 1; fila <= filas; fila++) {
            for (int asiento = 1; asiento <= asientosPorFila; asiento++) {
                bool ocupada = false;

                for (const Butaca& butaca : butacas) {
                    if (butaca.getFila() == fila && butaca.getAsiento() == asiento && butaca.estaOcupada()) {
                        ocupada = true;
                        break;
                    }
                }

                if (ocupada) {
                    cout << "X "; // Butaca ocupada
                }
                else {
                    cout << ". "; // Butaca disponible
                }
            }
            cout << endl; 
        }
    }


    bool venderEntradas(int cantidad) {
        vector<Butaca*> mejoresButacas = encontrarMejoresButacas(cantidad);

        if (mejoresButacas.size() < cantidad) {
            return false; // No hay butacas disponibles
        }

        for (Butaca* butaca : mejoresButacas) {
            butaca->ocupar();
        }

        return true;
    }

    Butaca& getButaca(int fila, int asiento) {
        
        if (fila >= 1 && fila <= filas && asiento >= 1 && asiento <= asientosPorFila) {
            return butacas[(fila - 1) * asientosPorFila + (asiento - 1)];
        }
        else {
            throw out_of_range("Fila o asiento fuera de rango.");
        }
    }

    int getFilas() const {
        return filas;
    }

    int getAsientosPorFila() const {
        return asientosPorFila;
    }

private:
    int filas;
    int asientosPorFila;
    vector<Butaca> butacas;

    void inicializarButacasOcupadasRandom() {
        
        srand(static_cast<unsigned int>(time(nullptr)));

        int totalButacas = filas * asientosPorFila;
        int butacasOcupadas = rand() % totalButacas;

        for (int i = 0; i < butacasOcupadas; i++) {
            int filaAleatoria = rand() % filas + 1;
            int asientoAleatorio = rand() % asientosPorFila + 1;

            Butaca& butaca = getButaca(filaAleatoria, asientoAleatorio);
            if (!butaca.estaOcupada()) {
                butaca.ocupar();
            }
            
        }
    }

    vector<Butaca*> encontrarMejoresButacas(int cantidad) {
        vector<Butaca*> mejoresButacas;

        for (int fila = 1; fila <= filas; fila++) {
            for (int i = 0; i < asientosPorFila - cantidad + 1; i++) {
                std::vector<Butaca*> candidatas;
                for (int j = i; j < i + cantidad; j++) {
                    Butaca& butaca = butacas[(fila - 1) * asientosPorFila + j];
                    if (!butaca.estaOcupada()) {
                        candidatas.push_back(&butaca);
                    }
                    else {
                        break;
                    }
                }

                if (candidatas.size() == cantidad) {
                    if (mejoresButacas.empty() || esMejor(candidatas, mejoresButacas)) {
                        mejoresButacas = candidatas;
                    }
                }
            }
        }

        return mejoresButacas;
    }

    // Se consideran mejores si están más cerca de la pantalla
    bool esMejor(const vector<Butaca*>& candidatas, const vector<Butaca*>& mejores) {
        int filaCandidatas = candidatas.front()->getFila();
        int filaMejores = mejores.front()->getFila();

        return filaCandidatas < filaMejores;
    }
};

// ----- ASIGNAR DIRECTAMENTE LA MEJOR BUTACA -----
 
int main() {
    CineTeatro cine(9, 10);

    while (true) {
        cine.mostrarButacasDisponibles();
        
        int cantidadEntradas;
        cout << "Cuantas entradas desea comprar? ";
        cin >> cantidadEntradas;
        cout << endl;

        if (cine.venderEntradas(cantidadEntradas)) {
            cout << "Entrada vendida con exito" << endl;
        }
        else {
            cout << "No hay suficientes butacas disponibles" << endl;
        }
        cout << endl;
        cine.mostrarButacasDisponibles();
        
        char respuesta;
        cout << "Desea comprar mas entradas? (S/N): ";
        cin >> respuesta;
        
        if (respuesta == 'N' || respuesta == 'n') {
            break;
        }
    }

    return 0;
}



// ----- PREGUNTAR BUTACA -----
//
//int main() {
//    CineTeatro cine(9, 10);
//
//    while (true) {
//        cine.mostrarButacasDisponibles();
//
//        int fila, asiento;
//        cout << "Que asiento desea comprar? (Fila Asiento): ";
//        cin >> fila >> asiento;
//
//        if (fila < 1 || fila > cine.getFilas() || asiento < 1 || asiento > cine.getAsientosPorFila()) {
//            cout << "Fila o asiento invalido. Intente nuevamente." << endl;
//            continue;
//        }
//
//        Butaca& butaca = cine.getButaca(fila, asiento);
//
//        if (butaca.estaOcupada()) {
//            cout << "La butaca ya esta ocupada. Intente nuevamente." << endl;
//        }
//        else {
//            butaca.ocupar();
//            cout << "Entrada vendida en la fila "<< fila << ", asiento " << asiento << endl;
//        }
//
//        cout << endl;
//        cine.mostrarButacasDisponibles();
//
//        char respuesta;
//        cout << "Desea comprar mas entradas? (S/N): ";
//        cin >> respuesta;
//
//        if (respuesta == 'N' || respuesta == 'n') {
//            break;
//        }
//    }
//
//    return 0;
//}