import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Server {
    public static void main(String[] args) {
        try {
            System.out.println("Iniciando servidor...");

            // Establecer el número de puerto del servidor RMI (opcional)
            int rmiPort = 1099; // Puerto por defecto: 1099
            System.setProperty("java.rmi.server.hostname", "127.0.0.1");

            // Creacion de la implementacion remota
            Persona persona1 = new PersonaImpl("Diego",22,"Male","Student","Mexican");

            Registry registry = LocateRegistry.createRegistry(8080);
            registry.rebind("Diego", persona1);
            System.out.println("Servidor RMI listo para recibir peticiones.");

        }catch (Exception e){
            System.out.println("Server error " + e);
            e.printStackTrace();
        }
    }
}
