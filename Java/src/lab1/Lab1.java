package lab1;

public class Lab1 {
    public static void main() {
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
}
