#include <stdio.h>
#define SIZEOF(object) (&object+1) - (&object)

int main()
{
    double x;
    int arr[10];
    
    printf("double var size: %d\n", SIZEOF(x));
    printf("double type size: %d\n", sizeof(double));
    printf("int arr[10] size : %d\n", SIZEOF(arr));
    return 0;
}
