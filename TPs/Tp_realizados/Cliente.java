//
// Cliente.java
//
package calculadora;

import org.omg.CORBA.ORB;
import java.util.Scanner;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;

import java.io.*;
public class Cliente {
public static void main (String args[ ]) {

	try {
		// INICIAMOS ORB
		ORB orb = ORB.init(args, null);        
        org.omg.CORBA.Object objRef =  orb.resolve_initial_references("NameService");
        NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
		String name = "Calculo";

		calculo cuentas = calculoHelper.narrow(ncRef.resolve_str(name));

		Scanner scan = new Scanner(System.in);
		int opcion;
		int dato1;
		int dato2;

		System.out.println("Ingrese un numero: ");
		dato1 = scan.nextInt();

		System.out.println("Ingrese un numero: ");
		dato2 = scan.nextInt();

		System.out.println("Ingrese una opcion: ");
		System.out.println("Ingrese 1 para la suma: ");
		System.out.println("Ingrese 2 para la resta: ");
		System.out.println("Ingrese 3 para la multiplicacion: ");
		System.out.println("Ingrese 4 para la division: ");
		
		opcion =scan.nextInt();
		if (opcion==1){
			System.out.println("el resultad de la suma es : "+cuentas.suma(dato1,dato2));
		}
		if (opcion==2){
			System.out.println("el resultad de la resta es : "+ cuentas.resta(dato1,dato2));
		}
		if (opcion==3){
			System.out.println("el resultad de la multiplicacion es : "+cuentas.multiplicacion(dato1,dato2));
		}
		if (opcion==4){
			System.out.println("el resultad de la division es : "+ cuentas.division(dato1,dato2));
		}
		if (opcion >4){
			System.out.println("Debe introducir un numero del 1 al 4 ");
		}


		
	} catch(Exception e) {
		System.out.println("ERROR : " + e);
		e.printStackTrace(System.out);
	}
}
}



