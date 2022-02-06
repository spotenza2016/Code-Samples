//Class gives the factorial of the given number.
public class Factorial {
    //Function gives the factorial in a recursive way.
    public static long pureRecursive(int n) {
        //If the given number is 0, throws Illegal Argument Exception.
        if (n <= 0) {
            throw new IllegalArgumentException();
        }
        //Otherwise, if the number is 1, triggers the base function of returning 1.
        else if (n == 1) {
            return 1;
        }
        //Otherwise, calls itself for the previous number (recursive) and multiplies the result by the current number, returning it.
        else {
            return n * pureRecursive(n - 1);
        }
    }

    //Function starts the tail() recursive function, calling it with a total of 1 and returning its result.
    public static long tailRecursive(int n) {
        return tail(n, 1);
    }

    //Function takes the given number and total, and finds the factorial.
    private static long tail(int n, long total) {
        //If the given number is 0, throws Illegal Argument Exception
        if (n <= 0) {
            throw new IllegalArgumentException();
        }
        //Otherwise, if the given number is 1, returns the current total.
        else if (n == 1) {
            return total;
        }
        //Otherwise, updates the total.
        else {
            //Multiplies the current total by the current number.
            total *= n;

            //Calls itself for the previous number (recursive), returning the total factorial found.
            return tail(n - 1, total);
        }
    }

    //Function iterates to find the factorial of the given number.
    public static long iterative(int n) {
        //If the given number is 0, throws Illegal Argument Exception.
        if (n <= 0) {
            throw new IllegalArgumentException();
        }

        //Declares a variable to hold the total, setting it to 1.
        long total = 1;

        //Loops while the number is greater than 1.
        while (n > 1) {
            //In each loop, multiplies the current total by the current number, then subtracts the number by one.
            total *= n--;
        }

        //Returns the total factorial once the loop is finished.
        return total;
    }
}
