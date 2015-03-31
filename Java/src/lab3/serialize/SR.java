package lab3.serialize;

import java.nio.ByteBuffer;

public class SR {
    public static ByteBuffer serializeInt(int d) {
        ByteBuffer b = ByteBuffer.allocate(4);
        b.putInt(d);
        return b;
    }
    
    public static ByteBuffer serializeDouble(double d) {
        ByteBuffer b = ByteBuffer.allocate(8);
        b.putDouble(d);
        return b;
    }
    
    public static int deserializeInt(ByteBuffer b) {
        return b.getInt();
    }
    
    public static double deserializeDouble(ByteBuffer b) {
        return b.getDouble();
    }
}

