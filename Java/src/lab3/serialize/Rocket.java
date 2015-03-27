package lab3.serialize;

import java.util.LinkedList;

/*
    Симуляция полёта ракеты

    Небольшие импульсные ракеты удобно представить в виде списков. На одном конце 
    лежит полезная нагрузка, далее идут K-тая, ..., 2-я, 1-я ступени, состоящие из 
    топливных баков, двигателей и сепараторов. Двигатели на жидком топливе расходуют 
    топливо из непосредственно прилегающего бака. Твердотопливные двигатели содержат 
    топливо внутри. Сепаратор отстыковывает все элементы ракеты, расположенные ниже. 
    Каждая часть обладает собственной массой, некоторые (баки и ТТ-двигатели) - 
    массой хранимого топлива. Двигатели имеют параметры: расход топлива (кг топлива/
    сек), тяга (ускорение*кг ракеты). По окончанию работы каждой части, 
    автоматически начинает работать следующая.

    Рассчитать максимальную высоту, на которую может подняться ракета, запущенная
    с Земли, заданная списком частей с их характеристиками.
*/

abstract class RocketPart {
    public enum partState {WAIT, ON, OFF, OUT};
    
    private final double weight;
    protected partState state;
    protected RocketPart prevPart;
    
    public RocketPart(double weight) {
        this.weight = weight;
        state = partState.WAIT;
    }
    
    public void setPrevPart(RocketPart prevPart) {
        this.prevPart = prevPart;
    }
    
    public void disconnect() { /* Finish Him */
        state = partState.OUT;
    }
    
    public double getWeight() {
        return (state != partState.OUT) ? weight : 0;
    }
    
    public partState getState() {
        return state;
    }
    
    public abstract void step(double s, Rocket r);
}

class Tank {
    private double fuel;
    
    public Tank(double fuel) {
        this.fuel = fuel;
    }
    
    public double getFuel() {
        return fuel;
    }
    
    public void drainFuel(double fuel) throws Exception {
        if (this.fuel >= fuel) {
            this.fuel -= fuel;
        } else {
            throw new Exception("Not enough fuel");
        }
    }
}

class FuelTank extends RocketPart {
    private final Tank tank;
    
    public FuelTank(double weight, double fuel) {
        super(weight);
        tank = new Tank(fuel);
    }
    
    public void getFuel(double fuel) throws Exception {
        tank.drainFuel(fuel);
    }

    @Override
    public double getWeight() {
        return super.getWeight() + tank.getFuel();
    }
    
    @Override
    public void step(double s, Rocket r) {
        state = partState.OFF;
    }
}

abstract class Engine extends RocketPart {
    protected final double fuelDrain;
    protected final double efficiency;
    protected final Tank fuelTank;
    
    public Engine(double fuelDrain, double efficiency, double weight) {
        super(weight);
        this.efficiency = efficiency;
        this.fuelDrain = fuelDrain;
        fuelTank = null;
    }
}

class SolidEngine extends Engine {
    private final Tank tank;

    public SolidEngine(double fuelDrain, double efficiency, double weight, double fuel) {
        super(fuelDrain, efficiency, weight);
        tank = new Tank(fuel);
    }
    
    @Override
    public double getWeight() {
        return super.getWeight() + tank.getFuel();
    }
    
    @Override
    public void step(double s, Rocket r) {
        if (state == partState.WAIT) {
            state = partState.ON;
        }
        double f = s * fuelDrain;
        try {
            tank.drainFuel(f);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            state = partState.OFF;
        }
        r.addImpulse(s * efficiency);
    }
}

class LiquidEngine extends Engine {
    public LiquidEngine(double fuelDrain, double efficiency, double weight) {
        super(fuelDrain, efficiency, weight);
    }
    
    @Override
    public void step(double s, Rocket r) {
        if (state == partState.WAIT) {
            state = partState.ON;
        }
        double f = s * fuelDrain;
        try {
            ((FuelTank)(prevPart)).getFuel(f);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            state = partState.OFF;
        }
        r.addImpulse(s * efficiency);
    }
}

class Separator extends RocketPart {
    public Separator(double weight) {
        super(weight);
    }

    @Override
    public void step(double s, Rocket r) {
        if (state == partState.WAIT) {
            state = partState.ON;
        } else if (state == partState.ON) {
            state = partState.OFF;
            r.cutTailParts(r.getCurrentPartNumber());
            System.out.println("Separate!");
        }
    }
}

class ScienceModule extends RocketPart {
    public ScienceModule(double weight) {
        super(weight);
    }

    @Override
    public void step(double s, Rocket r) {
        if (state == partState.WAIT) {
            state = partState.ON;
        } else if (state == partState.ON) {
            state = partState.OFF;
            System.out.println("ScienceModule works!");
        }
    }
}

public class Rocket {
    private final LinkedList<RocketPart> partList;
    private double speed;
    private int curPartNum;
    
    public Rocket() {
        partList = new LinkedList<>();
        speed = 0;
    }
    
    public void addPart(RocketPart part) {
        if (partList.size() > 0) {
            part.setPrevPart(partList.get(0));
        }
        partList.addFirst(part);
    }
    
    public static void delay(long ms) {
        long t = System.currentTimeMillis() + ms;
        while (System.currentTimeMillis() < t) {}
    }
    
    public void start() {
        int i = 0;
        double dt = 0.1;
        double tm = 0, maxh = 0, h = 0;
        int cnt = 0;
        
        while(h >= 0 || i < partList.size()) {
            curPartNum = i;
            delay((long)dt*1000);
            cnt++;
            if (i < partList.size()) {
                switch (partList.get(i).getState()) {
                    case WAIT:
                    case ON:
                        partList.get(i).step(dt, this);
                        break;
                    case OFF:
                    case OUT:
                        i++;
                        break;
                }
            }
            
            double g = (9.8 - 0.000003 * h) * dt; // ускорение (притяжение Земли)
            speed = speed - g*dt;                 // падение скорости
            h += dt * speed;                      // прирост высоты
            if (h > maxh) maxh = h;
            else tm = cnt*dt;
        }
        System.out.println(tm + ": " + maxh);
    }
    
    public void addImpulse(double i) {
        speed += i/getWeight();
    }
    
    public double getWeight() {
        double w = 0;
        for(RocketPart part: partList) {
            w += part.getWeight();
        }
        return w;
    }
    
    public void cutTailParts(int n) {
        for(int i = 0; i < n; i++) {
            partList.get(i).disconnect();
        }
    }

    int getCurrentPartNumber() {
        return this.curPartNum;
    }
}
