import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Persona extends Remote {

    public String getName() throws RemoteException;

    public String getLastName() throws RemoteException;

    public String getOccupation() throws RemoteException;

    public String getNationality() throws RemoteException;

    public Integer getAge() throws RemoteException;


}
