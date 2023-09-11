#include <stdio.h>
#include <stdlib.h>

//function prototypes
int obtainRandomSample(int *sequence);
int testRandomSample();

int obtainRandomSample(int *sequence)
{
    if(!sequence) //null ptr error check
    {
        printf("\nError, Invalid Pointer Used");
    }

    int x; //return variable of function
    x = *sequence; //sets x equal to first value in sequence

    double k = 0; //variable represents amount of values in sequence, used in if statement for random factor
    int i = 0;

    while (*(sequence + i) != INT32_MAX) //while loop increments thru sequence until end (NaN)
    {
        if (drand48() <= 1/(k+1)) //compares random num to reservoir sampling, if greater or equal to, then x is replaced
        {
            x = *(sequence + i); //sets return value to current sequence value, randomly decided upon when using if statement
        }
        k++; //increments k (amount of variables in sequence)
        i++; //increments z (used to traverse through sequence)
        //(sequence + 1); //increments sequence by one until end of loop (at end of sequence)
    }
    
    return x; //returns random value from sequence
}

int testRandomSample()
{
    int arr[51]; //initalize array
    int (*array)[51] = &arr; //ptr to array, allows for it to be passed to obtainRandomSample()
    int a; //counter variable, instances of first element chosen
    int b; //counter variable, instances of last element chosen
    int i; //counter variable used in for loops
    int x = 0; //spare variable, used in for loops
    
    FILE *fptr;
    fptr = fopen("test.txt","r"); //opens file to read values into array

    if (fptr == NULL) //file check
    {
        printf("\nError Opening File");
        return 2;
    }

    for (i = 0; i < 50; i++) //fills array with values from file
    {
        fscanf(fptr, "%d" , &arr[i]);
    }
    fclose(fptr); //closes file, no longer needed for reading

    arr[50] = INT32_MAX;
    a = arr[0]; //first element of array
    b = arr[49]; //last element of array before INT_MAX

    int tests = 1000000;
    for (i = 0; i < tests; i++)
    {
        x = obtainRandomSample(*array); //tests function w array
        //printf("%d ",x);
       
        if (x == 1) //increments variable for each time first element in sequence is chosen
        {
            a++;
        }

        if (x == 50) //increments variable for each time last element in sequence is chosen
        {
            b++;
        }
    }
    //printf("A = %d, B = %d",a,b); 

    if ((a+b) == tests) //makes sure that not only ends are being selected
    {
        printf("Error, Incorrect Operation");
        return 2;
    }
    
    if (a == 0 || b == 0) //one end never chosen case, function not working
    {
        printf("\nError, Incorrect Operation");
        return 2;
    }

    if (a < tests*.0175 || b < tests*.0175) //bias to one side of array case, tests if they're choosen at least 2% of the time
    {
        printf("\nError, Function Shows Bias");
        return 1;
    }

    return 0; 
}

