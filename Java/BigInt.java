package javalabs;

import java.util.ArrayList;


/*
 * Вариант 1
 * Длинные целые числа. Это числа с произвольным количеством цифр (например число
 * с 1000 цифр). Необходимо реализовать арифметические операции с этими числами
 * (включая деление и взятие остатка, а также смешанную операцию деления и взятия
 * остатка)
*/
class BigInt implements Cloneable {
    private ArrayList<Integer> nums;  // 123 = [3,2,1]
    private int sign;                 // {-1 | 1}
    
    public BigInt() {
        nums = new ArrayList<>();
        sign = 1;
    }
    
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
    
    public BigInt(String d) {
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
    }

    
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
        
        return res;
    }
    
    public BigInt sub(BigInt d) {
        BigInt b = new BigInt(d.toString());
        b.sign = d.sign * -1;
        return this.add(b);
    }
    
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
        return res;        
    }
    
    public BigInt div(BigInt d) throws Exception {
        BigInt res[] = divmod(d);
        return res[0];        
    }
    
    public BigInt mod(BigInt d) throws Exception {
        BigInt res[] = divmod(d);
        return res[1];        
    }
    
    public BigInt[] divmod(BigInt d) throws Exception {
        BigInt res[] = new BigInt[2];
        res[0] = new BigInt();
        res[1] = new BigInt();
        if (d.toString().equals("0")) {
            throw new Exception("Division by zero");
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
            if (i == -1) {
                //break;
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
        return res;
    }
    
    @Override
    public BigInt clone() throws CloneNotSupportedException {
        return (BigInt)(super.clone());
    }
    
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
    
    
    /* cmbAbs returns 
     *   1, if a > b
     *  -1, if a < b
     *   0, if a == b
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
}