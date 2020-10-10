/*************************************************************************
	> File Name: FloatTest.java
	> Author: 
	> Mail: 
	> Created Time: 2020年10月10日 星期六 19时19分36秒
 ************************************************************************/

public class FloatTest
{
    public static void main(String[] args)
    {
        float af = 5.2345678f;
        System.out.println(af);
        double a = 0.0;
        double d = Float.NEGATIVE_INFINITY;
        double c = Double.NEGATIVE_INFINITY;

        System.out.println(c == d);

        System.out.println(a / a);

        System.out.println(a / a == Float.NaN);

        System.out.println(6.0 / 0 == 555.0/0);

        System.out.println(-8 / a);

        System.out.println(0 / 0);
    }
}
