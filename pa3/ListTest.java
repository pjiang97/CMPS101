//Peter pjiang
//pjiang1
//pa3 cmps101
//A prgoram that tests the List ADT

public class ListTest{
   public static void main(String[] args){
      List A = new List();
      List B = new List();

      for(int i=1; i<=30; i++){
         A.append(i);
         B.prepend(i);
      }

      System.out.println(A);
      System.out.println(B);

      A.moveBack();
		    for(int i = 0; i < 15; i++){
			       A.movePrev();
		    }
		  A.delete();

      A.prepend(230);
		  B.append(20);
		  B.append(453);

      A.moveFront();
      for(int i=0; i<6; i++) A.moveNext();
      A.insertBefore(-1);
      for(int i=0; i<10; i++) A.moveNext();
      A.insertAfter(-5);
      for(int i=0; i<4; i++) A.movePrev();
      A.delete();
      System.out.println(A);
      System.out.println(A.length());
      A.clear();
      System.out.println(A.length());
   }
}
