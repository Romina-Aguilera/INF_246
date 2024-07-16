import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Laberinto {
    public static int[][] maze;
    public static int[] start;
    public static int[] end;

    public static void cargarLaberinto(String filename) throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            //Obtener dimensión de la matriz
            String sizeLine = br.readLine().trim();
            String[] dimensions = sizeLine.split("x");
            int n = Integer.parseInt(dimensions[0]);
            maze = new int[n][n];

            //Obtener coordenada de inicio
            String[] startCoords = br.readLine().trim().replaceAll("[\\[\\]]", "").split(",");
            start = new int[]{Integer.parseInt(startCoords[0].trim()), Integer.parseInt(startCoords[1].trim())};

            for (int i = 0; i < n; i++) {
                //Guardar laberinto (quitando los espacios)
                String line = br.readLine().trim().replaceAll(" ", "");
                for (int j = 0; j < n; j++) {
                    char ch = line.charAt(j);
                    if (ch == 'E') {
                        //Entrada al laberinto
                        start = new int[]{i, j};
                        maze[i][j] = 0;
                    } else if (ch == 'S') {
                        //Salida del laberinto
                        end = new int[]{i, j};
                        maze[i][j] = 0;
                    } else {
                        maze[i][j] = ch - '0';
                    }
                }
            }
        }
    }
}
