package lab4;

import java.util.ArrayList;

/**
 * Implements long arithmetic for integers
 * @author z4p
 * @version 0.1
 */
public class BigInt {
    private ArrayList<Integer> nums;  // 123 = [3,2,1]
    private int sign;                 // {-1 | 1}
  
    /**
     * Returns BigInt, that is equal to given integer
     * @param d given integer
     */
    public BigInt(int d) {
        nums = new ArrayList<>();
        
        if (d >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        d = Math.abs(d);
        
        while (d > 0) {
            int a = d % 10;
            d /= 10;
            nums.add(new Integer(a));
        }
    }
    
    /**
     * <p>Returns BigInt, that is equal to given integer, written in string in 
     * decimal form.</p>
     * <p>If there are some no-decimal symbols present, they are passed.
     * If there are no decimal symbols, it throws <i>NumberFormatException</i>.<p>
     *
     * <p>For example:</p>
     * <p>"31459" => 31459;</p>
     * <p>"2 718 281 828 459 0" => 27182818284590;</p>
     * <p>"-42A" => -42;</p>
     * <p>but "AFh" => NumberFormatException.</p>
     * 
     * 
     * @param d string with an integer
     * @throws NumberFormatException
     */
    public BigInt(String d) throws NumberFormatException {
        nums = new ArrayList<>();
        sign = 1;
        
        for(int i = d.length()-1; i >= 0; i--) {
            if (d.charAt(i) >= '0' && d.charAt(i) <= '9') {
                Integer a = Integer.parseInt( d.substring(i,i+1) );
                nums.add(a);
            }
            if (d.charAt(i) == '-') {
                sign = -1;
                break;
            }
        }
        
        if (nums.isEmpty()) {
            throw new NumberFormatException();
        }
    }

    /**
     * Adds summand d to this digit
     * @param d summand
     * @return BigInt, as the sum
     */
    public BigInt add(BigInt d) {
        BigInt res = new BigInt();
        int maxLength = (nums.size() > d.nums.size()) ? nums.size() : d.nums.size();
        this.normalize(maxLength);
        d.normalize(maxLength);
        
        int carry = 0;
        int s1 = this.sign;
        int s2 = d.sign;
        if (s1 == -1 && s2 == -1) {
            s1 = 1;
            s2 = 1;
            res.sign = -1;
        }
        
        for(int i = 0; i < maxLength; i++) {
            int sum = nums.get(i)*s1 + d.nums.get(i)*s2 + carry;
            carry = 0;
            if (sum > 9) {
                carry = 1;
                sum %= 10;
            }
            if (sum < 0) {
                sum += 10;
                carry--;
            }
            res.nums.add( sum );
        }
        if (carry == 1) {
            res.nums.add( 1 );
        }
        if (carry == -1) {
            res.nums.set(0, 10-res.nums.get(0));
            for (int i = 1; i < res.nums.size(); i++) {
                res.nums.set(i, 9-res.nums.get(i));
            }
            res.sign = -1;
        }
        
        res.normalize();
        this.normalize();
        d.normalize();
        
        assert res.nums.size > 0;
        
        return res;
    }
    
    /**
     * Subtract digit d from this digit
     * @param d subtrahend
     * @return BigInt, as the difference
     */
    public BigInt sub(BigInt d) {
        BigInt b = new BigInt(d.toString());
        b.sign = d.sign * -1;
        return this.add(b);
    }
    
    /**
     * Multiply this digit by d
     * @param d multiplier
     * @return BigInt, as the product
     */
    public BigInt mul(BigInt d) {
        BigInt res = new BigInt();
        
        for(int i = 0; i < d.nums.size(); i++) {
            BigInt a = new BigInt();
            int carry = 0;
            
            for(int j = 0; j < i; j++) {
                a.nums.add(0);
            }
            for(int j = 0; j < this.nums.size(); j++) {
                int p = this.nums.get(j) * d.nums.get(i) + carry;
                carry = p / 10;
                p = p % 10;
                a.nums.add(p);
            }
            a.nums.add(carry);
            
            res = res.add(a);
        }
        
        res.sign = this.sign * d.sign;
        
        assert res.nums.size > 0;
        
        return res;        
    }
    
    /**
     * Divides this digit by d and returns the result
     * @param d divisor
     * @throws DivisionByZeroException
     * @return BigInt, as the quotient
     */
    public BigInt div(BigInt d) throws DivisionByZeroException {
        BigInt res[] = divmod(d);
        return res[0];        
    }
    
    /**
     * Divides this digit by d and returns the result
     * @param d divisor
     * @throws DivisionByZeroException
     * @return BigInt, as a remainder
     */
    public BigInt mod(BigInt d) throws DivisionByZeroException {
        BigInt res[] = divmod(d);
        return res[1];
    }
    
    /**
     * Divides this digit by d and returns the result
     * @param d divisor
     * @throws DivisionByZeroException
     * @return BigInt[2], where [0] is the quotient and [1] is a remainder of division
     */
    public BigInt[] divmod(BigInt d) throws DivisionByZeroException {
        BigInt res[] = new BigInt[2];
        res[0] = new BigInt();
        res[1] = new BigInt();
        if (d.toString().equals("0")) {
            throw new DivisionByZeroException();
        }

        BigInt a = new BigInt();
        
        BigInt r = new BigInt();
        
        int i = this.nums.size()-1;
        do {
            do {
                a.nums.add(0, new Integer(this.nums.get(i)));
                if (BigInt.cmpAbs(a, d) == -1) {
                    r.nums.add(0);
                }
                i--;
            } while (BigInt.cmpAbs(a, d) == -1 && i > -1);
            if (i == -1 && BigInt.cmpAbs(a, d) == -1) {
                break;
            }
            for(int j = 2; j <= 9; j++) {
                if (BigInt.cmpAbs(a, d.mul(new BigInt(j))) == -1) {
                    int k = j-1;
                    r.nums.add(k);
                    a = a.sub(d.mul(new BigInt(k)));
                    break;
                }
            }
        } while (i != -1);
        
        res[1] = a;
        for(int j = r.nums.size()-1; j >= 0; j--) {
            res[0].nums.add(r.nums.get(j));
        }
        
        res[0].normalize();
        res[0].sign = this.sign * d.sign;
        res[1].sign = this.sign;
        
        assert res[0].nums.size > 0;
        assert res[1].nums.size > 0;
        
        return res;
    }
    
    /**
     * Returns the String, that contains that digit
     * @return Storing digit in the form of String
     */
    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        if (sign == -1) {
            s.append("-");
        }
        for(int i = nums.size()-1; i >= 0; i--) {
            s.append(nums.get(i));
        }
        
        return s.toString();
    }
    
    
    /**
     * Compares two digits (sign-insensitive)
     * @param a first digit
     * @param b second digit
     * @return  <p>1, if a > b;</p>
     * <p>-1, if a < b;</p>
     * <p>0, if a == b</p>
    */
    public static int cmpAbs(BigInt a, BigInt b) {
        a.normalize();
        b.normalize();
        if (a.nums.size() > b.nums.size()) {
            return 1;
        }
        if (a.nums.size() < b.nums.size()) {
            return -1;
        }
        BigInt c = a.sub(b);
        for (int i = a.nums.size()-1; i >= 0; i--) {
            if (a.nums.get(i) > b.nums.get(i)) {
                return 1;
            }
            if (a.nums.get(i) < b.nums.get(i)) {
                return -1;
            }
        }
        return 0;
    }
    
    // доведение числа разрядов до n. При n=0 - удаление всех нулей в старших разрядах
    private void normalize(int n) {
        if (n == 0) {
            while (nums.get(nums.size()-1) == 0 && nums.size() > 1) {
                nums.remove(nums.size()-1);
            }
        } else {
            for (int i = nums.size(); i < n; i++) {
                nums.add( 0 );
            }
        }
    }
     
    private void normalize() {
        normalize(0);
    }
         
    /**
     * BigInt constructor without parameters. For technical purposes only.
     */
    private BigInt() {
        nums = new ArrayList<>();
        sign = 1;
    }
}