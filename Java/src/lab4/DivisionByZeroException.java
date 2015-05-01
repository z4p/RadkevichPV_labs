package lab4;


/**
 * Class is used for throwing and processing exceptions
 * when division by zero is the user's greatest wish.
 * @author z4p
 * @version 0.1
 */
public class DivisionByZeroException extends Exception {
    private static final long serialVersionUID = 1L;
    public DivisionByZeroException() {
        super("Division by zero is disabled in this version");
    }
}
