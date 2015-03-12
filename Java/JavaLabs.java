package javalabs;

public class JavaLabs {
    public static void lab1() {
        String s3 = (new BigInt("3247")).add(new BigInt("-1691")).toString();    //  1556
        System.out.println(s3);
        
        try {
            BigInt[] dm = (new BigInt("1152")).divmod(new BigInt("62"));
            System.out.println("1152 / 62 = " + dm[0] + " (" + dm[1] + ")");
        } catch (Exception e) {
            System.err.println("Ошибка при делении. Вероятно, вы делили на ноль");
        }
    }
    
    public static void lab2() {
        Rocket r1 = new Rocket();
        r1.addPart(new ScienceModule(1));
        r1.addPart(new FuelTank(2, 1.5));
        r1.addPart(new LiquidEngine(0.1, 1, 0.5));
    }
    
    public static void main(String[] args) {
        lab1();
        lab2();
    }
}

//class A{{int a;try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{a=0;}}}}}}}}}}}}}A(){}A(int a){}A(char a){}A(double a){}A(float a){}A(long a){}A(short a){}A(boolean a){}A(String a){}A(Integer a){}A(Float a){}A(Short a){}A(Long a){}A(Double a){}A(Boolean a){}A(Character a){}}