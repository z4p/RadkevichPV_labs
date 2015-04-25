package lab4;

import java.util.logging.*;

/**
 * Main class
 * @author z4p
 */
public class Main {
    
    private static final Logger logger = Logger.getLogger(Main.class.getName());
    
    public static void main(String args[]) {
        String s3 = (new BigInt("3247")).add(new BigInt("-1691")).toString();    //  1556
        System.out.println(s3);
        
        try {
            BigInt[] dm;// = (new BigInt(1152)).divmod(new BigInt(62));
            dm = (new BigInt(12)).divmod(new BigInt(10));
            System.out.println(dm[0] + " " + dm[1]);
        } catch (DivisionByZeroException e) {
            System.err.println("Ошибка при делении. Вероятно, вы разделили на ноль. Так нельзя");
        }
    }
}
