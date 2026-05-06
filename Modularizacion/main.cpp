#include <iostream>
#include <ctime>
#include <string>
#include "Entidades.h"
#include "Mapa.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    char control;

    do { // Bucle de repetición global para reintentar el juego
        string nombre;
        int opcion;

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "--- CREACION DE PERSONAJE ---\n";
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nombre);

        cout << "\nELIJA SU CLASE (Analice las descripciones):\n";
        cout << "1. GUERRERO: El baluarte de acero. Alta salud (150 HP) y defensa solida.\n";
        cout << "2. MAGO: El canon de cristal. Baja salud (80 HP) pero un poder arcano devastador.\n";
        cout << "3. PICARO: El maestro del equilibrio. Salud media (110 HP) y gran agilidad.\n> ";
        cin >> opcion;

        Heroe* jugador;
        if (opcion == 1) jugador = new Heroe(nombre, "Guerrero", 150, 15, 2);
        else if (opcion == 2) jugador = new Heroe(nombre, "Mago", 80, 35, 4);
        else jugador = new Heroe(nombre, "Picaro", 110, 25, 3);

        string biomas[] = { "PANTANO", "CRIPTAS" };
        string log = "Te adentras en la mazmorra...";
        int salaGlobal = 0;
        bool retirado = false;

        for (int b = 0; b < 2; b++) { // Navegacion por biomas
            for (int s = 0; s < 4; s++) { // Salas por bioma
                if (!jugador->vivo() || retirado) break;

                while (true) {
                    dibujarDungeon(salaGlobal, jugador->getHP(), jugador->getNivel(), jugador->nombre, jugador->getClase(), biomas[b], log);
                    cout << "1. Avanzar  2. Descansar  3. Curar (" << jugador->getPociones() << ")  4. Salir\n> ";
                    int op; cin >> op;

                    if (op == 1) {
                        bool esBoss = (s == 3);
                        if (rand() % 100 < 65 || esBoss) {
                            Entidad* m = spawnEnemigo(esBoss);
                            log = "¡" + m->nombre + " te intercepta!";
                            while (m->vivo() && jugador->vivo()) {
                                dibujarDungeon(salaGlobal, jugador->getHP(), jugador->getNivel(), jugador->nombre, jugador->getClase(), biomas[b], log);
                                cout << "--- COMBATE --- 1. Atacar  2. Curar  3. Huir\n> ";
                                int c; cin >> c;
                                if (c == 1) {
                                    int d = jugador->getAtk(); m->recibirDano(d);
                                    log = "Causas " + to_string(d) + " de dano al enemigo.";
                                }
                                else if (c == 2) jugador->curar();
                                else if (c == 3 && rand() % 100 < 50) { delete m; m = nullptr; break; }

                                if (m && m->vivo()) {
                                    int dM = m->getAtk(); jugador->recibirDano(dM);
                                    log += " | Te hieren (-" + to_string(dM) + " HP).";
                                }
                            }
                            if (jugador->vivo() && m && !m->vivo()) {
                                jugador->ganarExp(esBoss ? 150 : 40);
                                delete m;
                            }
                        }
                        if (!jugador->vivo()) break;
                        salaGlobal++; break;
                    }
                    else if (op == 2) jugador->descansar();
                    else if (op == 4) { retirado = true; break; }
                }
            }
        }

        if (!jugador->vivo()) {
            pantallaMuerte();
            cin >> control;
        }
        else if (retirado) {
            cout << "\nHas escapado con vida de la mazmorra.\n";
            control = 'q';
        }
        else {
            cout << "\n¡HAS COMPLETADO LA MAZMORRA CON EXITO!\n";
            control = 'q';
        }

        delete jugador; // Liberacion de memoria para el TDA

    } while (tolower(control) == 'r'); // Repeticion si el usuario presiona R

    return 0;
}