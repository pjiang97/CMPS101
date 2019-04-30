//-----------------------------------------------------------------------------
//Peter Jiang
//pjiang1
//CMPS101 PA3
//  MatrixTest.java
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------

public class MatrixTest{
   public static void main(String[] args){
      int i, j;
      int size = 1000;
      Matrix A = new Matrix(size);
      Matrix B = new Matrix(size);

      for(i = 1; i<=size; i++)
        {
            for(j = 1; j<=size; j++)
            {
                A.changeEntry(i,j,size-j);
                B.changeEntry(i,j,j);
            }
        }

      //test matrices
      //
      A.changeEntry(1, 3, 1); B.changeEntry(0, 7, 4);
      A.changeEntry(2, 2, 4); B.changeEntry(2, 2, 2);
      A.changeEntry(1, 3, 0); B.changeEntry(1, 5, 2);
      A.changeEntry(6, 2, 7); B.changeEntry(1, 1, 3);
      A.changeEntry(2, 1, 5); B.changeEntry(1, 0, 0);
      A.changeEntry(6, 5, 3); B.changeEntry(7, 2, 7);


      System.out.println(A.getNNZ());
      System.out.println(A);

      System.out.println(B.getNNZ());
      System.out.println(B);

      Matrix C = A.scalarMult(1.5);
      System.out.println(C.getNNZ());
      System.out.println(C);

      Matrix D = A.add(A);
      System.out.println(D.getNNZ());
      System.out.println(D);

      Matrix E = A.sub(A);
      System.out.println(E.getNNZ());
      System.out.println(E);

      Matrix F = B.transpose();
      System.out.println(F.getNNZ());
      System.out.println(F);

      Matrix G = new Matrix(size);
      G.changeEntry(8, 3, 1);
      G.changeEntry(7, 1, 3);
      G.changeEntry(3, 0, 6);
      G.changeEntry(9, 5, 4);
      G.changeEntry(2, 1, 5);
      G.changeEntry(4, 2, 4);

      Matrix H = A.sub(B);
      System.out.println(H.getNNZ());
      System.out.println(H);

      Matrix I = B.sub(A);
      System.out.println(I.getNNZ());
      System.out.println(I);

      Matrix J = B.add(A);
      System.out.println(J.getNNZ());
      System.out.println(J);

      Matrix K = I.mult(J);
      System.out.println(K.getNNZ());
      System.out.println(K);

      Matrix L = C.mult(E);
      System.out.println(L.getNNZ());
      System.out.println(L);

      Matrix M = F.mult(H);
      System.out.println(M.getNNZ());
      System.out.println(M);

      Matrix N = M.scalarMult(3.0);
      System.out.println(N.getNNZ());
      System.out.println(N);

      Matrix O = J.copy();
      System.out.println(O.getNNZ());
      System.out.println(O);
      System.out.println(O.equals(A));
      System.out.println(O.equals(I));
      System.out.println(O.equals(D));
      System.out.println(O.equals(C));
      System.out.println(O.getNNZ());
      System.out.println(O);

      Matrix P = F.transpose();
      System.out.println(F.getNNZ());
      System.out.println(P);

      A.makeZero();
      System.out.println(G.getNNZ());
      System.out.println(G);
}
}
