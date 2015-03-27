/*
    Выполнил Радкевич Павел, 4 группа ММФ

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

package lab2;

import static lab2.Rocket.delay;

public class Lab2 {
    
    public static void main(String[] args) {
        Rocket r1 = new Rocket();
        
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
}

// што гэта за пачвара?
// для компиляции этой строки нужно около 11-12 Гб оперативы
/*
class A{{int a;try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{try{a=0;}finally{a=0;}}}}}}}}}}}}}A(){}A(int a){}A(char a){}A(double a){}A(float a){}A(long a){}A(short a){}A(boolean a){}A(String a){}A(Integer a){}A(Float a){}A(Short a){}A(Long a){}A(Double a){}A(Boolean a){}A(Character a){}}*/