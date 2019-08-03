/*
Eduardo Chavez
echavez9@ucsc.edu
pa3
*/

class List {
	private class Node{
		// Fields
		Object data; // for Entry from Matrix class
		Node next;
		Node previous;
		
		// Constructor
		Node(Object data){
			this.data = data;
			next = null;
			previous = null;
		}
		
		// toString(): overrides Object's toString() method
		public String toString(){
			return data.toString();
		}
		
		// equals(): overrides Object's equals() method
		public boolean equals(Object x){
			boolean eq = false;
			Node that;
			if(x instanceof Node){
				that = (Node) x;
				eq = (this.data==that.data); // 
			}
			return eq;
		}
	}
	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int index; // for cursor position
	
	// Constructor
	List() {
		front = back = cursor = null;
		length = 0;
		index = -1; // -1 since 0 corresponds to array[0] position
	}
	
	// Access functions --------------------------------------------------
	
	// isEmpty()
	// Returns true if this List is empty, false otherwise
	boolean isEmpty(){
		return length==0;
	}
	// Returns the number of elements in this List
	int length(){
		return length;
	}
	
	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index(){
		return index;
	}
	
	// Returns front element. Pre: length()>0
	Object front(){
		if(isEmpty() ){
			throw new RuntimeException(
			"List Error: front() called on empty List");
		}
		return front.data;
	}
	
	// Returns back element. Pre: length()>0
	Object back(){
		if(isEmpty()){
			throw new RuntimeException(
			"List Error: back() called on empty List");
		}
		return back.data;
	}
	
	// Returns cursor element. Pre: length()>0, index()>=0
	Object get(){
		if(isEmpty()){
			throw new RuntimeException(
			"List error: get() called on empty List");
		}
		if(index<0){
			throw new RuntimeException(
			"List error: get() called on out of bounds index");
		}
		return cursor.data;
	}
	
	// Returns true if this List and L are the same integer sequence.
	// The cursor is ignored in both lists.
	public boolean equals(Object L){
		boolean eq = false;
		List M;
		Node N,O;
		if(L instanceof List){
			M = (List) L;
			N = this.front;
			O = M.front;
			eq = (this.length==M.length);
			while(eq && N!=null){
				eq = N.equals(O);
				N = N.next;
				O = O.next;
			}
		}
		return eq;
	}
	
	// Manipulation Procedures -----------------------------------------
	
	// Resets this List to its original empty state.
	void clear(){
		front = back = cursor = null;
		length = 0;
		index = -1;
	}
	
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront(){
		if(!isEmpty()){
			cursor = front;
			index = 0;
		}
	}
	
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing
	void moveBack(){
		if(!isEmpty()){
			cursor = back;
			index = length - 1;
		}
	}
	
	// If cursor is defined and not at front, move cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing
	void movePrev(){
		if(cursor.previous!=null){
			cursor = cursor.previous;
			index--;
		}
		else if(cursor.previous == null){
			cursor = null;
			index = -1;
		}
		else {} //do nothing
	}
	
	// If cursor is defined and not at back, move cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined, does nothing
	void moveNext(){
		if(cursor.next!=null){
			cursor = cursor.next;
			index++;
		}
		else if(cursor.next == null){
			cursor = null;
			index = -1;
		}
		else{} //do nothing 
	}
	
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element
	void prepend(Object data){
		Node n = new Node(data);
		if(this.isEmpty()) {
			front = back = n;
		}
		else{
			front.previous = n;
			n.next = front;
			front = n;
		}
		length++;
	}
	
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element
	void append(Object data){
		Node n = new Node(data);
		if(this.isEmpty()){
			front = back = n;
		}
		else{
			n.previous = back;
			back.next = n;
			back = n;
		}
		length++;
	}

	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(Object data){
		if(this.isEmpty()) {
			throw new RuntimeException(
			"List Error: insertBefore() called on empty List");
		}
		if(index<0){
			throw new RuntimeException(
			"List Error: insertBefore called on out of bound cursor");
		}
		Node n = new Node(data);
		if(cursor == front){
			front.previous=n;
			n.next = front;
			front = n;
		}
		else{
			cursor.previous.next = n;
			n.previous = cursor.previous;
			n.next = cursor;
			cursor.previous = n;
		}
		index++;
		length++;
	}
	
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(Object data){
		if(this.isEmpty()){
			throw new RuntimeException(
			"List Error: insertAfter() called on empty List");
		}
		if(index<0){
			throw new RuntimeException(
			"List Error: insertAfter() called on out of bound cursor");
		}
		Node n = new Node(data);
		if(cursor == back){
			back.next = n;
			n.previous = back;
			back = n;
		}
		else{
			cursor.next.previous = n;
			n.next = cursor.next;
			n.previous = cursor;
			cursor.next = n;
		}
		length++;
	}
	
	// Deletes the front element. Pre: length() > 0
	void deleteFront(){
		if(this.isEmpty()){
			throw new RuntimeException(
			"List Error: deleteFront() called on empty List");
		}
		if(front == back) {
			front = back = cursor = null;
		}
		else {
		front.next.previous = null;
		front = front.next;
		}
		length--;
	}
	
	// Deletes the back element. Pre: length()>0
	void deleteBack(){
		if(this.isEmpty()){
			throw new RuntimeException(
			"List Error: deleteBack() called on empty List");
		}
		if(back == front) {
			back = front = cursor = null;
		}
		else {
		back.previous.next = null;
		back = back.previous;
		}
		length--;
	}
	
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index>=0
	void delete(){
		if(this.isEmpty()){
			throw new RuntimeException(
			"List Error: delete() called on empty List");
		}
		if(index<0){
			throw new RuntimeException(
			"List Error: delete() called on out of bound cursor");
		}
		if(cursor==front){
			deleteFront();
		}
		else if(cursor==back){
			deleteBack();
		}
		else{
			cursor.next.previous = cursor.previous;
			cursor.previous.next = cursor.next;
			length--;
		}
		cursor = null;
		index = -1;
	}
	
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new List is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy(){
		List L = new List();
		Node N = this.front;
		while(N!=null){
			L.append(N.data);
			N = N.next;
		}
	return L;	
	}
	
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space 
	// seperated sequence 
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = front;
		while(N!=null){
			sb.append(" ");
			sb.append(N.toString());
			N = N.next;
		}
		return new String(sb);
	}
	
} 