/*
Eduardo Chavez
echavez9@ucsc.edu
pa3
*/

import java.io.*;
import java.util.Scanner;

class Sparse{
	public static void main(String[] args) throws IOException {
		
		if(args.length != 2) {
			System.err.println("Usage: Sparse <input file> <output file>");
			System.exit(1);
		}
		String line = "";
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		if(in.hasNextLine()) {
			line+=in.nextLine() + " ";
		}
		String[] matrixInfo = line.split("\\s+");
		int matrixSize = Integer.parseInt(matrixInfo[0]);
		int nnzE1 = Integer.parseInt(matrixInfo[1]);
		int nnzE2 = Integer.parseInt(matrixInfo[2]);
		Matrix A = new Matrix(matrixSize);
		Matrix B = new Matrix(matrixSize);
		
		String[] matrixEntries;
		int row;
		int col;
		double val;
		
		in.nextLine();
		for(int i = 0; i < nnzE1 && in.hasNextLine(); i++) {
			line = "";
			line+=in.nextLine() + " ";
			matrixEntries = line.split("\\s+");
			row = Integer.parseInt(matrixEntries[0]);
			col = Integer.parseInt(matrixEntries[1]);
			val = Double.parseDouble(matrixEntries[2]);
			A.changeEntry(row,col,val);
		}
	
		in.nextLine();
		for(int i = 0; i < nnzE2 && in.hasNextLine(); i++) {
			line = "";
			line+=in.nextLine() + " ";
			matrixEntries = line.split("\\s+");
			row = Integer.parseInt(matrixEntries[0]);
			col = Integer.parseInt(matrixEntries[1]);
			val = Double.parseDouble(matrixEntries[2]);
			B.changeEntry(row,col,val);
		}
		
		out.println("A has " + A.getNNZ() + " non-zero entries: ");
		out.println(A);
		
		out.println("B has " + B.getNNZ() + " non-zero entries: ");
		out.println(B);
		
		Matrix C = A.scalarMult(1.5);
		out.println("(1.5)*A = ");
		out.println(C);
		
		Matrix D = A.add(B);
		out.println("A+B = ");
		out.println(D);
		
		Matrix E = A.add(A);
		out.println("A+A = ");
		out.println(E);
		
		Matrix F = B.sub(A);
		out.println("B-A = ");
		out.println(F);
		
		Matrix G = A.sub(A);
		out.println("A-A = ");
		out.println(G);
		
		Matrix H = A.transpose();
		out.println("Transpose(A) = ");
		out.println(H);
		
		Matrix I = A.mult(B);
		out.println("A*B = ");
		out.println(I);
		
		Matrix J = B.mult(B);
		out.println("B*B = ");
		out.println(J);
		
		in.close();
		out.close();

}




























}