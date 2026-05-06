#include <iostream>
#include <ctime>
#include <string>
#include "Entidades.h"
#include "Mapa.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    char control;

    do {
        string nombre;
        int opcion;
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "--- CREACION DE PERSONAJE ---\nNombre: ";
        cin.ignore(); getline(cin, nombre);

        cout << "\nCLASES DISPONIBLES:\n";
        cout << "1. GUERRERO: 150 HP | El tanque definitivo.\n";
        cout << "2. MAGO: 80 HP | Fragil pero con dano critico.\n";
        cout << "3. PICARO: 110 HP | Equilibrio y agilidad.\n> ";
        cin >> opcion;

        Heroe* jugador;
        if (opcion == 1) jugador = new Heroe(nombre, "Guerrero", 150, 18, 2);
        else if (opcion == 2) jugador = new Heroe(nombre, "Mago", 80, 40, 4);
        else jugador = new Heroe(nombre, "Picaro", 110, 28, 3);

        string biomas[] = { "PANTANO", "CRIPTAS" };
        string log = "Te adentras en la oscuridad...";
        int salaGlobal = 0;
        bool retirado = false;

        for (int b = 0; b < 2; b++) { // Navegacion por biomas
            for (int s = 0; s < 5; s++) { // 5 salas por bioma para mas experiencia
                if (!jugador->vivo() || retirado) break;

                while (true) {
                    dibujarDungeon(salaGlobal, jugador->getHP(), jugador->getNivel(), jugador->nombre, jugador->getClase(), biomas[b], log);
                    cout << "1. Avanzar  2. Descansar  3. Curar (" << jugador->getPociones() << ")  4. Salir\n> ";
                    int op; cin >> op;

                    if (op == 1) {
                        bool esBoss = (s == 4); // Jefe al final de cada bioma
                        if (rand() % 100 < 70 || esBoss) { // Mayor probabilidad de encuentro para ganar EXP
                            Entidad* m = spawnEnemigo(b, esBoss);
                            log = "¡" + m->nombre + " te ataca!";

                            while (m->vivo() && jugador->vivo()) { // Combate
                                dibujarDungeon(salaGlobal, jugador->getHP(), jugador->getNivel(), jugador->nombre, jugador->getClase(), biomas[b], log);
                                cout << "--- COMBATE --- 1. Atacar  2. Curar  3. Huir\n> ";
                                int c; cin >> c;
                                if (c == 1) {
                                    int d = jugador->getAtk(); m->recibirDano(d);
                                    log = "Golpeas por " + to_string(d) + " de dano.";
                                }
                                else if (c == 2) jugador->curar();
                                else if (c == 3 && !esBoss && rand() % 100 < 50) { delete m; m = nullptr; break; }

                                if (m && m->vivo()) {
                                    int dM = m->getAtk(); jugador->recibirDano(dM);
                                    log += " | Enemigo quita " + to_string(dM) + " HP.";
                                }
                            }
                            if (jugador->vivo() && m && !m->vivo()) {
                                log = "Victoria sobre " + m->nombre;
                                jugador->ganarExp(esBoss ? 120 : 45); // EXP aumentada
                                delete m;
                            }
                        }
                        else log = "Caminas sin incidentes...";

                        salaGlobal++; break;
                    }
                    else if (op == 2) { jugador->descansar(); log = "Recuperas fuerzas."; }
                    else if (op == 4) { retirado = true; break; }
                }
            }
        }

        if (!jugador->vivo()) {
            pantallaMuerte();
            cin >> control;
        }
        else if (retirado) {
            cout << "\nHas escapado con vida.\n"; control = 'q';
        }
        else {
            cout << "\n¡HAS CONQUISTADO LA MAZMORRA!\n"; control = 'q';
        }
        delete jugador;

    } while (tolower(control) == 'r'); // Estatuto de Repeticion

    return 0;
}