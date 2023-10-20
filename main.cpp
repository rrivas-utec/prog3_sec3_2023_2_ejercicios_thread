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
public:
    Cliente() = default;
    Cliente(double saldo): saldo(saldo) {}
    void deposito(double importe) { saldo += importe; }
    void retiro(double importe) { saldo -= importe; }
    friend ostream& operator << (ostream& out, const Cliente& c) {
        out << c.saldo;
        return out;
    }
};

void ejercicio_3() {
    int nd = 100;
    int d = 1;
    int nr = 100;
    int r = 1;
    Cliente c;
    // hilos de deposito

    // hilos de retiro

    // union de depositos
    // union de retiros

    cout << c;
}

int main() {
    ejercicio_2();
    return 0;
}
