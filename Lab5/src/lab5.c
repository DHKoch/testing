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
		
		if((argv[i][0] == '-') && (argv[i][1] == 'n')){
			i++;
			if(argv[i] == NULL){
				error();
				return 0;
			}
			fileNum = atoi(argv[i]);
			if(fileNum == 0){
				error();
				return 0;
			}
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'o')){
			i++;
			if(argv[i] == NULL){
				error();
				return 0;
			}
			offset = strtod(argv[i],argv);
			if(offset == 0){
				error();
				return 0;
			}
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'S')){
			i++;
			statsflag = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'C')){
			i++;
			centerflag = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'N')){
			i++;
			normalflag = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 's')){
			i++;
			if(argv[i] == NULL){
				error();
				return 0;
			}
			scale = strtod(argv[i],argv);
			if(scale == 0){
				error();
				return 0;
			}
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'r')){
			i++;
			if(argv[i] == NULL){
				error();
				return 0;
			}
			strcpy(outFile2,argv[i]);
			flag1 = 1;
		}
		
		else if((argv[i][0] == '-') && (argv[i][1] == 'h')){
			printf("Ther correct use of this program is as follows:\n");
			printf("./programName -h\nOr\n./progName -n 'file number' -o 'int' -s 'double' -r 'Output file name'\n");
			return 0;
		}
		
		else{
			error();
			return 0;
		}
		
	}
	printf("%d %f %f %s \n",fileNum,offset,scale,outFile);
	array = readfile(fileNum);
	for(i=0;i<6;i++){
		printf("%d\n",*(array+i));
	}
	
	if(flag1 == 1){
		copy(array,outFile2);
	}
	
	if(offset != 0){
		sprintf(outFile,"Offset_data_%02d.txt",fileNum);
		do_offset(array,offset,outFile);
	}
	
	if(scale != 0){
		sprintf(outFile,"Scaled_data_%02d.txt",fileNum);
		do_scale(array,scale,outFile);
	}
	
	if(statsflag == 1){
		sprintf(outFile,"Stats_data_%02d.txt",fileNum);
		double average = find_avg(array);
		int max = find_max(array);
		save_stats(average,max,outFile);
	}
	
	if(normalflag == 1){
		sprintf(outFile,"Normal_data_%02d.txt",fileNum);
		int maxval = find_maxval(fileNum);
		printf("Maxval: %d\n",maxval);
		save_normal(array,maxval,outFile);
	}
	
	if(centerflag == 1){
		sprintf(outFile,"Center_data_%02d.txt",fileNum);
		double average1 = find_avg(array);
		save_center(average1,array,outFile);
	}

	free(array);
	free(outFile);
	return 0;
}

void error(void){
	printf("Incorrect use of program!\nThe correct use is as follows:\n");
	printf("./programName -h\nOr\n./progName -n 'file number' -o 'int' -s 'double' -r 'Output file name'\n");
	
}

int* readfile(int fileNum){
	int i = 1;
	char* filename = malloc(sizeof(char)*16);
	sprintf(filename,"Raw_data_%02d.txt",fileNum);
	printf("%s\n",filename);
	FILE* fp = fopen(filename,"r");
	if(fp == NULL){
		printf("file not opened\n");
	}
	
	int length = 0;
	int maxval = 0;
	fscanf(fp,"%d %d",&length,&maxval);
	
	int* array = malloc(sizeof(int)*(length+1));
	*array = length;
	for(i=1;i<=length;i++){
		fscanf(fp,"%d",(array+i));
		printf("%d\n",*(array+i));
	}
	fclose(fp);
	return array;
}

void do_offset(int* array, double offset, char* outFile){
	int length = *array;
	FILE* fp = fopen(outFile,"w");
	if(fp == NULL){
		printf("file not opened\n");
	}
	int i = 1;
	fprintf(fp,"%d %.4f\n",length,offset);
	for(i=1;i<=length;i++){
		fprintf(fp,"%.4f\n",(double)(*(array+i) + offset));
		
	}
	fclose(fp);
}

void do_scale(int* array, double scale,char* outFile){
	int length = *array;
	FILE* fp = fopen(outFile,"w");
	if(fp == NULL){
		printf("file not opened\n");
	}
	int i = 1;
	fprintf(fp,"%d %.4f\n",length,scale);
	for(i=1;i<=length;i++){
		fprintf(fp,"%.4f\n",(double)(*(array+i) * scale));
		
	}
	fclose(fp);
}

void copy(int* array, char* outFile){
	char* filename = malloc(sizeof(char)*40);
	sprintf(filename,"%s.txt",outFile);
	FILE* fp = fopen(filename,"w");
	int i = 1;
	for(i=1; i<=*array;i++){
		fprintf(fp,"%d\n",*(array+i));
	}
	fclose(fp);
}

double find_avg(int* array){
	int length = *array;
	int i = 1;
	double total = 0;
	double average = 0;
	for(i=1;i<=length;i++){
		total = total + *(array + i);
	}
	average = total/(double)length;
	return average;
}

int find_max(int* array){
	int length = *array;
	int i = 1;
	int max = *(array+1);
	for(i=1;i<=length;i++){
		if(*(array+i)>max){
			max = *(array+i);
		}
	}
	return max;
}

void save_stats(double average, int max, char* filename){
	FILE* fp = fopen(filename,"w");
	fprintf(fp,"%.4f %d",average,max);
	fclose(fp);
}

void save_center(double average, int* array, char* outFile){
	FILE* fp = fopen(outFile,"w");
	int length = *array;
	int i =1;
	for(i=1;i<=length;i++){
		fprintf(fp,"%.4f\n",(double)*(array+i) - average);
	}
	fclose(fp);
}

int find_maxval(int filenum){
	char* filename = malloc(sizeof(char)*16);
	sprintf(filename,"Raw_data_%02d.txt",filenum);
	FILE* fp = fopen(filename,"r");
	if(fp == NULL){
		printf("file not opened\n");
	}
	
	int length = 0;
	int maxval = 0;
	fscanf(fp,"%d %d",&length,&maxval);
	return maxval;
}

void save_normal(int* array,int maxval,char* outFile){
	FILE* fp = fopen(outFile,"w");
	int length = *array;
	int i = 1;
	for(i=1;i<=length;i++){
		fprintf(fp,"%.4f\n",(double)*(array+i)/(double)maxval);
	}
	fclose(fp);
}

