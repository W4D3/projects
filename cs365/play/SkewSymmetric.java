import java.io;
import java.util.Scanner;

class SkewSymmetric {

    public SkewSymmetric(String args[]) {
        
        Scanner console = new Scanner(System.in);
        Scanner lineTokenizer;
        int [][]array, index, i;

        i = 0;
        index = 0;
        array = new int[index][];
        
        for (i: args) {
            lineTokenizer = new Scanner(new BufferedReader(console.nextLine())); 
            while (lineTokenizer.hasNext()) { 
                if (lineTokenizer.hasNextInt()) { 
                    element = lineTokenizer.nextInt();
                    y[i][index] = new int[element];
                    index++;
                }
            }
        }

        for (i : array) {
            
    }


    public static void main(String args[]) {
        new SkewSymmetric();
    }
}
