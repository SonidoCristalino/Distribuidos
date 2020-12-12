package   calculadora;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.ORB;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;
class ImplementacionFunciones extends calculoPOA{
private ORB orb;

    public void setORB(ORB orb_val) {
    orb = orb_val; 
    }


    public int suma (int a, int b ) {
        return a+b ;
    }

    public int resta(int a, int b) {
        return a-b;
    }        

    public int multiplicacion (int a, int b) {
        return a* b;
    }

    public double division (int a, int b) {
        if(b < 1){
            return a/1; 
        }
        else {
            return a/b;
        }
        
    }
}

public class Servidor {

    public static void main(String[] args) {
        try {

            // Creación e Inicialización del ORB
            ORB orb = ORB.init(args, null);
            POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
            rootpoa.the_POAManager().activate();

            // Se realiza la instancia para implementar las Funciones Remotas
            ImplementacionFunciones calcimp = new ImplementacionFunciones();
		    calcimp.setORB(orb);         
	        org.omg.CORBA.Object ref = rootpoa.servant_to_reference(calcimp);
      	    calculo href = calculoHelper.narrow(ref);
            // obtiene el nombre raiz del contexto
            org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
            NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
            // se establece el nombre que identifica al servidor en el contexto 
            String name = "Calculo";
            NameComponent path[] = ncRef.to_name(name);
            ncRef.rebind(path, href);

        	System.out.println(" Inicio el servidor :) ");         
            // se indica que ORB debe ser iniciada en el ontexto establecido 
		    orb.run();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    
}
