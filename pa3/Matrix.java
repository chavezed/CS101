/*
Eduardo Chavez
echavez9@ucsc.edu
pa3
*/

class Matrix{
	private class Entry {
		int column;
		double value;
		
		// constructor
		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}
		
		public boolean equals(Object x) {
			boolean eq = false;
			Entry that;
			if(x instanceof Entry) {
				that = (Entry)x;
				eq = ((this.column==that.column) && (this.value==that.value));
			}
			return eq;
		}
		public String toString() {
			String toRet = "(" + column +
						", " + value + ") ";
			return toRet;
		}
	}
	private int matrixSize;
	private int nnzEntries;
	private List[] row;
	// Constructor
	
	// Matrix()
	// Makes a new n x n zero Matrix
	// pre: n >= 1
	Matrix(int n) {
		if(n<1) {
			throw new RuntimeException(
			"Error: Matrix() called for empty matrix\n");
		}
		row = new List[n+1]; 
		for(int i = 1; i <= n; i++) {
			row[i] = new List();
		}
		matrixSize = n; // size is still n
		nnzEntries = 0;
	}
	
	// Access Functions
	
	// getSize()
	// Returns n, the number of rows and columns of this Matrix
	int getSize() {
		return matrixSize;
	}
	
	// getNNZ()
	// Returns the number of non-zero entries in this Matrix
	int getNNZ() {
		return nnzEntries;
	}
	
	// equals()
	// Overrides Object's equals() method
	public boolean equals(Object x) {
		boolean eq = false;
		Matrix that;
		if(x instanceof Matrix) {
			that = (Matrix)x;
			eq = (this.matrixSize==that.matrixSize && this.nnzEntries==that.nnzEntries);
			if(eq) {
				for(int i = 1; i <= matrixSize && eq; i++) {
					eq = this.row[i].equals(that.row[i]);
				}
			}
		}
		return eq;
	}
	
	// Manipulation procedures
	
	// makeZero()
	// Sets this Matrix to the zero state
	void makeZero() {
		for(int i = 1; i <= matrixSize && i <= nnzEntries; i++) {
			row[i].clear();
		}
		nnzEntries = 0;
	}
	
	// copy()
	// Returns a new Matrix having the same entries as this Matrix
	Matrix copy() {
		Matrix toRet = new Matrix(matrixSize);
		for(int i = 1; i <= matrixSize; i++) {
			for(row[i].moveFront(); row[i].index() != -1; row[i].moveNext()){
				toRet.row[i].append((Entry)row[i].get());
			}
		}
		toRet.nnzEntries = nnzEntries;
		return toRet;
	}
	
	// changeEntry()
	// Changes ith row, jth colums of this Matrix to x
	// pre: 1 <= i <= getSize(), 1 <= j <= getSize()
	void changeEntry(int i, int j, double x) {
		if( !(i >= 1 && i <= matrixSize) ) {
			throw new RuntimeException(
			"Error: changeEntry() called on out of bound row indeces.\n");
		}
		if( !(j >= 1 && j <= matrixSize) ) { 
			throw new RuntimeException(
			"Error: changeEntry() called on out of bound column indeces.\n");
		}
		
		if(x==0) {
			Entry toDel;
			for(row[i].moveFront(); row[i].index() != -1; row[i].moveNext() ){
				toDel = (Entry)row[i].get();
				if(j == toDel.column) {
					row[i].delete();
					row[i].moveBack();
					nnzEntries--;
				}
			}
		}
		else { //x!=0
			if(row[i].length() < matrixSize) {
				Entry tempE;
				boolean found = false;
				for(row[i].moveFront(); row[i].index()!=-1; row[i].moveNext()) {
					tempE = (Entry)this.row[i].get();
					if(tempE.column == j) {
						row[i].insertBefore(new Entry(j,x));
						row[i].delete(); //will make cursor=-1
						row[i].moveBack();
						found = true;
					}
					else if(j < tempE.column) {
						row[i].insertBefore(new Entry(j,x));
						row[i].moveBack();
						found = true;
						nnzEntries++;
					}
					else{ // j > tempE.column
					
					}
				}
				if(!found) {
					row[i].append(new Entry(j,x));
					nnzEntries++;
				}
			}
		}
	}
	
	// scalarMult()
	// Returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x) {
		Matrix toRet = new Matrix(matrixSize);
		Entry modifyE;
		for(int i = 1; i <= matrixSize; i++) {
			for(row[i].moveFront(); row[i].index() != -1; row[i].moveNext()){
				modifyE = (Entry)row[i].get();
				toRet.changeEntry(i, modifyE.column, modifyE.value*x);
			}
		}
		return toRet;
	}
	
	// add()
	// Returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize() == M.getSize()
	Matrix add(Matrix M) {
		if(this.getSize() != M.getSize()){
			throw new RuntimeException(
				"Error: add() called on Matrices with uneven lengths.\n");
		}
		Matrix toRet = new Matrix(matrixSize);
		Matrix mCopy = M.copy();
		Entry E1;
		Entry E2;
		int j=1;
		double addR;
		for(int i = 1; i <= matrixSize; i++) {
			row[i].moveFront();
			mCopy.row[i].moveFront();
			j = 1;
			while(row[i].index()!=-1 && mCopy.row[i].index()!=-1) {
				E1 = (Entry)row[i].get();
				E2 = (Entry)mCopy.row[i].get();
				addR = addHelp(row[i], mCopy.row[i], E1, E2);
				toRet.changeEntry(i,j,addR);
				j++;
			}
			if(row[i].index() == -1 && mCopy.row[i].index() != -1) {
				while(mCopy.row[i].index()!= -1) {
					E2 = (Entry)mCopy.row[i].get();
					toRet.changeEntry(i,j,E2.value);
					j++;
					mCopy.row[i].moveNext();
				}
			}
			else if(mCopy.row[i].index() == -1 && row[i].index() != -1) {
				while(this.row[i].index() != -1) {
					E1 = (Entry)row[i].get();
					toRet.changeEntry(i,j,E1.value);
					j++;
					row[i].moveNext();
				}
			}
		}
		return toRet;
	}
	
	// sub()
	// Returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize() == M.getSize()
	Matrix sub(Matrix M) {
		if(this.getSize() != M.getSize()){
			throw new RuntimeException(
				"Error: add() called on Matrices with uneven lengths.\n");
		}
		Matrix toRet = new Matrix(this.getSize());
		Matrix mCopy = M.copy();
		Entry E1;
		Entry E2;
		int j = 1;
		double subR;
		for(int i = 1; i <= matrixSize; i++) {
			row[i].moveFront();
			mCopy.row[i].moveFront();
			j = 1;
			while(row[i].index()!=-1 && mCopy.row[i].index()!=-1) {
				E1 = (Entry)row[i].get();
				E2 = (Entry)mCopy.row[i].get();
				subR = subHelp(row[i], mCopy.row[i], E1, E2);
				toRet.changeEntry(i,j,subR);
				j++;
			}
			if(row[i].index() == -1 && mCopy.row[i].index() != -1) {
				while(mCopy.row[i].index()!= -1) {
					E2 = (Entry)mCopy.row[i].get();
					toRet.changeEntry(i,j,-1*E2.value);
					j++;
					mCopy.row[i].moveNext();
				}
			}
			else if(mCopy.row[i].index() == -1 && row[i].index() != -1) {
				while(this.row[i].index() != -1) {
					E1 = (Entry)row[i].get();
					toRet.changeEntry(i,j,E1.value);
					j++;
					row[i].moveNext();
				}
			}
		}
		return toRet;
	}
	
	// transpose()
	// Returns a new Matrix that is the transpose of this Matrix
	Matrix transpose() {
		Matrix toRet = new Matrix(this.getSize());
		Entry temp;
		for(int i = 1; i <= matrixSize; i++) {
			for(row[i].moveFront(); row[i].index()!=-1; row[i].moveNext()) {
				temp = (Entry)row[i].get();
				toRet.changeEntry(temp.column, i, temp.value);
			}
		}
		return toRet;
	}
	
	// mult()
	// Returns a new Matrix that is the product of this Matrix with M
	// pre: getSize() == M.getSize()
	Matrix mult(Matrix M) {
		if(this.getSize() != M.getSize()){
			throw new RuntimeException(
			"Error: mult() called on matrices of uneven size");
		}
		Matrix transM = new Matrix(M.getSize());
		transM = M.transpose();
		Matrix toRet = new Matrix(M.getSize());
		double dotVal;
		for(int i = 1; i <= matrixSize; i++) {
			for(int j = 1; j <= matrixSize; j++) {
				dotVal = dot(row[i], transM.row[j]);
				toRet.changeEntry(i,j,dotVal);
			}
		}
		return toRet;
	}
	
	// Other functions
	
	// toString()
	// Overrides Object's toString() method
	public String toString() {
		StringBuffer sb = new StringBuffer();
		Entry temp;
		for(int i = 1; i <= matrixSize; i++) {
			row[i].moveFront();
			if(row[i].index()!=-1){
				sb.append(i + ":" + row[i].toString() + "\n");
			}
		}
		return new String(sb);
	}
	
	// dot()
	// helper method for mult()
	// returns dot product
	private static double dot(List P, List Q) { //Q is column transversed to row
		P.moveFront();
		Q.moveFront();
		Entry pE;
		Entry qE;
		double toRet = 0;
		while(P.index()!=-1 && Q.index()!=-1) {
			pE = (Entry)P.get();
			qE = (Entry)Q.get();
			if(pE.column == qE.column) {
			toRet += (pE.value*qE.value);
			P.moveNext();
			Q.moveNext();
			}
			else if(pE.column < qE.column) {
				P.moveNext();
			}
			else {
				Q.moveNext();
			}
			
		}
		return toRet;		
	}
	
	// addHelp()
	// helper method for add()
	// returns the sum of entries
	private static double addHelp(List p, List q, Entry P, Entry Q) { //P+Q
		double toRet=0;
		if(P.column == Q.column) {
			toRet = P.value + Q.value;
			p.moveNext();
			q.moveNext();
		}
		else if(P.column < Q.column) {
			toRet = P.value;
			p.moveNext();
		}
		else {
			toRet = Q.value;
			q.moveNext();
		}
		return toRet;
	}
	
	// subHelp()
	// helper method for sub()
	// returns difference of entries
	private static double subHelp(List p, List q, Entry P, Entry Q) { //P-Q
		double toRet=0;
		if(P.column == Q.column) {
			toRet = P.value - Q.value;
			p.moveNext();
			q.moveNext();
		}
		else if(P.column < Q.column) {
			toRet = P.value;
			p.moveNext();
		}
		else{
			toRet = -1*Q.value;
			q.moveNext();
		}
		return toRet;
	}
}

// rewrite addHelp/subHelp so it takes three arguments
// List P, List Q, Boolean asFlag
// Where asFlag = 1 (add) and asFlag = 0 (sub)
/*
private static double addsubHelp(List P, List Q, boolean asFlag) {
	
	
	
}

*/
