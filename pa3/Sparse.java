/* Peter Jiang
pjiang1
CMPS101 PA3
Sparse.java
Performs Matrix operations
*/

import java.io.*;
import java.util.Scanner;

public class Sparse{
	public static void main( String[] args) throws IOException{

		if (args.length < 2){
			System.err.println("Usage: sparse infile outfile");
			System.exit(1);
		}

		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = null;
		String[] entry = null;
		String line = null;

		int aLine, bLine;
		int i, n, lineNum = 0;

		line = in.nextLine() + " ";
		entry = line.split("\\s+");

		Matrix A = new Matrix(Integer.parseInt(entry[0]) );
		Matrix B = new Matrix(Integer.parseInt(entry[0]) );

		aLine = Integer.parseInt(entry[1]) + 2;
		bLine = Integer.parseInt(entry[2]) + aLine + 1;

		in = new Scanner(new File(args[0]) );
		out = new PrintWriter( new FileWriter(args[1]) );

		while(in.hasNextLine() ){
			lineNum++;
			line = in.nextLine() + " ";
			entry = line.split("\\s+");

			if (lineNum > 2 && lineNum <= aLine){
				A.changeEntry(Integer.parseInt(entry[0]), Integer.parseInt(entry[1]), Double.parseDouble(entry[2]) );
			}
			if (lineNum > (aLine + 1) && lineNum <= bLine){
				B.changeEntry( Integer.parseInt(entry[0]), Integer.parseInt(entry[1]), Double.parseDouble(entry[2]) );
			}
		}

		//print out the operations
		System.out.println("A has " + A.getNNZ() + " non-zero entries:");
		System.out.println(A);

		System.out.println("B has " + B.getNNZ() + " non-zero entries:");
		System.out.println(B);

		System.out.println("(1.5)*A =");
		System.out.println(A.scalarMult(1.5));

		System.out.println("A+B =");
		System.out.println(A.add(B));

		System.out.println("A+A =");
		System.out.println(A.add(A));

		System.out.println("B-A =");
		System.out.println(B.sub(A));

		System.out.println("A-A =");
		System.out.println(A.sub(A));

		System.out.println("Transpose(A) =");
		System.out.println(A.transpose());

		System.out.println("A*B =");
		System.out.println(A.mult(B));

		System.out.println("B*B =");
		System.out.println(B.mult(B));

	}
}
