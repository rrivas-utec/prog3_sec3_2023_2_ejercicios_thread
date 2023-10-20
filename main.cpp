#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

mutex mtx;

void incrementar(int& result, int inc) {
    this_thread::sleep_for(chrono::milliseconds(30));
//    lock_guard lg(mtx);
    unique_lock ul(mtx);
//    mtx.lock();
    result += inc;
//    mtx.unlock();
    ul.unlock();
    // .... instrucciones adicionales
}

void ejercicio_1(int n, int inc, int& total) {
//    int n = 100;
//    int inc = 1;
//    int total = 0;
    vector<jthread> vt(n); // Creando n hilos
    // loop de asignacion de funcion a hilos
    for (auto& t: vt) t = jthread(incrementar, ref(total), inc);
    // loop de joins
    for (auto& t: vt) t.join();
//    // mostrar el resultado
//    cout << total << endl;
}

void ejercicio_2() {
    int n = 100;
    int m = 400;
    int inc = 1;
    vector<int> totales(m);
    for (int i = 0; i < m; ++i)
        ejercicio_1(n, inc, totales[i]);

    for (const auto& item: totales) cout << item << " ";
}

class Cliente {
    double saldo = 0;
    mutex mtx;
public:
    Cliente() = default;
    Cliente(double saldo): saldo(saldo) {}
    void deposito(double importe) {
        lock_guard lg(mtx);
        saldo += importe;
    }
    void retiro(double importe) {
        unique_lock ul(mtx);
        saldo -= importe;
    }
    friend ostream& operator << (ostream& out, const Cliente& c) {
        out << c.saldo;
        return out;
    }
};

void ejercicio_3() {
    int nd = 100;
    int d = 1;
    int nr = 50;
    int r = 1;
    Cliente c;
    // hilos de deposito
    vector<jthread> vtd(nd); // Crear hilos de deposito
    // asignar el metodo de deposito al hilo
    for (auto& t: vtd) t = jthread(&Cliente::deposito, &c, d);

    // hilos de retiro
    vector<jthread> vtr(nr);
    for (auto& t: vtr) t = jthread(&Cliente::retiro, &c, r);

    // union de depositos
    for (auto& t: vtd) t.join();
    // union de retiros
    for (auto& t: vtr) t.join();

    cout << c;
}

int main() {
//    ejercicio_2();
    ejercicio_3();
    return 0;
}
