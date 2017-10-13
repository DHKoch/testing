#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(void);
int* readfile(int fileNum);
void do_offset(int* array, double offset,char* outFile);
void do_scale(int* array, double scale,char* outFile);
void copy(int* array,char* outFile);
double find_avg(int* array);
int find_max(int* array);
void save_stats(double average,int max, char* filename);
void save_center(double average, int* array,char* outFile);
int find_maxval(int filenum);
void save_normal(int* array,int maxval, char* outFile);

int main(int argc, char* argv[]){
	
	int i = 1;
	int fileNum = 0;
	double offset = 0;
	double scale = 0;
	char* outFile = malloc(sizeof(char)*32);
	char* outFile2 = malloc(sizeof(char)*32);
	int* array;
	int flag1 = 0;
	int statsflag = 0;
	int centerflag = 0;
	int normalflag = 0;
	
	for(i=1;i<argc;i++){
		//loops through all the command line arguments and checks for errors
		if((argv[i][0] == '-') && (argv[i][1] == 'n')){
			//filenum argument
			i++;
			if(argv[i] == NULL){
				error();
				return 0;
			}
			//converts filenum string to int
			fileNum = atoi(argv[i]);
			if(fileNum == 0){
				//checks for incorrect filenum
				error();
				return 0;
			}
			if(fileNum > 10){
				//checks for incorrect filenum
				error();
				return 0;
			}
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'o')){
			//offset vlaue argument 
			i++;
			if(argv[i] == NULL){
				error();
				return 0;
			}
			//converts string to double
			offset = strtod(argv[i],argv);
			if(offset == 0){
				error();
				return 0;
			}
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'S')){
			//do stats flag is set

			statsflag = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'C')){
			printf("here 4\n");
			//do center flag is set
			
			centerflag = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'N')){
			//do normal flag is set
			printf("here 3\n");

			normalflag = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 's')){
			//scale argument
			i++;
			if(argv[i] == NULL){
				//checks for nothing after -s
				error();
				return 0;
			}
			//converts string to double
			scale = strtod(argv[i],argv);
			if(scale == 0){
				//error checking
				error();
				return 0;
			}
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'r')){
			// sets new name for output file
			i++;
			if(argv[i] == NULL){
				//checks for incorretc argument
				error();
				return 0;
			}
			//copies new file name into variable and sets a flag
			strcpy(outFile2,argv[i]);
			flag1 = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'h')){
			//prints out how to use the program
			printf("Ther correct use of this program is as follows:\n");
			printf("./programName -h\nOr\n./progName -n 'file number' -o 'int' -s 'double' -r 'Output file name' -S -N -C\n");
			return 0;
		}
		
		else{
			//handles any other case than those stated above
			error();
			return 0;
		}
		
	}
	//printf("%d %f %f %s \n",fileNum,offset,scale,outFile);
	array = readfile(fileNum); //read in signal from input file
	/*for(i=0;i<6;i++){
		printf("%d\n",*(array+i));
	}*/
	
	if(flag1 == 1){
		//copies the original input into an output file with the
		//specified name for -r argument 
		copy(array,outFile2);
	}
	
	if(offset != 0){
		// sets output file name to offset
		sprintf(outFile,"Offset_data_%02d.txt",fileNum);
		do_offset(array,offset,outFile); 
	}
	
	if(scale != 0){
		sprintf(outFile,"Scaled_data_%02d.txt",fileNum);
		do_scale(array,scale,outFile);
	}
	
	if(statsflag == 1){
		//does stats operations
		sprintf(outFile,"Stats_data_%02d.txt",fileNum);
		double average = find_avg(array); //average is needed for the save stats file
		int max = find_max(array); //max is needed for the save stats file
		save_stats(average,max,outFile);
	}
	printf("here1\n");
	if(normalflag == 1){
		printf("here\n");
		//does normal operations
		sprintf(outFile,"Normal_data_%02d.txt",fileNum);
		int maxval = find_maxval(fileNum); //max val is needed to normalize
		printf("Maxval: %d\n",maxval);
		save_normal(array,maxval,outFile);
	}
	
	if(centerflag == 1){
		sprintf(outFile,"Center_data_%02d.txt",fileNum);
		double average1 = find_avg(array); // average is needed to center the data
		save_center(average1,array,outFile);
	}
	//free up memory
	free(array);
	free(outFile);
	free(outFile2);
	return 0;
}

void error(void){
	//prints out error and how to use the program 
	printf("Incorrect use of program!\nThe correct use is as follows:\n");
	printf("./programName -h\nOr\n./progName -n 'file number' -o 'int' -s 'double' -r 'Output file name' -S -N -C\n");
	
}

//reads data from file
int* readfile(int fileNum){
	int i = 1;
	char* filename = malloc(sizeof(char)*16);
	sprintf(filename,"Raw_data_%02d.txt",fileNum); //sets correct file name based on filenum
	//printf("%s\n",filename);
	FILE* fp = fopen(filename,"r");
	if(fp == NULL){
		//checks to see if file could be opened
		printf("file not opened\n");
	}
	
	int length = 0;
	int maxval = 0;
	//reads in the length of the fiel and max value
	fscanf(fp,"%d %d",&length,&maxval);
	//allocates memory for the array
	int* array = malloc(sizeof(int)*(length+1));
	//length is set as the first value in the array
	*array = length;
	for(i=1;i<=length;i++){
		//loops through and sets all other values in the array
		fscanf(fp,"%d",(array+i));
		//printf("%d\n",*(array+i));
	}
	fclose(fp); // close file
	return array;
}

void do_offset(int* array, double offset, char* outFile){
	int length = *array;
	FILE* fp = fopen(outFile,"w");
	if(fp == NULL){ //checks to see if file could be opened
		printf("file not opened\n");
	}
	int i = 1;
	fprintf(fp,"%d %.4f\n",length,offset); // first line in the file will have the length and offset value
	for(i=1;i<=length;i++){ //prints the value+offset to the file
		fprintf(fp,"%.4f\n",(double)(*(array+i) + offset));
		
	}
	fclose(fp); //closes file
}

void do_scale(int* array, double scale,char* outFile){
	int length = *array;
	FILE* fp = fopen(outFile,"w");
	if(fp == NULL){
		printf("file not opened\n");
	}
	int i = 1;
	fprintf(fp,"%d %.4f\n",length,scale); //first line in fiel will have length and scale
	for(i=1;i<=length;i++){ //prints the value*scale to the file
		fprintf(fp,"%.4f\n",(double)(*(array+i) * scale));
		
	}
	fclose(fp);
}

void copy(int* array, char* outFile){
	char* filename = malloc(sizeof(char)*40);
	sprintf(filename,"%s.txt",outFile);
	FILE* fp = fopen(filename,"w");
	int i = 1;
	for(i=1; i<=*array;i++){ //copies the input file data to the ouputfile
		fprintf(fp,"%d\n",*(array+i));
	}
	fclose(fp);
	free(filename);
}

double find_avg(int* array){
	int length = *array;
	int i = 1;
	double total = 0;
	double average = 0;
	for(i=1;i<=length;i++){ //totals all values in array
		total = total + *(array + i);
	}
	//divide total by length for average
	average = total/(double)length;
	return average;
}

int find_max(int* array){
	int length = *array;
	int i = 1;
	int max = *(array+1);
	//loops and checks each value against the previous
	for(i=1;i<=length;i++){
		if(*(array+i)>max){
			max = *(array+i);
		}
	}
	return max;
}

void save_stats(double average, int max, char* filename){
	FILE* fp = fopen(filename,"w");
	fprintf(fp,"%.4f %d",average,max); //prints the average and max to the stats file
	fclose(fp);
}

void save_center(double average, int* array, char* outFile){
	FILE* fp = fopen(outFile,"w");
	int length = *array;
	int i =1;
	for(i=1;i<=length;i++){ //center data so new average will be 0
		fprintf(fp,"%.4f\n",(double)*(array+i) - average); //prints new value to center file
	}
	fclose(fp);
}

int find_maxval(int filenum){ 
	// read the first line of the file to get the max value
	char* filename = malloc(sizeof(char)*16);
	sprintf(filename,"Raw_data_%02d.txt",filenum);
	FILE* fp = fopen(filename,"r");
	if(fp == NULL){
		printf("file not opened\n");
	}
	
	int length = 0;
	int maxval = 0;
	fscanf(fp,"%d %d",&length,&maxval);
	//returns max value
	return maxval;
}

void save_normal(int* array,int maxval,char* outFile){
	//every value will be between -1 and 1
	FILE* fp = fopen(outFile,"w");
	int length = *array;
	int i = 1;
	for(i=1;i<=length;i++){
		//prints new values into normal file
		fprintf(fp,"%.4f\n",(double)*(array+i)/(double)maxval);
	}
	fclose(fp);
}

