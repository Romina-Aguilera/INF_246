import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;
import java.io.IOException;

// Clase MazeSolver que extiende RecursiveTask para resolver el laberinto de manera recursiva
public class MazeSolver extends RecursiveTask<Boolean> {
    private int x, y, processNumber; // Variables para representar la posición en el laberinto y el número de proceso

    // Constructor de la clase MazeSolver
    public MazeSolver(int x, int y, int processNumber) {
        this.x = x;
        this.y = y;
        this.processNumber = processNumber;
    }

    // Método compute() que realiza la tarea de resolver el laberinto
    @Override
    protected Boolean compute() {
        // Verifica si la posición actual está fuera del laberinto o es una pared
        if (x < 0 || x >= Laberinto.maze.length || y < 0 || y >= Laberinto.maze[0].length || Laberinto.maze[x][y] == 1) {
            return false; // Retorna falso si es así, indicando que no se puede continuar desde esta posición
        }

        // Verifica si se ha llegado a la posición de salida
        if (x == Laberinto.end[0] && y == Laberinto.end[1]) {
            // Imprime que este proceso ha llegado a la salida
            System.out.println("P" + processNumber + "- [" + x + "," + y + "]- Salida");
            return true; // Retorna verdadero, indicando que se ha encontrado la salida
        }

        Laberinto.maze[x][y] = 1; // Marca la posición actual como visitada
        // Imprime la posición actual y el número de proceso
        System.out.println("P" + processNumber + "- [" + x + "," + y + "]");

        // Crea cuatro subprocesos (instancias de MazeSolver) para explorar las cuatro direcciones posibles
        MazeSolver right = new MazeSolver(x, y + 1, processNumber + 1);
        MazeSolver down = new MazeSolver(x + 1, y, processNumber + 1);
        MazeSolver left = new MazeSolver(x, y - 1, processNumber + 1);
        MazeSolver up = new MazeSolver(x - 1, y, processNumber + 1);

        // Divide y ejecuta los subprocesos utilizando la operación fork()
        right.fork();
        down.fork();
        left.fork();
        up.fork();

        // Espera a que los subprocesos terminen y realiza una operación OR en sus resultados
        if (right.join() || down.join() || left.join() || up.join()) {
            return true; // Retorna verdadero si alguno de los subprocesos ha encontrado la salida
        }

        Laberinto.maze[x][y] = 0; // Desmarca la posición actual
        return false; // Retorna falso indicando que no se encontró la salida desde esta posición
    }

    // Método main para iniciar el programa
    public static void main(String[] args) {
        try {
            // Se carga el laberinto desde un archivo
            Laberinto.cargarLaberinto("laberinto.txt");
            // Se crea un pool de hilos ForkJoinPool
            ForkJoinPool pool = new ForkJoinPool();
            // Se crea un objeto MazeSolver con las coordenadas de inicio y se invoca su ejecución en el pool
            long inicial = System.currentTimeMillis();
            MazeSolver solver = new MazeSolver(Laberinto.start[0], Laberinto.start[1], 1);
            boolean result = pool.invoke(solver); // El resultado indica si se encontró la salida o no
            long fin = System.currentTimeMillis();
            long tiempo_ejec = fin - inicial;
            System.out.println("El tiempo de ejecución usando Forks es de" + tiempo_ejec + "ms");
            if (!result) {
                System.out.println("No se encontró salida."); // Mensaje si no se encontró la salida
            }
        } catch (IOException e) {
            e.printStackTrace(); // Manejo de excepciones en caso de error de entrada/salida
        }
    }
}
