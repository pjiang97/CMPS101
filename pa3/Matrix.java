/*Peter Jiang
pjiang1
CS101 PA3
Matrix.java
Array of List objects*/

public class Matrix{

	private class Entry{
		//fields
		int column;
		double value;

		//constructor
		Entry(int column, double value){
			this.column = column;
			this.value = value;
		}

		public boolean equals(Object x){
			boolean eq = false;
			Entry other;
			if(x instanceof Entry){
				other = (Entry) x;
				eq = (this.column == other.column && this.value == other.value);
			}
			return eq;
		}

		//toString() overrides default
		public String toString(){
			return "(" +column+ ", " +value+ ")";
		}
	}

	List[] matrix;

	// Makes a new n x n zero Matrix. pre: n>=1
  //Matrix constructor
	Matrix(int n){
		if(n < 1)
			throw new RuntimeException("Matrix error: Matrix() called with invalid size");
		matrix = new List[n + 1];
		for(int i = 1; i < n+1; i++){
				matrix[i] = new List();
		}
	}

	//Returns n, the number of matrixs and columns of this Matrix
	int getSize(){
		return matrix.length-1;
	}

	//Returns the number of non-zero entries in this Matrix
	int getNNZ() {
		int counter = 0;
		for(int i = 1; i<= getSize(); i++){
			counter = counter + matrix[i].length();
		}
		return counter;
	}

	// overrides Object's equals() method
	public boolean equals(Object x){
		Matrix M;
		if(x instanceof Matrix){
			M = (Matrix) x;
			if(getSize() != M.getSize())
				return false;
			for(int i = 1; i <= getSize(); ++i){
				if(!(matrix[i].equals(M.matrix[i])))
					return false;
			}
		}
		return true;
	}

	// sets this Matrix to the zero state
	void makeZero(){
		for(int i = 0; i < getSize(); i++){
			matrix[i] = new List();
		}
	}

	// returns a new Matrix having the same entries as this Matrix
	Matrix copy(){
		Matrix m = new Matrix(getSize());
		if(m.getSize() > 0){
			for(int i = 1; i <= getSize(); i++){
				if(matrix[i].length() == 0){
					continue;
				}
				matrix[i].moveFront();
				while(matrix[i].index() >= 0){
					Entry e = (Entry) matrix[i].get();
					m.changeEntry(i, e.column, e.value);
					matrix[i].moveNext();
				}
			}
		}
		return m;
	}

	// changes ith matrix, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x){
		if(!((i >= 1 && i <= getSize()) && (j >= 1 && j <= getSize()))){
				throw new RuntimeException("Matrix Error: calling changeEntry() with invalid parameters");
		}
	  boolean b = false;
		matrix[i].moveFront();
		while(matrix[i].index() >= 0){
			Entry entry = (Entry) matrix[i].get();
			b = (entry.column == j ? true : false);
			if(b){
				if(x == 0.0){
					matrix[i].delete();
					return;
				}else{
					entry.value = x;
					return;
				}
			}
			matrix[i].moveNext();
		}

		if(!b && x != 0.0){
			matrix[i].moveFront();
			if(matrix[i].index() == -1){
				matrix[i].append(new Entry(j, x));
				return;
			}else{
				while(matrix[i].index() > -1 && ((Entry)matrix[i].get()).column < j){
					matrix[i].moveNext();
				}
				if(matrix[i].index() > -1){
					matrix[i].insertBefore(new Entry(j, x));
					return;
				}else{
					matrix[i].append(new Entry(j,x));
					return;
				}
			}
		}
	}

	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x){
		Matrix scal = this.copy();
		for(int i = 1; i <= scal.getSize(); i++){
			if(matrix[i].length() == 0){
				continue;
			}
			scal.matrix[i].moveFront();
			while(scal.matrix[i].index() >= 0){
				Entry entry = (Entry) scal.matrix[i].get();
				scal.changeEntry(i, entry.column, (x * entry.value));
				scal.matrix[i].moveNext();
			}
		}
		return scal;
	}

	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M){
			if(getSize() != M.getSize())
				throw new RuntimeException("Matrix Error: add() called on Matrices with different sizes");
			if(M == this)
				return this.copy().scalarMult(2);
			Matrix sumMatrix = new Matrix(getSize());
			for(int i = 1; i <= getSize(); ++i){
				sumMatrix.matrix[i] = addHelp(matrix[i], M.matrix[i], true);
			}
			return sumMatrix;
		}

	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M){
		if(this.getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: sub() called on diffrent size matricies");
      }
      Matrix subMatrix = M.copy();
      subMatrix = subMatrix.scalarMult(-1);
      Matrix sub = this.add(subMatrix);
      return sub;
   }

	 // returns a new Matrix that is the transpose of this Matrix
	Matrix transpose(){
		Matrix transMatrix = new Matrix(getSize());
		for(int i = 1; i <= getSize(); i++){
			if(matrix[i].length() == 0){
				continue;
			}
			matrix[i].moveFront();
			while(matrix[i].index() != -1){
				transMatrix.changeEntry(((Entry)matrix[i].get()).column, i, ((Entry)matrix[i].get()).value);
				matrix[i].moveNext();
			}
		}
		return transMatrix;
	}

	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix mult(Matrix M){
		if(getSize() != M.getSize())
			throw new RuntimeException("Matrix Error: mult() called on two matrices with different sizes");
		Matrix mulMatrix = new Matrix(getSize());
		Matrix transMatrix = M.transpose();

		for(int i = 1; i <= getSize(); i++){
			if(matrix[i].length() == 0){
				continue;
			}
			for(int j = 1; j<= getSize(); ++j){
				if(transMatrix.matrix[j].length() == 0){
					continue;
				}
			mulMatrix.changeEntry(i, j, dot(matrix[i], transMatrix.matrix[j]));
		    }
		}
		return mulMatrix;
	}

	//other functions
	//overrides Object's toString() method
	public String toString(){
		String out = "";
		for(int i = 1; i <= getSize(); i++){
			if(matrix[i].length() > 0)
				out = out + (i + ": " + matrix[i] + "\n");
		}
		return out;
	}

	// helper method that calculates the dot product of the two lists
	private static double dot(List P, List Q){
		double mult = 0.0;
		if(P.length() != 0){
			P.moveFront();
		}
		if(Q.length() != 0){
			Q.moveFront();
		}
		while(P.index() >= 0 && Q.index() >= 0){
			Entry p = (Entry) P.get();
			Entry q = (Entry) Q.get();
			if(p.column < q.column){
				P.moveNext();
			}else if(p.column > q.column){
				Q.moveNext();
			}else if(p.column == q.column){
				mult = mult + (p.value * q.value);
				P.moveNext();
				Q.moveNext();
			}
		}
		return mult;
	}

	//helper for add for two lists.
	private List addHelp(List N, List M, boolean add){
		List L = new List();
		N.moveFront();
		M.moveFront();
		while(N.index() >= 0 || M.index() >= 0){
			if(N.index() >= 0 && M.index() >= 0){
				Entry a = (Entry) N.get();
				Entry b = (Entry) M.get();
				if(a.column > b.column){
					L.append(new Entry(b.column, (add ? 1.0 : -1.0) * b.value));
					M.moveNext();
				}else if(a.column < b.column){
					L.append(new Entry(a.column, a.value));
					N.moveNext();
				}else if(a.column == b.column){
					if((add && a.value + b.value !=0) || (!add && a.value - b.value != 0))
						L.append(new Entry(a.column, (add ? a.value + b.value : a.value - b.value)));
					N.moveNext();
					M.moveNext();
				}
			}else if(N.index() >= 0){
				Entry a = (Entry) N.get();
				L.append(new Entry(a.column, a.value));
				N.moveNext();
			}else{
				Entry b = (Entry) M.get();
				L.append(new Entry(b.column, (add ? 1.0 : -1.0) * b.value));
				M.moveNext();
			}
		}
		return L;
	}
}
