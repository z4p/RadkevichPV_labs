package lab4;

import java.io.IOException;
import java.util.logging.*;

/**
 * Main class
 * @author z4p
 */
public class Main {
    
    public static void main(String args[]) {
//        try {
//            LogManager.getLogManager().readConfiguration(
//                    Main.class.getResourceAsStream("logging.properies"));
//        } catch (IOException | SecurityException ex) {
//            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
//        }
        
        try {
            BigInt[] dm = (new BigInt(12)).divmod(new BigInt("-0"));
            System.out.println(dm[0] + " " + dm[1]);
        } catch (DivisionByZeroException e) {
            Logger.getLogger(Main.class.getName()).log(Level.WARNING, 
                    "User has divided something by zero", e);
            System.err.println("Ошибка при делении. Вероятно, вы разделили на ноль. Так нельзя");
        }
    }
}
