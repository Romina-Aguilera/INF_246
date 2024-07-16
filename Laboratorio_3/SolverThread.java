import java.io.IOException;

// Se define la clase SolverThread que extiende de Thread para representar un hebra de ejecución
public class SolverThread extends Thread {
    private int x, y, processNumber; // Se declaran variables para representar la posición en el laberinto y el número de proceso

    // Constructor de la clase SolverThread
    public SolverThread(int x, int y, int processNumber) {
        this.x = x;
        this.y = y;
        this.processNumber = processNumber;
    }

    // Método run, que será ejecutado por la hebra
    @Override
    public void run() {
        resolver(x, y, processNumber); // Llama al método resolver con las coordenadas iniciales y el número de proceso
    }

    // Método privado resolver para encontrar la salida del laberinto
    private boolean resolver(int x, int y, int processNumber) {
        // Verifica si la posición actual está fuera del laberinto o es una pared
        if (x < 0 || x >= Laberinto.maze.length || y < 0 || y >= Laberinto.maze[0].length || Laberinto.maze[x][y] == 1) {
            return false; // Retorna falso si es así, indicando que no se puede continuar desde esta posición
        }
        System.out.println(Laberinto.end); // Imprime la posición final del laberinto
        // Verifica si se ha llegado a la posición de salida
        if (x == Laberinto.end[0] && y == Laberinto.end[1]) {
            // Imprime que este proceso ha llegado a la salida
            System.out.println("P" + processNumber + "- [" + x + "," + y + "]- Salida");
            return true; // Retorna verdadero, indicando que se ha encontrado la salida
        }

        Laberinto.maze[x][y] = 1; // Marca la posición actual como visitada
        // Imprime la posición actual y el número de proceso
        System.out.println("P" + processNumber + "- [" + x + "," + y + "]");

        // Crea cuatro subprocesos (hilos) para explorar las cuatro direcciones posibles
        SolverThread right = new SolverThread(x, y + 1, processNumber + 1);
        SolverThread down = new SolverThread(x + 1, y, processNumber + 1);
        SolverThread left = new SolverThread(x, y - 1, processNumber + 1);
        SolverThread up = new SolverThread(x - 1, y, processNumber + 1);

        // Inicia los subprocesos
        right.start();
        down.start();
        left.start();
        up.start();

        try {
            // Espera a que todos los subprocesos terminen
            right.join();
            down.join();
            left.join();
            up.join();
        } catch (InterruptedException e) {
            e.printStackTrace(); // Manejo de excepciones en caso de interrupción
        }

        // Si alguno de los subprocesos está vivo (aún no ha terminado), retorna verdadero
        if (right.isAlive() || down.isAlive() || left.isAlive() || up.isAlive()) {
            return true;
        }

        Laberinto.maze[x][y] = 0; // Desmarca la posición actual
        return false; // Retorna falso indicando que no se encontró la salida desde esta posición
    }

    // Método main para iniciar el programa
    public static void main(String[] args) {
        try {
            // Se carga el laberinto desde un archivo
            Laberinto.cargarLaberinto("laberinto.txt");
            // Se crea un objeto SolverThread con las coordenadas de inicio y se inicia su ejecución
            SolverThread solver = new SolverThread(Laberinto.start[0], Laberinto.start[1], 1);
            long inicio = System.currentTimeMillis();
            solver.start();
            solver.join(); // Espera a que el hilo principal termine
            long termino = System.currentTimeMillis();
            long tiempo_ejecucion = termino - inicio;
            System.out.println("El tiempo de ejecución usando Hebras es de" + tiempo_ejecucion + "ms");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace(); // Manejo de excepciones en caso de error de entrada/salida o interrupción
        }
    }
}
