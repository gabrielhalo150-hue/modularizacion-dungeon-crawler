<?php
function limpiarPantalla() {
    echo (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') ? popen('cls', 'w') : str_repeat("\n", 50);
    // En Linux/Terminal real, 'clear' es mejor, pero esto es universal para PHP.
    passthru(strtoupper(substr(PHP_OS, 0, 3)) === 'WIN' ? 'cls' : 'clear');
}

function dibujarDungeon($sala, $hp, $lvl, $n, $c, $bioma, $msg) {
    $coordX = [2, 7, 16, 2, 7, 16, 2, 7];
    $coordY = [2, 2, 4, 7, 7, 7, 4, 1];
    
    $arte = [
        "######################",
        "#  .  #      #       #",
        "#     #      #   .   #",
        "#     ########       #",
        "#  .           #  .  #",
        "#######   ############",
        "#     #   #          #",
        "#  .  #   #    .     #",
        "######################"
    ];

    limpiarPantalla();
    echo "==========================================\n";
    echo " $n ($c) | LVL: $lvl | HP: $hp\n";
    echo " BIOMA: $bioma | SALA: " . ($sala + 1) . "\n";
    echo "==========================================\n";

    foreach ($arte as $i => $fila) {
        for ($j = 0; $j < strlen($fila); $j++) {
            if ($i == $coordY[$sala % 8] && $j == $coordX[$sala % 8]) echo "@";
            else echo $fila[$j];
        }
        echo "\n";
    }
    echo "==========================================\n";
    echo " LOG: $msg\n";
    echo "==========================================\n";
}

function pantallaMuerte() {
    limpiarPantalla();
    echo "             ,      ,             \n";
    echo "            /(.-\"\"-.)\\            \n";
    echo "        |\\  \\/      \\/  /|        \n";
    echo "        | \\ / =    = \\ / |        \n";
    echo "        \\ ( \\  o  o  / ) /        \n";
    echo "         \\_,|    U   |,_/         \n";
    echo "            | \\====/ |            \n";
    echo "            \\  '--'  /            \n";
    echo "             '------'             \n";
    echo "\n       HAS SIDO ELIMINADO        \n";
    echo "   [R] REINTENTAR  |  [Q] SALIR   \n\n";
}