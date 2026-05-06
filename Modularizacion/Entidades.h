#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>
#include <iostream>

class Entidad {
protected:
    int hp, atk; // Escalares de estado
public:
    std::string nombre;
    Entidad(std::string n, int h, int a) : nombre(n), hp(h), atk(a) {}
    bool vivo() { return hp > 0; }
    void recibirDano(int d) { hp -= d; if (hp < 0) hp = 0; }
    int getAtk() { return (rand() % atk) + 5; }
    int getHP() { return hp; }
};

class Heroe : public Entidad {
private:
    int nivel, exp, expSiguiente, pociones; // Escalares de progresión
    std::string clase;
public:
    Heroe(std::string n, std::string c, int h, int a, int p)
        : Entidad(n, h, a), clase(c), nivel(1), exp(0), expSiguiente(100), pociones(p) {
    }

    void ganarExp(int e) {
        exp += e;
        if (exp >= expSiguiente) { // Estatuto de Decisión: Level Up
            nivel++;
            exp = 0;
            expSiguiente += 100;
            hp += 40;
            atk += 10;
            std::cout << "\n>>> ¡LEVEL UP! Has alcanzado el Nivel " << nivel << " <<<\n";
        }
    }
    void descansar() { hp += 30; }
    void curar() { if (pociones > 0) { hp += 55; pociones--; } }
    int getNivel() { return nivel; }
    int getPociones() { return pociones; }
    std::string getClase() { return clase; }
};

inline Entidad* spawnEnemigo(bool esBoss) {
    if (esBoss) return new Entidad("Jefe Final: Dragon de Ceniciza", 180, 28);
    int r = rand() % 100; // Probabilidades de aparición
    if (r < 40) return new Entidad("Rata Imunda", 25, 6);
    if (r < 75) return new Entidad("Slime de Acido", 35, 12);
    return new Entidad("Guerrero Esqueleto", 55, 18);
}

#endif