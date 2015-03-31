package lab3.serialize;

import java.nio.ByteBuffer;
import java.util.ArrayList;

/*
Взял наливки из черешен
Взял пельмешков, сел за стол
We don't need no education
We don't need no thought control
*/

class SmallSystem implements SerializableByBytes {
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
    public byte[] serialize() {
        return SR.serializeInt(cores).array();
    }

    @Override
    public void deserialize(byte[] a) {
        ByteBuffer b = ByteBuffer.wrap(a);
        cores = SR.deserializeInt(b);
        b.get(a, b.arrayOffset(), b.limit()-b.position());
    }

}

class LargeSystem extends SmallSystem {
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
    public byte[] serialize() {
        ArrayList<Byte> a = new ArrayList<>();
        byte[] s = super.serialize();
        for(byte bt: s) {
            a.add(bt);
        }
        ByteBuffer b = SR.serializeDouble(ECE);
        for(byte bt: b.array()) {
            a.add(bt);
        }
        byte[] res = new byte[a.size()];
        for(int i = 0; i < a.size(); i++)
            res[i] = a.get(i);
        return res;
    }

    @Override
    public void deserialize(byte[] a) {
        super.deserialize(a);
        ByteBuffer b = ByteBuffer.wrap(a);
        ECE = SR.deserializeDouble(b);
        b.get(a, b.arrayOffset(), b.limit()-b.position());
    }
}

public class FuckTheSystem implements SerializableByBytes {
    private final SmallSystem ss;
    private final LargeSystem ls;

    public FuckTheSystem() {
        ss = new SmallSystem();
        ls = new LargeSystem();
    }
    
    public double run() {
        return ss.getCores() + ls.getCores();
    }

    @Override
    public byte[] serialize() {
        ArrayList<Byte> a = new ArrayList<>();
        byte[] sb = ss.serialize();
        byte[] lb = ls.serialize();
        for(byte bt: sb) {
            a.add(bt);
        }
        for(byte bt: lb) {
            a.add(bt);
        }
        byte[] res = new byte[a.size()];
        for(int i = 0; i < a.size(); i++)
            res[i] = a.get(i);
        return res;
    }

    @Override
    public void deserialize(byte[] a) {
        ss.deserialize(a);
        ls.deserialize(a);
    }
}
