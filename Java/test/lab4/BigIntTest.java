
package lab4;

import junit.framework.TestCase;

/**
 *
 * @author z4p
 */
public class BigIntTest extends TestCase {
    
    public BigIntTest(String testName) {
        super(testName);
    }
    
    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }
    
    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    /**
     * Test of add method, of class BigInt.
     */
    public void testAdd() {
        System.out.println("add");
        BigInt d = new BigInt(1212);
        BigInt instance = new BigInt(99);
        BigInt expResult = new BigInt(1311);
        BigInt result = instance.add(d);
        assertEquals(expResult.toString(), result.toString());
    }

    /**
     * Test of sub method, of class BigInt.
     */
    public void testSub() {
        System.out.println("sub");
        BigInt d = new BigInt(1212);
        BigInt instance = new BigInt(99);
        BigInt expResult = new BigInt(-1113);
        BigInt result = instance.sub(d);
        assertEquals(expResult.toString(), result.toString());
    }

    /**
     * Test of mul method, of class BigInt.
     */
    public void testMul() {
        System.out.println("mul");
        BigInt d = new BigInt(1212);
        BigInt instance = new BigInt(99);
        BigInt expResult = new BigInt(119988);
        BigInt result = instance.mul(d);
        assertEquals(expResult.toString(), result.toString());
    }

    /**
     * Test of div method, of class BigInt.
     */
    public void testDiv() throws Exception {
        System.out.println("div");
        BigInt d = new BigInt(99);
        BigInt instance = new BigInt(1212);
        BigInt expResult = new BigInt(12);
        BigInt result = instance.div(d);
        assertEquals(expResult.toString(), result.toString());
    }

    /**
     * Test of mod method, of class BigInt.
     */
    public void testMod() throws Exception {
        System.out.println("mod");
        BigInt d = new BigInt(99);
        BigInt instance = new BigInt(1212);
        BigInt expResult = new BigInt(24);
        BigInt result = instance.mod(d);
        assertEquals(expResult.toString(), result.toString());
    }

    /**
     * Test of toString method, of class BigInt.
     */
    public void testToString() {
        System.out.println("toString");
        BigInt instance = new BigInt(-1212121212);
        String expResult = "-1212121212";
        String result = instance.toString();
        assertEquals(expResult, result);
    }

    /**
     * Test of cmpAbs method, of class BigInt.
     */
    public void testCmpAbs() {
        System.out.println("cmpAbs");
        BigInt a = new BigInt("-11");
        BigInt b = new BigInt(-11);
        int expResult = 0;
        int result = BigInt.cmpAbs(a, b);
        assertEquals(expResult, result);
    }
    
}
