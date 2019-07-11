#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int z=0;

int compare_string(char *first, char *second) 
{
   while (*first == *second) {
      if (*first == '\0' || *second == '\0')
         break;
         
      first++;
      second++;
   }
 
   if (*first == '\0' && *second == '\0')
      return 0;
   else
      return -1;
}

const char *readLine(FILE *file) {

    if (file == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }

    int maximumLineLength = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

    if (lineBuffer == NULL) {
        printf("Error allocating memory for line buffer.");
        exit(1);
    }

    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {
        if (count == maximumLineLength) {
            maximumLineLength += 128;
            lineBuffer = realloc(lineBuffer, maximumLineLength);
            if (lineBuffer == NULL) {
                printf("Error reallocating space for line buffer.");
                exit(1);
            }
        }
        lineBuffer[count] = ch;
        count++;

        ch = getc(file);
    }

    lineBuffer[count] = '\0';
    char line[count + 1];
    strncpy(line, lineBuffer, (count + 1));
    free(lineBuffer);
    const char *constLine = line;
    return constLine;
}


int main()
{
	FILE *ptr;
	char x[1000];
	int i,par,count=0;
	char ch;
	ptr = fopen("COOJA.testlog","r"); //COOJA is the test log where the data from the mote output from the simulator has to be copied.
    if ((ptr = fopen("COOJA.testlog", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
	const char *l = readLine(ptr);
	par=l[32];
	//printf("%c",par);
       while (!feof(ptr)) 
       {
       	 const char *line = readLine(ptr);
	 if(line[15]=='f')                //this filters out the lines carrying parrent id
	 {
		if(par!=line[32])	  //this is the exact index number that gives the parent ID
		{
			count++;
			par=line[32];     
   	 		//printf"%c\n", line[32]);
		}
	 }
       }
	
	printf("Parent Change count : %d\n",count-7);  //the negative 7 ensures that the first 56 lines of the mote output doesnt hamper the parent count.

//For more dynamic approach , instead of extracting the parent ID's from the 32nd index , the whole parent IP address can be compared as done below and results can be obtained !

	/*result = compare_string(x, y),i;
   
    if (result == 0)
       printf("The strings are same.\n");
    else
	{
		x=y;
		printf("%s",x);
	}
       //printf("The strings are different.\n");*/
	return 0;
}






