package lab3.regexp;

import java.util.regex.Pattern;

/*
    Задание 1. Выполнил Радкевич Павел, 4 группа ММФ
    20. В тексте найти первую подстроку максимальной длины, не содержащую букв.
*/

public class RegExp {
    public static void main(String[] args) {
        String text = "...It is as so a thousand mouth cry out in pain!\n"
                + "WRA!!!!! D'you hear these voices too?..";
        String maxLine = "";
        
        Pattern p = Pattern.compile("[^a-zA-Z]+", Pattern.MULTILINE);
        int offset = 0;
        for (int i = 0; i < text.length(); ++i) {
            if (p.matcher(text.substring(offset, i)).matches()) {
                if (i-offset > maxLine.length())
                    maxLine = text.substring(offset, i);
            } else {
                offset = i;
            }
        }
        
        System.out.println("String: '" + text + "'\nSubstring: '" + maxLine + "'\nLength: " + maxLine.length());
    }
}
