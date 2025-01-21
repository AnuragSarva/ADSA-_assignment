// NOTE:- This program will takes few minutes to run...
// The below code generates random permutation of array of 4 diffrent size and 100 for each.
// and uses Fisher Yeates shuffle also to get random permutation.
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// the above headers gives to a permission to use the inbuild librarys such as printf(), fprintf(), fsacnf() for reading and writing to files.
// malloc(), free(), rand() to create memeory location during runtime and also free the space and for random number generation.

// below function will help us to swap two numbers
void swop(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// The below function is used to generate a random permutation of an array elements, for that it will uses Fisher Yates Shuffle Algorithm.
void Ara_Gen_Rand(int *ara, int sz) {
    // the below loop will iterate and store the value from 1 to value of size in the array.
    // initially array stores the data sequencely not in random order.
    for (int i = 1; i <= sz; i++) {
        ara[i] = i;
    }
    
    // below few line of code is the implementaition of a Fisher Yates Algorithm, used to shuffel the element of a array in random permutation.
    for (int i = sz -1; i > 0; i--) {
        // below line of code is used find the randdom index and stored that index in j, the value between index i and index j is swaped, i.e. how it will randomised the array. 
        // by using this algorithm, it ensures that every element has equal probability of being placed in any position, i.e. how it will generate random permutation of the array.
        int j = rand() % (i+1);
        // calling another function swap element at index i and j.
        swop(&ara[i], &ara[j]);
    }
}

// Below is the function used to save generated arrays in text file.
void save_Arr_in_txt_file(int given_arra_sz[], int arra_sz, int numArr) {
    // here two nested loop runs, the outer loop is four times for all different size of array and the inner is run hundred times to geneartehundred array for each differnet sizes.
    for (int s = 0; s < arra_sz; s++) {
        int sz = given_arra_sz[s];
        // below line of code will generate 100 differnt permuted array of same size.
        for (int a = 0; a < num_of_Arr; a++) {
            char filename[100];
            // here i am creating the text file with name like- "array_1_of_size_10000.txt"
            sprintf(filename, "array_%d_of_size_%d.txt", a + 1, sz);
            // below is the line of code for file handeling in C.
            // here file is opened for write the element into it.
            FILE *file = fopen(filename, "w");
            // this line of code will help me check the file is coreectly opened or not, if not openend then function will terminate.
            if (file == NULL) {
                printf("There is a error to open the text file!!!\n");
                return;
            }

            // randomly memery is crearted to store element into the array of size 'size'.
            int *arr = (int *)malloc(sz * sizeof(int));
            // using below line of code to fill the array with random permuutation by uisng user defined function.
            Ara_Gen_Rand(arr, sz);
             
            // now the generated array is iterated from begin to end, each element is inserted into the text file in single coloum.
            for (int i = 0; i < sz; i++) {
                fprintf(file, "%d\n", arr[i]);
            }
            
            // after writng process is done, then we close the file, to protect data.
            fclose(file);
            // now deallocating the run time allocated memory to free up the space.
            free(arr);
        }
    }
}

void prog_des()
{
    printf("Programing Assignment 1, Problem 0. Randomly generate array.\n");
}

int main() { 
    // below line of code will make sure that it will generate random number each time the program runs.
    srand(time(0));  
    // this is the array of different size, which is provided in the question. 
    int given_arra_sz[] = {10000, 100000, 1000000, 10000000};
    int num_of_Arr = 100;
    // here i am finding the size of array.
    // here i can directly write 4 but i am writing a code such that i will work not only for this data for other also.
    int arra_sz = sizeof(given_arra_sz) / sizeof(given_arra_sz[0]);

    prog_des();

    // this printf is only for indicating the program will start runing.
    printf("Problem 0 is started runing...\n");

    // function call to generate the array with randon permutation and store into deffernt text file for defferent sizes.
    save_Arr_in_txt_file(given_arra_sz, arra_sz, num_of_Arr);
    
    // this will tell us that program will run seccessfully.
    printf("Successfully arrays is generated and saved into a text file.\n");
    return 0;
}
