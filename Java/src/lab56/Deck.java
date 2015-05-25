package hs;

import static java.lang.Math.random;
import java.util.ArrayList;

public class Deck {
    private final ArrayList<Card> cards;
    private final String race;
    
    public Deck(String race) {
        this.race = race;
        this.cards = new ArrayList<>();
    }
    
    public void addCard(Card card, int count) {
        for (int i = 0; i < count; ++i) {
            cards.add(card);
        }
    }
    
    public void shuffle() {
        for (int i = 0; i < cards.size()*3; ++i) {
            int d = (int)(random()*cards.size());
            Card c = cards.get(d);
            cards.remove(d);
            cards.add(c);
        }
    }
    
    public Card getCard() throws Exception {
        if (cards.isEmpty()) {
            System.out.println("1111");
            throw new Exception("Deck is empty");
        }
        Card c = cards.get(0);
        cards.remove(0);
        return c;
    }
    
    public String getRace() {
        return this.race;
    }
    
    public static Deck getIGDeck() {
        Deck deck = new Deck("Adeptus Militarium");
        deck.addCard(new Card("Tactical Squad", 1, 1, 1, 0), 8);
        deck.addCard(new Card("Elite Squad", 2, 1, 2, 0), 5);
        deck.addCard(new Card("Heavy Weapon Squad", 2, 2, 3, 0), 4);
        deck.addCard(new Card("Ogryns", 4, 3, 4, 1), 2);
        deck.addCard(new Card("Leman Russ", 7, 7, 5, 0), 3);
        deck.addCard(new Card("Baneblade", 10, 10, 7, 0), 1);
        deck.shuffle();
        return deck;
    }
    
    public static Deck getCSMDeck() {
        Deck deck = new Deck("Chaos Space Marines");
        deck.addCard(new Card("Cultists", 1, 1, 1, 1), 6);
        deck.addCard(new Card("Space Marines", 2, 2, 2, 0), 6);
        deck.addCard(new Card("Possessed", 4, 3, 4, 1), 4);
        deck.addCard(new Card("Obliterators", 4, 3, 5, 0), 2);
        deck.addCard(new Card("Hellbrute", 8, 5, 5, 1), 3);
        deck.addCard(new Card("Land Raider", 8, 8, 6, 0), 2);
        deck.shuffle();
        return deck;
    }
    
    public static Card getCardByName(String name) throws Exception {
        for(Card c : allCards) {
            if (c.title.equals(name)) {
                return c;
            }
        }
        
        throw new Exception("Unknown card: "+name);
    }
    
    static Card[] allCards = {
        new Card("Cultists", 1, 1, 1, 1),
        new Card("Space Marines", 2, 2, 2, 0),
        new Card("Possessed", 4, 3, 4, 1),
        new Card("Obliterators", 4, 3, 5, 0),
        new Card("Hellbrute", 8, 5, 5, 1),
        new Card("Land Raider", 8, 8, 6, 0),
        new Card("Tactical Squad", 1, 1, 1, 0),
        new Card("Elite Squad", 2, 1, 2, 0),
        new Card("Heavy Weapon Squad", 2, 2, 3, 0),
        new Card("Ogryns", 4, 3, 4, 1),
        new Card("Leman Russ", 7, 7, 5, 0),
        new Card("Baneblade", 10, 10, 7, 0)
    }; 
}