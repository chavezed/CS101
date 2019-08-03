/*
Eduardo Chavez
echavez9@ucsc.edu
pa3
*/

class ListTest {
	public static void main(String[] args) {
		List A = new List();
		List B = new List();
		
		Integer a1 = new Integer(3);
		Integer a2 = new Integer(6);
		Integer a3 = new Integer(9);
		Integer a4 = new Integer(12);
		
		A.append(a1);
		A.append(a2);
		A.append(a3);
		A.append(a4);
		
		B.prepend(a1);
		B.prepend(a2);
		B.prepend(a3);
		B.prepend(a4);
		
		System.out.println("Size of A: " + A.length());
		System.out.println(A);
		
		System.out.println("Size of B: " + B.length());
		System.out.println(B);
		
		System.out.println("Forward print of A");
		for(A.moveFront(); A.index()>=0; A.moveNext()){
			System.out.println(A.get() + " ");
		}
		System.out.println();
		
		System.out.println("Reverse print of B");
		for(B.moveBack(); B.index()>=0; B.movePrev()){
			System.out.println(B.get() + " ");
		}
		System.out.println();
		
		System.out.println("C = A.copy()");
		List C = A.copy();
		System.out.println("Does A = C : " + A.equals(C));
		System.out.println("Does A = B : " + A.equals(B));
		System.out.println("Does C = C : " + C.equals(C));
		
		System.out.println("Modify C and check it doesn't affect A");
		C.moveFront();
		C.moveNext();
		C.insertBefore(new Integer(99));
		C.moveNext();
		C.insertAfter(new Integer(33));
		C.delete();
		
		System.out.println("Does A = C : " + A.equals(C));
		System.out.println("Length of A: " + A.length());
		System.out.println(A);
		System.out.println("Length of C: " + C.length());
		System.out.println(C);
		
		System.out.println("Delete all elements of B (forward delete)");
		int bLen = B.length();
		for(int i = 0; i < bLen; i++) {
			B.deleteFront();
		}
		System.out.println("Length of B: " + B.length());
		System.out.println(B);
		
		System.out.println("Delete all elements of C (reverse delete)");
		int cLen = C.length();
		for(int i = 0; i < cLen; i++) {
			C.deleteBack();
		}
		System.out.println("Length of C: " + C.length());
		System.out.println(C);
		
		System.out.println("Delete all elements of A (using clear)");
		A.clear();
		System.out.println("Length of A: " + A.length());
		System.out.println(A);
		
		// Using String Objects ----------------------------------------------
		
		List D = new List();
		List E = new List();
		
		String b1 = new String("one");
		String b2 = new String("two");
		String b3 = new String("three");
		String b4 = new String("four");
		
		D.append(b1);
		D.append(b2);
		D.append(b3);
		D.append(b4);
		
		E.prepend(b1);
		E.prepend(b2);
		E.prepend(b3);
		E.prepend(b4);
		
		System.out.println("Size of D: " + D.length());
		System.out.println(D);
		
		System.out.println("Size of E: " + E.length());
		System.out.println(E);
		
		System.out.println("Forward print of D");
		for(D.moveFront(); D.index()>=0; D.moveNext()){
			System.out.println(D.get() + " ");
		}
		System.out.println();
		
		System.out.println("Reverse print of E");
		for(E.moveBack(); E.index()>=0; E.movePrev()){
			System.out.println(E.get() + " ");
		}
		System.out.println();
		
		System.out.println("F = D.copy()");
		List F = D.copy();
		System.out.println("Does D = F : " + D.equals(F));
		System.out.println("Does D = E : " + D.equals(E));
		System.out.println("Does F = F : " + F.equals(F));
		
		System.out.println("Modify F and check it doesn't affect D");
		F.moveFront();
		F.moveNext();
		F.insertBefore(new String("eleven"));
		F.moveNext();
		F.insertAfter(new String("twenty"));
		F.delete();
		
		System.out.println("Does D = F: " + D.equals(F));
		System.out.println("Length of D: " + D.length());
		System.out.println(D);
		System.out.println("Length of F: " + F.length());
		System.out.println(F);
		
		System.out.println("Delete all elements of E (forward delete)");
		int eLen = E.length();
		for(int i = 0; i < eLen; i++) {
			E.deleteFront();
		}
		System.out.println("Length of E: " + E.length());
		System.out.println(E);
		
		System.out.println("Delete all elements of F (reverse delete)");
		int fLen = F.length();
		for(int i = 0; i < fLen; i++) {
			F.deleteBack();
		}
		System.out.println("Length of F: " + F.length());
		System.out.println(F);
		
		System.out.println("Delete all elements of D (using clear)");
		D.clear();
		System.out.println("Length of D: " + D.length());
		System.out.println(A);
		
		// Using Double Objects ----------------------------------------------
		
		List G = new List();
		List H = new List();
		
		Double c1 = new Double(1.2);
		Double c2 = new Double(2.3);
		Double c3 = new Double(3.4);
		Double c4 = new Double(4.5);
		
		G.append(c1);
		G.append(c2);
		G.append(c3);
		G.append(c4);
		
		H.prepend(c1);
		H.prepend(c2);
		H.prepend(c3);
		H.prepend(c4);
		
		System.out.println("Size of G: " + G.length());
		System.out.println(G);
		
		System.out.println("Size of H: " + H.length());
		System.out.println(H);
		
		System.out.println("Forward print of G");
		for(G.moveFront(); G.index()>=0; G.moveNext()){
			System.out.println(G.get() + " ");
		}
		System.out.println();
		
		System.out.println("Reverse print of H");
		for(H.moveBack(); H.index()>=0; H.movePrev()){
			System.out.println(H.get() + " ");
		}
		System.out.println();
		
		System.out.println("I = G.copy()");
		List I = G.copy();
		System.out.println("Does G = I : " + G.equals(I));
		System.out.println("Does G = H : " + G.equals(H));
		System.out.println("Does I = I : " + I.equals(I));
		
		
		System.out.println("Modify I and check it doesn't affect G");
		I.moveFront();
		I.moveNext();
		I.insertBefore(new Double(4.432));
		I.moveNext();
		I.insertAfter(new Double(8.768));
		I.delete();
		
		System.out.println("Does G = I: " + G.equals(I));
		System.out.println("Length of G: " + G.length());
		System.out.println(G);
		System.out.println("Length of I: " + I.length());
		System.out.println(I);
		
		System.out.println("Delete all elements of I (forward delete)");
		int iLen = I.length();
		for(int i = 0; i < iLen; i++) {
			I.deleteFront();
		}
		System.out.println("Length of I: " + I.length());
		System.out.println(I);
		
		System.out.println("Delete all elements of H (reverse delete)");
		int hLen = H.length();
		for(int i = 0; i < hLen; i++) {
			H.deleteBack();
		}
		System.out.println("Length of H: " + H.length());
		System.out.println(H);
		
		System.out.println("Delete all elements of G (using clear)");
		G.clear();
		System.out.println("Length of G: " + G.length());
		System.out.println(G);
		
		
	}
}