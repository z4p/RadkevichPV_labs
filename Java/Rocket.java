package javalabs;

import java.util.ArrayList;

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
    public enum partState {WAIT, ON, OFF};
    
    private final double weight;
    protected partState state;
    
    public RocketPart(double weight) {
        this.weight = weight;
        state = partState.WAIT;
    }
    
    public double getWeight() {
        return weight;
    }
    
    public partState getState() {
        return state;
    }
    
    public abstract void step(double s);
}

class Tank {
    private double fuel;
    
    public Tank(double fuel) {
        this.fuel = fuel;
    }
    
    public void getFuel(double fuel) throws Exception {
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
        tank.getFuel(fuel);
    }

    @Override
    public void step(double s) {
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
    public void step(double s) {
        if (state == partState.WAIT) {
            state = partState.ON;
        }
        double f = s * fuelDrain;
        try {
            tank.getFuel(f);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            state = partState.OFF;
        }
    }
}

class LiquidEngine extends Engine {
    private FuelTank tank;

    public LiquidEngine(double fuelDrain, double efficiency, double weight) {
        super(fuelDrain, efficiency, weight);
        tank = null;
    }
    
    public void setFuelTank(FuelTank tank) {
        this.tank = tank;
    }
    
    @Override
    public void step(double s) {
        if (state == partState.WAIT) {
            state = partState.ON;
        }
        double f = s * fuelDrain;
        try {
            tank.getFuel(f);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            state = partState.OFF;
        }
    }
}

class Separator extends RocketPart {
    public Separator(double weight) {
        super(weight);
    }

    @Override
    public void step(double s) {
        if (state == partState.WAIT) {
            state = partState.ON;
        } else if (state == partState.ON) {
            state = partState.OFF;
            System.out.println("Separate!");
        }
    }
}

class ScienceModule extends RocketPart {
    public ScienceModule(double weight) {
        super(weight);
    }

    @Override
    public void step(double s) {
        if (state == partState.WAIT) {
            state = partState.ON;
        } else if (state == partState.ON) {
            state = partState.OFF;
            System.out.println("ScienceModule works!");
        }
    }
}

public class Rocket {
    private ArrayList<RocketPart> partList;
    
    public Rocket() {
        partList = new ArrayList<>();
    }
    
    public void addPart(RocketPart part) {
        partList.add(0, part);
    }
    
    public void start(double s) {
        long t = System.currentTimeMillis();
        System.out.println("3");
        
        boolean finished = false;
        int i = 0;
        do {
            
        } while(!finished); 
    }
    
    private double getWeight() {
        double w = 0;
        for(RocketPart part: partList) {
            w += part.getWeight();
        }
        return w;
    }
}
