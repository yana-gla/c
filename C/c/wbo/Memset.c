/* Sample program to show that memmove() is better than */
/* memcpy() when addresses overlap. */
#include <stdio.h> 
#include <string.h> 
int main() 
{ 
    char str[100] = "LearningIsFun"; 
    char *first, *second; 
    first = str; 
    second = str; 
    printf("Original string :%s\n ", str); 
      
    /* when overlap happens then it just ignore it */
    /*memcpy(first + 8, first, 10); 
    printf("memcpy overlap : %s\n ", str); */
  
    /* when overlap it start from first position */
    
    /*memmove(second + 8, first, 10); 
    printf("memmove overlap : %s\n ", str); */
    
    memmove(str, second + 4, 10); 
    printf("memmove overlap : %s\n ", str); 
    
    
    
  
    return 0; 
}
