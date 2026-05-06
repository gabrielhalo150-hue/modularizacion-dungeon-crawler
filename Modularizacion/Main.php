<?php
require_once 'Entidades.php';
require_once 'Visuales.php';

do {
    limpiarPantalla();
    echo "--- REGISTRO DE AVENTURERO ---\n";
    $nombre = readline("Nombre: ");

    echo "\nCLASES DISPONIBLES:\n";
    echo "1. GUERRERO: 150 HP | El tanque definitivo.\n";
    echo "2. MAGO: 80 HP | Fragil pero con dano critico.\n";
    echo "3. PICARO: 110 HP | Equilibrio y agilidad.\n> ";
    $opcion = readline();

    if ($opcion == 1) $jugador = new Heroe($nombre, "Guerrero", 150, 18, 2);
    elseif ($opcion == 2) $jugador = new Heroe($nombre, "Mago", 80, 40, 4);
    else $jugador = new Heroe($nombre, "Picaro", 110, 28, 3);

    $biomas = ["PANTANO", "CRIPTAS"];
    $log = "Te adentras en la oscuridad...";
    $salaGlobal = 0;
    $retirado = false;

    for ($b = 0; $b < 2; $b++) {
        for ($s = 0; $s < 5; $s++) { // 5 salas por bioma para asegurar el farmeo
            if (!$jugador->vivo() || $retirado) break;

            while (true) {
                dibujarDungeon($salaGlobal, $jugador->getHP(), $jugador->getNivel(), $jugador->nombre, $jugador->clase, $biomas[$b], $log);
                echo "1. Avanzar  2. Descansar  3. Curar ({$jugador->pociones})  4. Salir\n> ";
                $op = readline();

                if ($op == "1") {
                    $esBoss = ($s == 4);
                    if (rand(0, 99) < 70 || $esBoss) {
                        $m = spawnEnemigo($b, $esBoss);
                        $log = "¡{$m->nombre} te ataca!";
                        
                        while ($m->vivo() && $jugador->vivo()) {
                            dibujarDungeon($salaGlobal, $jugador->getHP(), $jugador->getNivel(), $jugador->nombre, $jugador->clase, $biomas[$b], $log);
                            echo "--- COMBATE --- 1. Atacar  2. Curar  3. Huir\n> ";
                            $c = readline();
                            
                            if ($c == "1") {
                                $d = $jugador->getAtk(); $m->recibirDano($d);
                                $log = "Golpeas por $d de dano.";
                            } elseif ($c == "2") {
                                if (!$jugador->curar()) $log = "¡No te quedan pociones!";
                            } elseif ($c == "3" && !$esBoss && rand(0, 99) < 50) {
                                $log = "¡Lograste huir!"; $m = null; break;
                            }

                            if ($m && $m->vivo()) {
                                $dM = $m->getAtk(); $jugador->recibirDano($dM);
                                $log .= " | Enemigo quita $dM HP.";
                            }
                        }
                        if ($jugador->vivo() && $m && !$m->vivo()) {
                            $log = "Victoria sobre {$m->nombre}";
                            $jugador->ganarExp($esBoss ? 120 : 45);
                        }
                    } else $log = "Caminas sin incidentes...";
                    
                    $salaGlobal++; break;
                } elseif ($op == "2") { $jugador->descansar(); $log = "Recuperas fuerzas."; }
                elseif ($op == "4") { $retirado = true; break; }
            }
        }
    }

    if (!$jugador->vivo()) {
        pantallaMuerte();
        $control = readline();
    } elseif ($retirado) {
        echo "\nHas escapado con vida.\n"; $control = 'q';
    } else {
        echo "\n¡HAS CONQUISTADO LA MAZMORRA!\n"; $control = 'q';
    }

} while (strtolower($control) == 'r');