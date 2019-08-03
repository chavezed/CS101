/*
Eduardo Chavez
echavez9@ucsc.edu
pa1
*/
import java.io.*;
import java.util.Scanner;
   
class Lex{
   public static void main(String[] args) throws IOException{
	   
	  if(args.length != 2){
		  System.err.println("Usage: Lex <input file> <output file>");
		  System.exit(1);
	  }
	  int lineCount = 0;
	  String line = "";
	  Scanner in = new Scanner(new File(args[0]));
	  PrintWriter out = new PrintWriter(new FileWriter(args[1]) );
	  while(in.hasNextLine() ){
		  lineCount++;
		  line+=in.nextLine() + " ";	 
	  }
	  String[] inputString = line.split("\\s+");
	  List indecesList = new List();
	  indecesList = indexSort(inputString,lineCount);
	  
	  for(indecesList.moveFront(); indecesList.index()!=-1; indecesList.moveNext() ){
		  out.println(inputString[indecesList.get() ]);
	  }
	  
	  out.println();
	  in.close();
	  out.close();
	}
	
	public static List indexSort(String[] strArr, int len){
		List toRet = new List();
		toRet.prepend(0);
		String s1 = "";
		String s2 = "";
		boolean done;
		for(int i = 1; i < len; i++){
			toRet.moveBack();
			s1 = strArr[i];
			s2 = strArr[toRet.get()];
			done = false;
			if(s1.compareTo(s2) <0 ){
				while(s1.compareTo(s2) <0 && !done) {
					toRet.movePrev();
					if(toRet.index() == -1){
						toRet.prepend(i);
						done = true;
					}
					else{
						s2 = strArr[toRet.get()];
						if(s1.compareTo(s2) > 0){
							toRet.insertAfter(i);
							done = true;
						}
					}
				}
			}
			else{
				toRet.append(i);
			}
	  }
		return toRet;
	}
}