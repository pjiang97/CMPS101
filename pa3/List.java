//Peter Jiang
//pjiang1
//CMPS101 pa3
//List.java
//List ADT for matrix

//import java.util.*;

public class List{
	//inner node class
	private class Node{

		Object data;
		Node prev;
		Node next;

		//node constructor
		Node(Object data){
			this.data = data;
			prev = null;
			next = null;
		}

		//overload constructor
		Node (Object data, Node prev, Node next){
			this.data = data;
			this.next = next;
			this.prev = prev;
		}


    //overrides Objects toString() method
		public String toString(){
			return data.toString();
		}

		public boolean equals(Object x){
			boolean equals =  false;
			Node other;
			if(x instanceof Node){
				other = (Node) x;
				equals = (this.data.equals(other.data));
			}
			return equals;
		}
	}

	//list data
	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int index;

	//Constructor
	public List(){
		index = -1;
		length = 0;
		front = null;
		back = null;
		cursor = null;
	}

	//access functions

	//returns the number of elements in this list
	int length(){
		return length;
	}

    //returns index of the cursor element
	int index(){
		return index;
	}

  //returns front element
  //pre: length() > 0
	Object front(){
		if(this.length() <= 0){
			throw new RuntimeException ("List Error: front() called on empty List");
		}
		return front.data;
	}

	//retreturns back element
	//pre: length() > 0
	Object back(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: back() called on an empty List");
		}
		return back.data;
	}

	//returns cursor element
	//pre: length()>0, index()>=0
	Object get(){
		if(this.length() == 0){
			throw new RuntimeException("List Error: get() called on empty List");
		}
		if(this.index() < 0){
			throw new RuntimeException("List Error: get() called on undefined index");
		}
		return cursor.data;
	}

	//returns true if this List and L are the same integer
	//sequence. The cursor is ignored in both lists.
	boolean equals(List L){
		boolean equal = true;
		Node X = this.front;
		Node Y = L.front;
		if( this.length == L.length){
			while( equal && X != null){
				equal = (X.data == Y.data);
				X = X.next;
				Y = Y.next;
			}
			return equal;
		}else{
			return false;
		}
	}

	//resets this list to its original empty state
	void clear(){
		cursor = front;
		if (cursor != null){
			while(cursor.next != null){
				Node temp = cursor;
				cursor = cursor.next;
				temp.next = null;
				temp.prev = null;
			}
			front = null;
			back = null;
			cursor = null;

			index = -1;
			length = 0;
		}
	}

	//if list is non empty, place cursor under the front element
	//otherwise do nothing
	void moveFront(){
		if(length > 0){
			cursor = front;
			index = 0;
		}
	}

	//if list is non empty, place cursor under back element
	//otherwise do nothing
	void moveBack(){
		if(length > 0){
			cursor = back;
			index = length-1; ///
		}
	}

	//If cursor is defined and not at front, moves cursor one step toward
	//front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing. f
	void movePrev(){
		if(cursor != null && index != 0){
			cursor = cursor.prev;
			index--;
		}
		else if(cursor != null && index == 0){
			cursor = null;
			index = -1;
		}
	}

	//If cursor is defined and not at back, moves cursor one step toward
	//back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing
	void moveNext(){
		if(cursor != null && index != length-1){
			cursor =  cursor.next;
			index++;
		}
		else if(cursor != null && index == length-1){
			cursor = null;
			index = -1;
		}
	}

	//Insert new element into this List. If List is non-empty,
	//insertion takes place before front element
	void prepend(Object data){
		Node temp = new Node(data, null, front);
		if(front == null)
			back = temp;
		else
			front.prev = temp;
		front = temp;
		length++;
	}

	//insert new element into this list. if list is non-empty
	//insertion takes placea fter back element.
	void append(Object data){
		Node temp = new Node(data, back, null);
		if(front == null)
			front =  temp;
		else
			back.next = temp;
		back = temp;
		length++;
	}

	//insert new element before cursor
	//pre: lenght()>0, index()>=0
	void insertBefore(Object data){
		if(index < 0)
			throw new RuntimeException("List error: insertBefore() called with an undefined index on List");
		if(length < 1)
			throw new RuntimeException("List error: insertBefore() called on empty list");

		Node temp = new Node(data, cursor.prev, cursor);
		if(cursor.prev != null)
			cursor.prev.next = temp;
		else
			front = temp;
		cursor.prev = temp;
		length++;
	}

	//inserts new element after cursor.
	//pre:length()>0, index()>0
	void insertAfter(Object data){
		if(index < 0)
			throw new RuntimeException("List errror: insertAfter() called with an undefined index");
		if(length < 1)
			throw new RuntimeException("List error: insertAfter() called on empty list");
		Node temp = new Node(data, cursor, cursor.next);

		if(cursor.next != null)
			cursor.next.prev = temp;
		else
			back = temp;
		cursor.next = temp;
		length++;
	}

	//deletes the front element.
	//pre: length()>0
	void deleteFront(){
		if(length < 1)
			throw new RuntimeException("List error: deleteFront() called on an empty List");
		if(cursor == front){
			cursor = null;
			index = -1;
		}
		front = front.next;
		front.prev = null;
		length--;
	}

	//deletes the back element,
	//pre:length()>0
	void deleteBack(){
		if(length < 1)
			throw new RuntimeException("List error: deleteBack() called on an empty List");
		if(cursor == back){
			cursor = null;
			index = -1;
		}
		back = back.prev;
		back.next = null;
		length--;
	}

	//delete cursor element, making cursor undefined
	//pre: length()>0 index()>=0
	void delete(){
		if(length > 0 && index >= 0){
			if(cursor == front)
				deleteFront();
			else if(cursor == back)
				deleteBack();
			else{
				cursor.prev.next = cursor.next;
				cursor.next.prev = cursor.prev;
				cursor = null;
				index = -1;
				length--;
			}
		}
	}

	//other methods------------------

	// Overrides Object's toString method. Returns a String
	//representation of this List consisting of a space
	//separated sequence of integers, with front on left.
	public String toString(){
		String str = "";
        for (Node N = front; N != null; N = N.next) {
            str += N.toString() + " ";
        }
        return str;
  }
}
