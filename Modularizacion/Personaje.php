class Personaje {
    public $nombre;
    private $oro; // No3: Atributo privado

    public function __construct($n, $o) {
        $this->nombre = $n;
        $this->oro = $o;
    }

    public function mostrarInfo() {
        echo "Heroe: {$this->nombre} | Oro en bolsa: {$this->oro}\n";
    }
}