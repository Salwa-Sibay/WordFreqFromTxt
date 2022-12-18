#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//this is the definition of our structure that will store the words we're analyzing, how many times they each appears, and their frequencies
typedef struct{
	char wordName[51];
	int wordCount;
	float wordFrequency;
} word_t;

//function prototypes
int  analyzeFile(FILE *inp, word_t word[]); //this function will look through the file and count the appearance of the words
void averageSentenceLength(FILE *inp, int wordCount); //this counts how many sentences there are and then calculates average sentence length
void printWordFreq(word_t word[], int wordCount); //takes the count of words and frequencies and the struct, prints them

//main function woooo
int main(){
    setbuf(stdout, NULL);
	//the above line is because using scanf in eclipse with windows messes it up

    int wordCount = 0;
	char  in_name[80];
	FILE *inp;
	//return value from a function, names for the files, and the pointers to their locations

	//inputs
	printf("Enter name of file you want to find frequencies for->  ");
	for  (scanf("%s", in_name); (inp = fopen(in_name, "r")) == NULL; scanf("%s", in_name)) {
	    	  //uses the input as an initializer, checks the condition, and if the condition is met, will ask again
	          printf("Cannot open %s for input\n", in_name);
	          printf("Re enter file name> ");
      }

	//initializing the struct array for the words we're analyzing
	word_t word[5];
	strcpy(word[0].wordName, "and");
	word[0].wordCount = 0;
	strcpy(word[1].wordName, "by");
	word[1].wordCount = 0;
	strcpy(word[2].wordName, "from");
	word[2].wordCount = 0;
	strcpy(word[3].wordName, "the");
	word[3].wordCount = 0;
	strcpy(word[4].wordName, "to");
	word[4].wordCount = 0;

	//calling functions
	wordCount = analyzeFile(inp, word);
	printWordFreq(word, wordCount);
	inp = fopen(in_name, "r"); //this line is needed to be able to use the file again
	averageSentenceLength(inp, wordCount);

	//closes file
	fclose(inp);
	return 0;
}

//functions~~
int  analyzeFile(FILE *inp, word_t word[]){
	//first the memory for each line must be allocated
	char *textRead = malloc(10000);
	int count = 0; //this will keep track of total number of words
	//this while loop will read the file line by line until the end of file

	while (fscanf(inp, "%[^\n] ", textRead) != EOF){
		char *pch;
		pch = strtok (textRead, " ,.-;?!/:");
		//this while loop will take the tokenized words and compare them to the words we're analyzing
		//if they are the same, the word count for that word for increase by 1

		while (pch != NULL){
			count++; //this will increase for each tokenized word

			if(strcmp(pch, word[0].wordName)==0 || strcmp(pch, "And")==0)
				word[0].wordCount+=1;
			else if(strcmp(pch, word[1].wordName)==0 || strcmp(pch, "By")==0)
				word[1].wordCount+=1;
			else if(strcmp(pch, word[2].wordName)==0 || strcmp(pch, "From")==0)
				word[2].wordCount+=1;
			else if(strcmp(pch, word[3].wordName)==0 || strcmp(pch, "The")==0)
				word[3].wordCount+=1;
			else if(strcmp(pch, word[4].wordName)==0 || strcmp(pch, "To")==0)
				word[4].wordCount+=1;

			pch = strtok (NULL, " ,.-;?!/:");
		}
		pch = strtok (NULL, " ,.-;?!/:");
	}

		free(textRead);
		return count; //the total word count for the file will be returned by this function
}

void averageSentenceLength(FILE *inp, int wordCount){
	//initializing variables
	float sentenceAverage = 0.0;
	float sentenceCount = 0.0;
	char *textRead = malloc(10000);

	while (fscanf(inp, "%[^.!?]", textRead) != EOF){
		if (strlen(textRead)<=1) continue; //this is here to any spaces after the last sentence don't count as a sentence
		//reads up till the punctuation
		//counts how many sentences there are
		sentenceCount++;
		fscanf(inp, "%*c");

	}


	printf("\n\nThe total sentence count is %f. \nThe total word count is %d.", sentenceCount, wordCount);
	//this uses the values found previously for the word count and the sentence count and uses them to find the average length
	sentenceAverage = (float)wordCount/sentenceCount;
	free(textRead);

	printf("\nThe average sentence length is %.4f", sentenceAverage);
}

void printWordFreq(word_t word[], int wordCount){
	printf("\nThese are the word frequencies in alphabetical order: ");
	//this loop calculates the frequency of each word and then stores that value in the struct
	for(int i=0; i<5; i++){
		word[i].wordFrequency = ((float)word[i].wordCount/(float)wordCount)*1000;
		//then it prints the whole structure for each of the words
		printf("\n%s: Repeated %i amount of times and the frequency is %.4f",
			word[i].wordName,
			word[i].wordCount,
			word[i].wordFrequency);
	}
}
