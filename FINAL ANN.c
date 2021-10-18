#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void randomizer(float matrix[10][10], int row, int col){
	int i,j;
	
	for (i = 0; i < row; ++i) {
    	for (j = 0; j < col; ++j) {
        	float x=rand()%10;
			matrix[i][j]=x*0.1;
      }
   }
   
   for (i = 0; i < row; ++i) {
    	for (j = 0; j < col; ++j) {
        	printf("%0.3f  ",matrix[i][j]);
      }
      printf("\n");
	}
}


void sigmoid(float arr[10][10],int row,int col)
{
	const double e=2.718281828459045;
	int i,j;
	
	for (i=0;i<row;i++){
		for(j=0;j<col;j++){
			arr[i][j]=1/(1+pow(e,-arr[i][j]));
		}
	}
}


void bias(float matrix[10][10],int row ,int col, float bias){
	int i,j;

	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			matrix[i][j]=matrix[i][j]+bias;
		}
	}
}

// function to multiply two matrices
void multiplyMatrices(float first[][10], float second[][10], float h1[][10], int r1, int c1, int r2, int c2){
	int i,j,k;				

   // Multiplying first and second matrices and storing it in h1
   for (i = 0; i < r1; ++i) {
      for (j = 0; j < c2; ++j) {
			h1[i][j]=0;
        	
			for (k = 0; k < c1; ++k) {
            	h1[i][j] += first[i][k] * second[k][j];
         }
      }
   }
}

// function to display the matrix
void display(float (*h1)[10], int row, int column) {
	int i,j;
	printf("\n");

    for (i=0; i<row; i++){
    	
        for (j=0; j<column; j++){
        
		    printf("%0.5f     ", *(*(h1+i)+j));
        }
		
		printf("\n");
    }

   printf("\n");
   
}
void loss(float val, int key){
	float error=0;
	float num;
	
	num=key-val;
	num=pow(num,2);
	
	FILE *fp;
	fp=fopen("error.txt","a+");
	
	static int count=0;
	static float losss=0;
	losss= num+losss;
	
	
	count++;
	
	if (count==150){
		error=losss/150;
	
		fprintf(fp,"ERROR : %0.10f\n\n",error);	
	}
	
}

void argmax(float arr[10][10],float first[10][10]){
	int i,j;
	float max=arr[0][0];
	int key=0; 
	
	
	for (i=0;i<1;i++){
		for(j=0;j<3;j++){
			if(arr[i][j]>max){
				max=arr[i][j];
				key=j;				
			}		
		}
	}
	
	loss(max,key);
	
	
	printf("MAX VALUE IS LOCATED AT LOCATION :\x1b[106m\x1b[30m %d \x1b[0m\x1b[0m",key);
	FILE *out;
	out=fopen("prediction.txt","a");

	if(key==0){
		for(i=0;i<1;i++){
			for(j=0;j<4;j++){
				fprintf(out,"%0.1f    ",first[i][j]);
			}
		}
		fputs(" CLASS: 0\n",out);
	}
	if(key==1){
		for(i=0;i<1;i++){
			for(j=0;j<4;j++){
				fprintf(out,"%0.1f    ",first[i][j]);
			}
		}
		fputs(" CLASS: 1\n",out);
	}
	if(key==2){
		for(i=0;i<1;i++){
			for(j=0;j<4;j++){
				fprintf(out,"%0.1f    ",first[i][j]);
			}
		}
		fputs(" CLASS: 2\n",out);
	}
	
}



struct matrix{
	float first		[10][10];
	float second	[10][10];
	float h1		[10][10];
	float third		[10][10];
	float h2		[10][10];
	float fourth	[10][10];
	float h3		[10][10];	
};

int main() {
	system("color 00");
	srand(time(NULL));
	
	struct matrix m;
	int r1, c1, r2, c2;
	r1=1;
	c1=4;
	float number;
	int i,j,k,dec;
	float bi;
	
	printf("\x1b[93m");
	printf("--------MENU--------\n\n");
	printf("1. RUN THE ANN\n\n");
	printf("2. VIEW PREVIOUS RESULT\n\n");
	printf("3. VIEW ERROR THROUGH LOSS FUNCTION\n\n");
	printf("4. VIEW NAMES OF STUDENTS\n\n");
	printf("5. VIEW DATA SET\n\n");
	printf("6. PRESS 0 TO EXIT\n\n\n");
	printf("\x1b[0m");
	scanf("%d",&dec);
	
	if(dec==1){
	
	//not taking input of first data set matrix because its fixed
	printf("\nEnter rows and column for the first weight matrix: ");
	scanf("%d %d", &r2, &c2);
	printf("\n\nEnter value for bias: ");
	scanf("%f",&bi);

   // Taking input until
   // 1st matrix columns is not equal to 2nd matrix row
	while (c1 != r2) {
    	printf("Error! Enter rows and columns again.\n");
    	//printf("Enter rows and columns for the first matrix: ");
    	//scanf("%d%d", &r1, &c1);
    	printf("Enter rows and columns for the second matrix: ");
    	scanf("%d%d", &r2, &c2);
   }

	FILE *fp;
	fp= fopen("IRIS.txt","r");

	while(!feof(fp)){
		
		printf("\n\n\n\n");
		for (i=0;i<1; ++i){
			for(j=0;j<4;++j){
				fscanf(fp,"%f",&number);
				m.first[i][j]=number;
			}
		}

	printf("\x1b[107m");
	printf("\x1b[31m");
	for(i=0;i<1;i++){
		for(j=0;j<4;j++){
			printf("   %f",m.first[i][j]);
		}
	}
	printf("\x1b[0m");
	printf("\x1b[0m");
	printf("\n");
	
	
	
	// get elements of the first weight matrix
	printf("\x1b[36m");
	printf("\n\n\n");
	randomizer(m.second, r2, c2);
	printf("\x1b[0m");
	
	
	// multiply two matrices.
	multiplyMatrices(m.first, m.second, m.h1, r1, c1, r2, c2);
	
	bias(m.h1,r1,c2,bi);
	
	sigmoid(m.h1,r1,c2);
	
	printf("\n\x1b[4mHIDDEN LAYER 1 (sigmoid applied):\x1b[0m\n");
	
	// display the result
	display(m.h1, r1, c2);
	
	int a=5, b=3;
	int r3=1,c3=5;
	printf("\x1b[36m");
	randomizer(m.third,a,b);
	printf("\x1b[0m");
	
	printf("\n\x1b[4mHIDDEN LAYER 2 (sigmoid applied):\x1b[0m\n");
		
	multiplyMatrices(m.h1,m.third,m.h2,r3,c3,a,b);
	
	bias(m.h2,r3,b,bi);
	sigmoid(m.h2,r3,b);
	
	display(m.h2,r3,b);
	
	
	int c=3,d=3;
	
	printf("\x1b[36m");
	randomizer(m.fourth, c,d);
	printf("\x1b[0m");
	
	multiplyMatrices(m.h2,m.fourth,m.h3,r3,b,c,d);
	
	bias(m.h3,r3,d,bi);
	sigmoid(m.h3,r3,d);
	
	printf("\n");
	printf("\n\n\x1b[4mFINAL OUTPUT:\x1b[0m\n");
	display(m.h3,r3,d);	   
	
	argmax(m.h3,m.first);
	printf("\n\n\n\n");
	}
		
		FILE *out;
		out=fopen("prediction.txt","a+");
		
		fseek(out,0,SEEK_END);
		fprintf(out,"\n\n\n\n\n\n");
	}
	
	
	
	else if(dec==2){
		FILE *fptr;
		
		fptr=fopen("prediction.txt","r");
		char c=fgetc(fptr);
		
		if(c==EOF){
			printf("\x1b[91mNO RECORDS YET!!\x1b[0m");
		}
		
		while(c!=EOF){
			printf("\x1b[36m%c\x1b[0m",c);
			c=fgetc(fptr);
		}
	}
	
	else if(dec==3){
		
		printf("\x1b[91m\n\x1b[4mDISCREPANCIES BETWEEN DATA SET AND OUTPUT THROUGH LOSS\x1b[0m\n\n\x1b[0m");
		FILE *fp;
		fp=fopen("error.txt","a+");
		
		char c;
		c=getc(fp);
		
		while(c!=EOF){
			printf("\x1b[36m%c\x1b[0m",c);
			c=fgetc(fp);
			
		}
		
		fclose(fp);
		printf("\n\n\n\n");
		
	}
	else if (dec==4){
		printf("\x1b[91m\nPROJECT MADE BY: \x1b[0m\n");
		printf("\x1b[36m");
		printf("\nRayyan Minhaj 		20K-0143\n\n");
		printf("Kainat Afzal 		20K-0281\n\n");
		printf("Nashit Budhwani 	20K-0274\n\n");
		printf("Habeel Amin 		20K-0223\n\n");
		printf("Sabeerah Ahmed 		20K-0362\n\n");
		printf("Fabiha Atique		20K-0369\n\n");
		printf("\x1b[0m");	
		printf("\n\n\n\n");	
	}
	
	
	else if(dec==5){
		printf("\x1b[91m\n\x1b[4mDATA SET\x1b[0m\n\n\x1b[0m");
		FILE *fp;
		fp=fopen("IRIS.txt","a+");
		
		char c;
		c=fgetc(fp);
		while(c!=EOF){
			printf("\x1b[36m%c\x1b[0m",c);
			c=fgetc(fp);
		}			
	}
	else if(dec==0){
		exit(0);
	}

}
