//-------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa2
//-------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"
//-------------------------------------------------------------------------
#define MAX_LEN 160
//-------------------------------------------------------------------------

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	char** inArr = NULL;
	char line[MAX_LEN];
	int lineCount = 0;
	int lineLength = 0;
	int i;
	
	// check num of args
	if(argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// input/output file validation
	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to open file %s for reading.\n",argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to open file %s for reading.\n",argv[2]);
		exit(1);
	}
	
	// lineCount number of lines in input file
	while(fgets(line, MAX_LEN, in) != NULL){
		lineCount++;
	}
	
	// move to beginning of file
	rewind(in);
	inArr = malloc( lineCount * sizeof(char *));
	
	for(i = 0; i < lineCount; i++){
		fgets(line, MAX_LEN, in);
		lineLength = strlen(line);
		line[lineLength - 1] = '\0'; 
		lineLength--; 
		inArr[i] = malloc(lineLength + 1); 
		strcpy(inArr[i], line);
	}
	
	List indexList = newList();
	char* s1;
	char* s2;
	prepend(indexList,0);
	int done;
	
	// sort List in Lexicographical order
	for(i = 1; i < lineCount; i++){
		moveBack(indexList);
		s1 = inArr[i];
		s2 = inArr[get(indexList)];
		done = 0;
		if(strcmp(s1,s2) < 0){
			while(strcmp(s1,s2) < 0 && !done){
				movePrev(indexList);
				if(index(indexList) == -1){
					prepend(indexList, i);
					done = 1;
				}
				else{
					s2 = inArr[get(indexList)];
					if(strcmp(s1,s2) > 0){
						insertAfter(indexList, i);
						done = 1;
					}
				}
			}
		}
		else{
			append(indexList, i);
		}
	}
	
	// print Lexicographically sorted List
	for(moveFront(indexList); index(indexList) != -1; moveNext(indexList)) {
		fprintf(out,"%s\n", inArr[get(indexList)]);
	}
	
	// clear memory
	for(i = 0; i < lineCount; i++){
		free(inArr[i]);
	}
	free(inArr);
	inArr = NULL;
	
	freeList(&indexList);
	fclose(in);
	fclose(out);
	
	return(0);
}