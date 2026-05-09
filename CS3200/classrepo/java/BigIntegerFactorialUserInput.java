import java.math.BigInteger;
import java.util.Scanner;

public class BigIntegerFactorialUserInput {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a non-negative integer: ");

        int number = scanner.nextInt();

        if (number < 0) {
            System.out.println("Factorial is not defined for negative integers.");
        } else {
            BigInteger factorial = calculateFactorial(number);
            System.out.println(number + "! = " + factorial);
        }

        scanner.close();
    }

    public static BigInteger calculateFactorial(int n) {
        BigInteger result = BigInteger.ONE;

        for (int i = 2; i <= n; i++) {
            result = result.multiply(BigInteger.valueOf(i));
        }

        return result;
    }
}
