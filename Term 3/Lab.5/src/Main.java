public class Main {

    static class WrongCountException extends Exception 
    {
        WrongCountException(String message) 
        {
            super(message);
        }
    }

    /*static class NotConvergentException extends Exception 
    {
        NotConvergentException(String message) 
        {
            super(message);
        }
    }*/

    static class NegativeEpsilonException extends Exception 
    {
        NegativeEpsilonException(String message) 
        {
            super(message);
        }
    }
    
    
    public static double calculateSum(String[] arguments) throws /*NotConvergentException,*/ NegativeEpsilonException
    {
    	
        double x = Double.parseDouble(arguments[0]);
      /*  if(Math.abs(x) >= 1) {
            throw new NotConvergentException("Error: the series is not convergent");
        }*/
        
        double epsilon = Double.parseDouble(arguments[1]);
        if(epsilon <= 0){
            throw new NegativeEpsilonException ("Error: epsilon must be non-negative");
        }
        
        double currentElement = Math.pow(x, 2)/6* Math.pow(4/3, 6);
        double sum = 0;
        for (int k = 1; Math.abs(currentElement) >= epsilon; k++)
        {
            sum += currentElement;
            currentElement *= (-1)/(2*k)/(2*k+1)*Math.pow(4/3, 4);
        }
        return sum;
    }

    public static void main(String[] arguments) {
        try {
            if (arguments.length != 2) {
                throw new WrongCountException("Error: wrong number of arguments.");
            }
        } catch (WrongCountException e) {
            System.out.println(e.getMessage());
            return;
        }
        try {
            System.out.println(calculateSum(arguments));
        }
        catch (NumberFormatException e) {
            System.out.println("Error: invalid value of argument.");
            return;
        }
        catch (NegativeEpsilonException e) {
            System.out.println(e.getMessage());
            return;
        }
        /*catch (NotConvergentException e) {
        System.out.println(e.getMessage());
             return;
        }*/
    }
    

}