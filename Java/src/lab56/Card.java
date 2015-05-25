package hs;

public class Card {
    public Card(String title, int attack, int life, int price, int spec) {
        this.title = title;
        this.attack = attack;
        this.life = life;
        this.price = price;
        this.spec = spec;
    }
    
    @Override
    public String toString() {
        return title + " \tА" + attack + " \tЖ" + life + "\tОД" + price + " \t" + (spec == 1 ? " ХтХ":"");
    }
    
    public final String title;
    public final int attack;
    public final int life;
    public final int price;
    public final int spec;
}