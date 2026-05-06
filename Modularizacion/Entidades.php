<?php
// TDA: Clase base para cualquier entidad en la mazmorra
class Entidad {
    public $nombre;
    protected $hp;
    protected $atk;

    public function __construct($n, $h, $a) {
        $this->nombre = $n;
        $this->hp = $h;
        $this->atk = $a;
    }

    public function vivo() { return $this->hp > 0; }
    
    public function recibirDano($d) {
        $this->hp -= $d;
        if ($this->hp < 0) $this->hp = 0;
    }

    public function getAtk() { return rand(5, $this->atk); }
    public function getHP() { return $this->hp; }
}

class Heroe extends Entidad {
    private $nivel = 1;
    private $exp = 0;
    private $expSiguiente = 80;
    public $pociones;
    public $clase;

    public function __construct($n, $c, $h, $a, $p) {
        parent::__construct($n, $h, $a);
        $this->clase = $c;
        $this->pociones = $p;
    }

    public function ganarExp($e) {
        $this->exp += $e;
        if ($this->exp >= $this->expSiguiente) {
            $this->nivel++;
            $this->exp = 0;
            $this->expSiguiente += 100;
            $this->hp += 50; // Escalado de vida
            $this->atk += 12; // Escalado de daño
            echo "\n>>> ¡LEVEL UP! Eres Nivel {$this->nivel}. HP y ATK aumentados! <<<\n";
            readline("Presiona Enter para continuar...");
        }
    }

    public function descansar() { $this->hp += 35; }
    public function curar() { 
        if ($this->pociones > 0) { 
            $this->hp += 60; 
            $this->pociones--; 
            return true;
        }
        return false;
    }
    public function getNivel() { return $this->nivel; }
}

function spawnEnemigo($bioma, $esBoss) {
    if ($esBoss) {
        return ($bioma == 0) 
            ? new Entidad("JEFE: Guardian del Pantano", 100, 15) 
            : new Entidad("FINAL BOSS: DRAGON ANCESTRAL", 200, 30);
    }
    $r = rand(0, 99);
    if ($r < 45) return new Entidad("Rata Inmunda", 20, 5);
    if ($r < 80) return new Entidad("Slime de Acido", 35, 10);
    return new Entidad("Esqueleto Guerrero", 55, 18);
}