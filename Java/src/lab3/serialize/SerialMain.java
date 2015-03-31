package lab3.serialize;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.logging.Level;
import java.util.logging.Logger;

public class SerialMain {
    public static void main(String[] args) {
        FuckTheSystem fts = new FuckTheSystem();
        
        try {
            Path p = Paths.get("simple.rct");
            Files.write(p, fts.serialize());
            fts.deserialize( Files.readAllBytes(p) );
        } catch (IOException ex) {
            Logger.getLogger(SerialMain.class.getName()).log(Level.SEVERE, null, ex);
            System.err.println("Some shit with files happened");
        }
        
        System.out.println( fts.run() );
    }
}
