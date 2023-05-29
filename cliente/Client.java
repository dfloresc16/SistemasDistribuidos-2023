import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("127.0.0.1",8080);
            Persona p1 = (Persona) registry.lookup("Diego");
            String data = "Name " + p1.getName() + "\nLast Name " +p1.getLastName() + "\nAge " + p1.getAge() + "\nOccupation " + p1.getOccupation() + "\nNationality " + p1.getNationality();
            System.out.println(data);
        }catch (Exception e){
            System.out.println("Error client " + e.getMessage());
        }
    }
}
