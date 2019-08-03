/*
Eduardo Chavez
echavez9@ucsc.edu
pa3
*/

class MatrixTest {
	public static void main(String[] args) {
		int i, j, n=15;
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);
				
		for(i = 1; i <= 5; i++) {
			for(j = 1; j <= 5; j++) {
				A.changeEntry(i,j,i);
				B.changeEntry(j,i,j+i);
			}	
		}
		
		System.out.println("A has " + A.getNNZ() + " non-zero entries: ");
		System.out.println(A);
		
		System.out.println("B has " + B.getNNZ() + " non-zero entries: ");
		System.out.println(B);
		
		Matrix C = A.scalarMult(1.5);
		System.out.println("(1.5)*A = ");
		System.out.println(C);
		
		Matrix D = A.add(B);
		System.out.println("A+B = ");
		System.out.println(D);
		
		Matrix E = A.add(A);
		System.out.println("A+A = ");
		System.out.println(E);
		
		Matrix F = B.sub(A);
		System.out.println("B-A = ");
		System.out.println(F);
		
		Matrix G = A.sub(A);
		System.out.println("A-A = ");
		System.out.println(G);
		
		Matrix H = A.transpose();
		System.out.println("Transpose(A) = ");
		System.out.println(H);
		
		Matrix I = A.mult(B);
		System.out.println("A*B = ");
		System.out.println(I);
		
		Matrix J = B.mult(B);
		System.out.println("B*B = ");
		System.out.println(J);
		
		Matrix K = A.copy();
		System.out.println("K = A.copy()");
		System.out.println("K has " + K.getNNZ() + " non-zero entries: ");
		System.out.println(K);
		System.out.println("Does K = A: " + K.equals(A));
		
		A.changeEntry(3,5,0);
		A.changeEntry(3,6,0);
		A.changeEntry(2,4,0);
		A.changeEntry(10,3,-99);
		
		
		System.out.println("Checking if modifying A will affect K");
		System.out.println("K has " + K.getNNZ() + " non-zero entries: ");
		System.out.println(K);
		System.out.println("A has " + A.getNNZ() + " non-zero entries: ");
		System.out.println(A);
		System.out.println("Does K = A: " + K.equals(A));
		
		System.out.println("Making A zero Matrix");
		A.makeZero();
		System.out.println("A has " + A.getNNZ() + " non-zero entries: ");
		System.out.println(A);
		
	}
}