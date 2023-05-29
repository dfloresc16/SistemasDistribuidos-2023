import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class PersonaImpl extends UnicastRemoteObject implements Persona{

    private String name;

    private String lastName;
    private Integer age;

    private String gender;

    private String occupation;

    private String nationality;

    public PersonaImpl(String name, Integer age, String gender, String occupation, String nationality) throws RemoteException{
        this.name = name;
        this.age = age;
        this.gender = gender;
        this.occupation = occupation;
        this.nationality = nationality;
    }

    @Override
    public String getName() throws RemoteException {
        return this.name;
    }

    @Override
    public String getLastName() throws RemoteException {
        return this.lastName;
    }

    @Override
    public String getOccupation() throws RemoteException {
        return this.occupation;
    }

    @Override
    public String getNationality() throws RemoteException {
        return this.nationality;
    }

    @Override
    public Integer getAge() throws RemoteException {
        return this.age;
    }
}
