#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 11 /* Hint */
#define PUZZLE_SIZE 9

int rv = 1; // flag to check answer
int sum = 0;

/* example puzzle */
int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1] = {
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0}
		};

/* data structure for passing data to threads */
typedef struct
{
	int thread_number;
	int x;
	int y;
} parameters;

/* print puzzle */ 
#define LINE "====================== \n"
#define COLLINE "\n___________________________________ \n"
#define NAME "||  SUM   CHECKER  || \n"
void print_grid(int grid[10][10])
{
    int i,j;
    printf(LINE);
    printf(NAME);
    printf(LINE);

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
	        printf("|%1d |",grid[i][j]);
		}
        printf(COLLINE);
	}
    printf("\n");
}
// read file to check sudoku
void SetPuzzle(char filename[]){
    FILE *file = fopen(filename,"r");
    int i,j,ch,num;
    for (i=0;i<=9;i++){
        for(j=0;j<=9;j++){
            while(((ch = getc(file)) != EOF)){
                if(ch == EOF) break;
                if(ch == ',') break;
                if(ch == '\n') break;
                ungetc(ch,file);
                fscanf(file,"%d",&num);
                if(num!=-1)
                    puzzle[i][j] = num;            
            } 
        }
    }
    print_grid(puzzle);
    return;
}

void* check_sum(void* param){
	if (!rv) return NULL;
	parameters* my_param = (parameters*)param;
	int my_num = my_param->thread_number;
	int my_x = my_param->x;
	int my_y = my_param->y;
	int my_sum = 0;
	int i, j;
	if (my_num < 9){
		for (i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				my_sum += puzzle[my_x + i][my_y + j];
			}
		}
	}
	if (my_num = 9){
		for (i = 1; i < 10; i++){
			my_sum = 0;
			for (j = 1; j < 10; j++){
				my_sum += puzzle[i][j];
			}
			if (my_sum != sum){
				rv = 0;
				break;
			}
		}
	}
	if (my_num = 10){
		for (i = 1; i < 10; i++){
			my_sum = 0;
			for (j = 1; j < 10; j++){
				my_sum += puzzle[j][i];
			}
			if (my_sum != sum){
				rv = 0;
				break;
			}
		}
	}
	if (my_sum != sum) rv = 0;
	return NULL;
}

int main(int argc, char* argv[])
{
	// input the sudoku file
	SetPuzzle("test1");
	
	pthread_t* thread_handles;
	thread_handles = (pthread_t*)malloc(NUMBER_OF_THREADS * sizeof(pthread_t));
	int thread;
	int i;
	for (i = 1; i < 10; i++) sum += puzzle[1][i];
	for (thread = 0; thread < NUMBER_OF_THREADS; thread++){
		if (!rv) break;
		parameters* param =(parameters*)malloc(sizeof(pthread_t));
		param->thread_number = thread;
		param->x = (thread%3)*3 + 1;
		param->y = (thread/3)*3 + 1;
		pthread_create(&thread_handles[thread], NULL, check_sum, (void*)param); 
	}
	for (thread = 0; thread < NUMBER_OF_THREADS; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	free(thread_handles);
	
	if (rv == 1)
		printf("Successful :) \n");
	else
		printf("Must check again! :( \n");

	return 0;
}
