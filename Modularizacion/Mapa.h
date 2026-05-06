#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <string>

const int coordX[] = { 2, 7, 16, 2, 7, 16, 2, 7 };
const int coordY[] = { 2, 2, 4, 7, 7, 7, 4, 1 };

inline void dibujarDungeon(int sala, int hp, int lvl, std::string n, std::string c, std::string bioma, std::string msg) {
    std::string arte[10] = {
        "######################",
        "#  .  #      #       #",
        "#     #      #   .   #",
        "#     ########       #",
        "#  .           #  .  #",
        "#######   ############",
        "#     #   #          #",
        "#  .  #   #    .     #",
        "######################"
    };

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "==========================================\n";
    std::cout << " Heroe: " << n << " (" << c << ") | LVL: " << lvl << " | HP: " << hp << "\n";
    std::cout << " Bioma: " << bioma << " | Sala: " << sala << "\n";
    std::cout << "==========================================\n";

    for (int i = 0; i < 9; i++) { // Bucle de repetición anidado
        for (int j = 0; j < 22; j++) {
            if (i == coordY[sala] && j == coordX[sala]) std::cout << '@';
            else std::cout << arte[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "==========================================\n";
    std::cout << " LOG: " << msg << "\n";
    std::cout << "==========================================\n";
}

inline void pantallaMuerte() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    // Calavera Demoniaca ASCII Restaurada
    std::cout << "             ,      ,             \n";
    std::cout << "            /(.-\"\"-.)\\            \n";
    std::cout << "        |\\  \\/      \\/  /|        \n";
    std::cout << "        | \\ / =    = \\ / |        \n";
    std::cout << "        \\ ( \\  o  o  / ) /        \n";
    std::cout << "         \\_,|    U   |,_/         \n";
    std::cout << "            | \\====/ |            \n";
    std::cout << "            \\  '--'  /            \n";
    std::cout << "             '------'             \n";
    std::cout << "\n       HAAS SIDO ELIMINADO        \n";
    std::cout << "     Press [R] to Restart / [Q] to Quit \n\n";
}

#endif