#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>
#include <iostream>

class Entidad {
protected:
    int hp, atk; // Escalares protegidos
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
        : Entidad(n, h, a), clase(c), nivel(1), exp(0), expSiguiente(80), pociones(p) {
    }

    void ganarExp(int e) {
        exp += e;
        if (exp >= expSiguiente) { // Estatuto de Decisión: Level Up
            nivel++;
            exp = 0;
            expSiguiente += 100;
            hp += 50; // Aumento significativo de HP
            atk += 12; // Aumento significativo de Daño
            std::cout << "\n>>> ¡LEVEL UP! Ahora eres Nivel " << nivel << ". HP y ATK aumentados! <<<\n";
        }
    }
    void descansar() { hp += 35; }
    void curar() { if (pociones > 0) { hp += 60; pociones--; } }
    int getNivel() { return nivel; }
    int getPociones() { return pociones; }
    std::string getClase() { return clase; }
};

inline Entidad* spawnEnemigo(int bioma, bool esBoss) {
    if (esBoss) {
        if (bioma == 0) return new Entidad("JEFE: Guardian del Pantano", 100, 15);
        else return new Entidad("FINAL BOSS: DRAGON ANCESTRAL", 200, 30);
    }
    int r = rand() % 100;
    if (r < 45) return new Entidad("Rata Imunda", 20, 5); // 45% Probabilidad
    if (r < 80) return new Entidad("Slime de Acido", 35, 10); // 35% Probabilidad
    return new Entidad("Esqueleto Guerrero", 55, 18); // 20% Probabilidad
}

#endif