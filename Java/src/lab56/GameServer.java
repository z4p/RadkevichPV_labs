package hs;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.Serializable;
import static java.lang.Math.random;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

public class GameServer {
    public static ArrayList<Game> games;
    
    public static void main(String[] args) {
        try {
            ArrayList<PlayerThread> players = new ArrayList<>();
            games = new ArrayList<>();
            
            Garbager gb = new Garbager(players);
            gb.start();
            
            ServerSocket ss = new ServerSocket(7777);
            System.out.println("Server started on " + ss.getLocalPort());
            while (true) {
                Socket s = ss.accept();
                System.out.println(s.getInetAddress() + " connected");
                PlayerThread p = new PlayerThread(s, new Player());
                p.start();
                players.add(p);
            }
        } catch (IOException ex) {
            System.out.println("ServerSocket error: " + ex.getLocalizedMessage());
        }
        
    }
}

class Garbager extends Thread {
    private final ArrayList<PlayerThread> p;
    
    public Garbager(ArrayList<PlayerThread> players) {
        p = players;
    }
    
    @Override
    synchronized public void run() {
        while (true) {
            PlayerThread op = null;
            for(PlayerThread pt : this.p) {
                if (!pt.isAlive() || !pt.getPlayer().isAlive()) {
                    p.remove(pt);
                }
                if (pt.getPlayer().isReady()) {
                    if (op == null) {
                        op = pt;
                        System.out.println("p1 found");
                    } else {
                        op.setOpponent(pt);
                        pt.setOpponent(op);
                        GameServer.games.add(new Game(op.getPlayer(), pt.getPlayer()));
                        System.out.println("p2 found");
                        System.out.println("new game has started");
                    }
                }
            }
            try {
                this.wait(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(Garbager.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}

class Player {
    private int race;
    private String name = "man";
    private boolean _ready;
    private Deck deck;
    private ArrayList<String> msgs;
    private ArrayList<Card> hand;
    private ArrayList<Card> table;
    private PlayerThread pth;
    private int health;
    
    public synchronized void takeCard() {
        try {
            Card c = deck.getCard();
            hand.add(c);
            msgs.add("card "+c.title);
        } catch (Exception ex) {
            System.out.println(deck.getRace());
            Logger.getLogger(Player.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public synchronized ArrayList<String> getMessages() {
        return msgs;
    }
    
    Player() {
        health = 30;
        _ready = false;
        msgs = new ArrayList<>();
        hand = new ArrayList<>();
        table = new ArrayList<>();
    }
    
    public synchronized void setPlayerThread(PlayerThread pth) {
        this.pth = pth;
    }
    
    public synchronized void setRace(int race) {
        this.race = race;
        switch (race) {
            case 1:
                deck = Deck.getIGDeck();
                break;
            case 2:
                deck = Deck.getCSMDeck();
                break;
        }        
    }
    
    public synchronized void setReadyState(boolean state) {
        _ready = state;
    }
    
    public synchronized boolean isReady() {
        return _ready;
    }
    
    public synchronized void setName(String name) {
        this.name = name;        
    }
    
    public synchronized void damage(int d) {
        health-=d;
    }
    
    public synchronized boolean isAlive() {
        return health > 0;
    }
}

class Game {
    private final Player p1;
    private final Player p2;

    private int p1Health = 30;
    private int p2Health = 30;
    private int move = 1;
    
    public int getMove() {
        return move;
    }
    
    public Game(Player p1, Player p2) {
        this.p1 = p1;
        this.p2 = p2;
        
        p1.setReadyState(false);
        p2.setReadyState(false);
        
        try {
            if (random()*2 < 1) {
                Player t = p1;
                p1 = p2;
                p2 = t;
            }
            
            p1.takeCard();
            p1.takeCard();
            p1.takeCard();
            
            p2.takeCard();
            p2.takeCard();
            p2.takeCard();
            
            while (p1Health > 0 && p2Health > 0) {
                
            }
        } catch (Exception ex) {
            Logger.getLogger(Game.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

class PlayerThread extends Thread {
    private final Socket s;
    DataOutputStream out;
    DataInputStream in;
    private String name = "man";
    private Player player;
    private PlayerThread opponent;
    
    public void setOpponent(PlayerThread opponent) {
        this.opponent = opponent;
    }
        
    public void move() {
        
    }
    
    public void waitForMove() {
        
    }
    
    public Player getPlayer() {
        return player;
    }
    
    public PlayerThread(Socket s, Player player) {
        super();
        this.s = s;
        this.player = player;
    }
    
    @Override
    public synchronized void run() {
        try {
            this.player.setPlayerThread(this);
            
            out = new DataOutputStream( s.getOutputStream() );
            in = new DataInputStream( s.getInputStream() );
            out.writeUTF("hello");
            while (true) {
                if (in.available() > 0) {
                    String t = in.readUTF();
                    System.out.println( s.getRemoteSocketAddress() + ": " + t );
                    if (t.startsWith("name")) {
                        player.setName(t.substring(5));
                    }
                    if (t.startsWith("quit")) {
                        s.close();
                        return;
                    }
                    if (t.startsWith("race")) {
                        if ("1".equals(t.substring(5, 6))) player.setRace(1);
                        if ("2".equals(t.substring(5, 6))) player.setRace(2);
                        player.setReadyState(true);
                    }
                }
                while (player.getMessages().size() > 0) {
                    out.writeUTF(player.getMessages().get(0));
                    player.getMessages().remove(0);
                }

                this.wait(100);
            }
        }
        catch(IOException e) {
            Logger.getLogger(this.getClass().getName()).log(Level.WARNING, "IOEx in thread", e);
        }
        catch(InterruptedException e) {
            Logger.getLogger(this.getClass().getName()).log(Level.WARNING, "Thread has been interrupted the bad way!", e);
        }
    }
    
}
