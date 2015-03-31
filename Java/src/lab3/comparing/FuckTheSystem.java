package lab3.comparing;


/*
Взял наливки из черешен
Взял пельмешков, сел за стол
We don't need no education
We don't need no thought control
*/

class SmallSystem implements TransitiveCmp {
    protected int cores;
    
    public SmallSystem() {
        cores = 1;
    }
    
    public void inc() {
        ++cores;
    }
    
    public double getCores() {
        return cores;
    }

    @Override
    public boolean isEqual(Object obj) {
        SmallSystem s = (SmallSystem)obj;
        return cores == s.cores;
    }

    @Override
    public boolean compare(Object obj1, Object obj2) {
        SmallSystem s1 = (SmallSystem)obj1;
        SmallSystem s2 = (SmallSystem)obj2;
        return s1.isEqual(s2) && s2.isEqual(s1);
    }

   
}

class LargeSystem extends SmallSystem implements TransitiveCmp {
    protected double ECE;
    
    public LargeSystem() {
        super();
        ECE = 0.5;
    }
    
    @Override
    public void inc() {
        super.inc();
        ECE += 0.1;
    }
    
    @Override
    public double getCores() {
        return super.getCores() * ECE;
    }
    
    @Override
    public boolean isEqual(Object obj) {
        LargeSystem s = (LargeSystem)obj;
        return super.isEqual(s) && ECE == s.ECE;
    }

    @Override
    public boolean compare(Object obj1, Object obj2) {
        LargeSystem s1 = (LargeSystem)obj1;
        LargeSystem s2 = (LargeSystem)obj2;
        return s1.isEqual(s2) && s2.isEqual(s1) && super.compare(s1, s2);
    }
}

public class FuckTheSystem implements TransitiveCmp {
    private final SmallSystem ss;
    private final LargeSystem ls;

    public FuckTheSystem() {
        ss = new SmallSystem();
        ls = new LargeSystem();
    }
    
    public void incSS() {
        ss.inc();
    }
    
    public double run() {
        return ss.getCores() + ls.getCores();
    }

    @Override
    public boolean isEqual(Object obj) {
        FuckTheSystem f = (FuckTheSystem) obj;
        return ss.compare(ss, f.ss) && ls.compare(ls, f.ls);
    }

    @Override
    public boolean compare(Object obj1, Object obj2) {
        FuckTheSystem f1 = (FuckTheSystem) obj1;
        FuckTheSystem f2 = (FuckTheSystem) obj2;
        return f1.isEqual(f2) && f2.isEqual(f1);
    }
}
