import java.io.*;
import java.util.Scanner;
   
class Lexcopy{
   public static void main(String[] args) throws IOException{
	   
	  if(args.length != 2){
		  System.err.println("Usage: Lex <input file> <output file>");
		  System.exit(1);
	  }
	  int lineCount = 0;
	  String line = "";
	  Scanner in = new Scanner(new File(args[0]));
	  PrintWriter out = new PrintWriter(new FileWriter(args[1]));
	  while(in.hasNextLine() ){
		  lineCount++;
		  line+=in.nextLine() + " ";
		  //inputString = line.split("\\s+");	// "\s" matches one whitespace
										    // while "\\s+" matches one or many whitespaces  
	  }
	  String[] inputString = line.split("\\s+");
	  List indecesList = new List();
	  indecesList.prepend(0);
	  String s1 = "";
	  String s2 = "";
	  boolean done;
	  for(int i = 1; i < lineCount; i++){
			indecesList.moveBack();
			s1 = inputString[i];
			s2 = inputString[indecesList.get()];
			done = false;
			if(s1.compareTo(s2)<0){
				while(s1.compareTo(s2)<0 && !done) {
					indecesList.movePrev();
					if(indecesList.index() == -1){
						indecesList.prepend(i);
						done = true;
					}
					else{
						s2 = inputString[indecesList.get()];
						if(s1.compareTo(s2)>0){
							indecesList.insertAfter(i);
							done = true;
						}
					}
				}
			}
			else{
				indecesList.append(i);
			}
	  }
	  for(indecesList.moveFront(); indecesList.index()!=-1; indecesList.moveNext()){
		  out.println(inputString[indecesList.get()]);
	  }
	  out.println();
	  in.close();
	  out.close();
	}
}