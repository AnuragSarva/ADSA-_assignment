// NOTE:- This program will takes few minutes to run...
// This code is first implementing the randomized quick sort algorithm
// then it will read the text file which i had generated in previous code and computing averge comparision and standard deviation. 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// the above headers gives to a permission to use the inbuild librarys such as printf(), fprintf(), fsacnf() for reading and writing to files.
// malloc(), free(), rand() to create memeory location during runtime and also free the space and for random number generation.

// this is the global variable which will keep the record of comparision and it is reset for each run.
long compare = 0;

// this function is used swap the element of two variables.
void swop(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// this function will find randomly pivot element.
void r_p(int arr[], int l, int h)
{
    int rand_p = l + rand() % (h - l + 1);
    // after finding the pivot elements indes, it swap that element with last element.
    // basically it modifies the array.
    swop(&arr[rand_p], &arr[h]);
}

// This is the partition function of a quick sort algorithm which will select pivot randomly.
int partition(int arr[], int low, int high) {
    // here r_p function is call, it will help me to find pivot elelemt and replace it with last elelemt.
    r_p(arr, low, high);

    // from here the main process of partition function of a quick sort is started. 
    int pivot = arr[high];
    int i = low - 1;

    // in below for loop, index j's element is compared with the pivot element, if it is less then pivot element, 
    // then another variable i, is behind of it will move one spet forward and swap arr[i] and arr[j].
    for (int j = low; j < high; j++) {
        compare = compare + 1;
        if (arr[j] < pivot) {
            i = 1 + 1;
            swop(&arr[i], &arr[j]);
        }
    }

    // the below swap help me to keep the proper position of a pivot element.
    // that is the element which are less then pivot is are placed in left and greter is palced in right, automaticaly after this swap.  
    swop(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// This is the sole function for Randomized Quick Sort Algorithm.
void Quick_Sort_Randomized(int arr[], int low, int high) {
    if (low < high) {
        // this will call the partition function to get propr index of pivot element. 
        int x = partition(arr, low, high);
        // it will recursively call itself for left subpart and right subpart of the array.
        // this is for left sub array.
        Quick_Sort_Randomized(arr, low, x - 1);
        // this is for right sub array.
        Quick_Sort_Randomized(arr, x + 1, high);
    }
}

// this function is used to run Quick Sort algorithm and measures comparisons that needed in quick sort.
void sort_measure_ara(int arr[], int size) {
    // this will reset the comparision count evry time.
    compare = 0;  
    Quick_Sort_Randomized(arr, 0, size - 1);
}

// this is the dedicated function to read arrays from the text file
void rdArraFromtxtFile(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "r");
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

// this is a special function which is used to calculate square root for calculating standard deviation.
double cSqrt(double num) {
    double gss = num / 2.0;
    double apsln = 0.00001;
    int k;

    if(abs(gss * gss - num) >= gss) k = 1;
    else k = 0;

    do {
        if(k)
            gss = (gss + num / gss) / 2.0;
    } while (abs(gss * gss - num) >= gss);
    
    return gss;
}

// this function is designed for special task which is to compute average number of comparision and standard deviation.
void calstats(double *sumofcomp, double *avcomp, double *stddevtn, int *numsarray, double *comparnArray)
{
    for (int i = 0; i < *numsarray; i++) {
            *sumofcomp += comparnArray[i];
        }
    // computing average number of comparision
    *avcomp = *sumofcomp / *numsarray;
        
    for (int i = 0; i < *numsarray; i++) {
            *stddevtn += (comparnArray[i] - *avcomp) * (comparnArray[i] - *avcomp);
        }
    // this will finds standard deviation
    *stddevtn = cSqrt(*stddevtn / *numsarray);
}

// this is the driver function which helps me to open a text file.
void rd_fun(double *comparra, int *numsarra, int *sz)
{
    for (int i = 0; i < *numsarra; i++) {
            char filename[100];
            sprintf(filename, "array_%d_of_size_%d.txt", i + 1, *sz);
            // this is dynaeically allocation memeory, to store each array element.
            int *arr = (int *)malloc(*sz * sizeof(int));
            // this function a saved text file in problem 0.
            rdArraFromtxtFile(filename, arr, *sz);
            
            sort_measure_ara(arr, *sz);
            comparra[i] = compare;
            
            free(arr);
        }
}

void hello()
{
    printf("Programing Assignment 1, DSA Question number 2 part a. insertion in both the trees.\n");
}

int main() {
    // below line of code will make sure that it will generate random number each time the program runs.
    srand(time(0));
    // this is the array of different size, which is provided in the question. 
    int sizes[] = {10000, 100000, 1000000, 10000000};
    // here i am finding the size of array.
    // here i can directly write 4 but i am writing a code such that i will work not only for this data for other also.
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int numArrays = 100;

    // This is the array to store comparison counts for each run
    double comparisonsArray[100];
 
    hello();

    // below is the line of code for file handeling in C.
    // here file is opened for write the element into it.
    FILE *outFile = fopen("output_dsaq_1.txt", "w");
    // this line of code will help me check the file is coreectly opened or not, if not openend then function will terminate.
    if (outFile == NULL) {
        printf("There is a error to open the text file!!!\n");
        return 1;
    }
    
    // here i am assigning the name of a coloum in the text file.
    fprintf(outFile, "Array Size\tAverage Comparisons\n");
    
    for (int s = 0; s < numSizes; s++) {
        int size = sizes[s];
        printf("Program is running for array size: %d\n", size);
        
        // this function is used for assigning data of text file into filename and create dynamic memeory allocation and deallocation.
        rd_fun(comparisonsArray, &numArrays, &size);
        
        // Compute average and standard deviation of comparisons
        double sumofcomp = 0, avcomp, stddevtn = 0;
        // this is the function for specific task, it calculates average comparision and standard deviation.
        calstats(&sumofcomp, &avcomp, &stddevtn, &numArrays, comparisonsArray);
        
        printf("Array size: %d, Average comparisons: %.4lf, Standard deviation: %.4lf\n", size, avcomp, stddevtn);
        
        // Write the size and average comparisons to the output file
        fprintf(outFile, "%d\t%.4lf\n", size, avcomp);
    }
    
    // the below command is used to close the text file, this is comes under good programing skills.
    fclose(outFile);
    
    return 0;
}
