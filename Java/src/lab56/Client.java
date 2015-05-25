package hs;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Client {
    public static void redraw(String msg) throws IOException, InterruptedException {
//        Process p = Runtime.getRuntime().exec("clr");
//        p.waitFor();
//        p.destroy();
        System.out.println(msg);
    }
    
    public static char readKey(char from, char to) {
        char c = '0';
        try {
            do {
                c = (char) System.console().reader().read();
            } while (c < from || c > to);
        } catch (IOException e) {}
        return c;
    }
    
    public static void main(String[] args) {
        String addr = "127.0.0.1";
        if (args.length > 0) {
            addr = args[0];
        }
        try {
            Socket s = new Socket(InetAddress.getByName(addr), 7777);
            DataInputStream in = new DataInputStream(s.getInputStream());
            //DataInputStream keyb = new DataInputStream(System.in);
            DataOutputStream out = new DataOutputStream(s.getOutputStream());
            
            int move = 0;
            ArrayList<Card> hand = new ArrayList<>();
            
            while (true) {
                while (in.available() > 0) {
                    String msg = in.readUTF();
                    if (msg.startsWith("hello")) {
                        System.out.println("Connected!\nSelect the race you want to play for:"
                                + "\n 1 - Astra Militarium\n 2 - Chaos Space Marines\n");
                        char c = readKey('1', '2');
                        String race = "race " + c;
                        System.out.println("Waiting for other player...");
                        out.writeUTF(race);
                    }
                    if (msg.startsWith("card")) {
                        try {
                            hand.add(Deck.getCardByName(msg.substring(5)));
                        } catch (Exception ex) {
                            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, msg, ex);
                        }
                    }
                    
                    if (msg.startsWith("yourturn")) {
                        
                        // move phase
                        
                        move++;
                        int ap = move+2;
                        char ch;
                        do {
                            System.out.println("\n\n Очков Действия: "+ap);
                            System.out.println("Выберите карту для хода (9 - отказ от хода):");
                            int i = 0;
                            for (Card c : hand) {
                                System.out.println(i+" "+c);
                                ++i;
                            }
                            ch = readKey('0', '9');
                            if (ch == '9') break;
                            Card card = hand.get((int)ch);
                            if (ap < card.price) {
                                System.out.println("Недостаточно ОД");
                                continue;
                            } else {
                                ap -= card.price;
                            }
                            out.writeUTF("card "+card);
                        } while (ch != '9');
                        
                        // attack phase
                        
                        
                    }
                }
            }
        } catch (IOException ex) {
            System.out.println("Client error: " + ex.getLocalizedMessage());
        }
    }
}
