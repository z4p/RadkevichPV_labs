package javalabs;

import static javalabs.Rocket.delay;

public class JavaLabs {
    public static void lab1() {
        String s3 = (new BigInt("3247")).add(new BigInt("-1691")).toString();    //  1556
        System.out.println(s3);
        
        try {
            BigInt[] dm;// = (new BigInt(1152)).divmod(new BigInt(62));
            dm = (new BigInt(10)).divmod(new BigInt(10));
            System.out.println(dm[0] + " " + dm[1]);
        } catch (Exception e) {
            System.err.println("Ошибка при делении. Вероятно, вы разделили на ноль. Так нельзя");
        }
    }
    
    public static void lab2() {
        Rocket r1 = new Rocket();
        /*
        ракета:
            масса: 3 кг + 2 кг топлива,
            ЖРД: 1 кг топлива / сек, 20 м/с2*кг
        
            2 сек: разгон до 8 м/с
            2,8 сек: макс высота
        */
        r1.addPart(new ScienceModule(1));
        r1.addPart(new FuelTank(1, 2));
        r1.addPart(new LiquidEngine(1, 10, 1));
        r1.addPart(new Separator(0.1));
        r1.addPart(new SolidEngine(2, 20, 4, 5));
        
        for(int countdown = 5; countdown > 0; countdown--) {
            System.out.println(countdown);
            delay(1000);
        }
        r1.start();
    }
    
    public static void main(String[] args) {
        //lab1();
        lab2();
    }
}

//class A{{int a;try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{a=0;}}}}}}}}}}}}}A(){}A(int a){}A(char a){}A(double a){}A(float a){}A(long a){}A(short a){}A(boolean a){}A(String a){}A(Integer a){}A(Float a){}A(Short a){}A(Long a){}A(Double a){}A(Boolean a){}A(Character a){}}