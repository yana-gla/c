#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{	
	char ch = '\0';
	system("stty -icanon -echo");
	printf("Press 'A', 'T', or 'Esc' (to exit):\n");
	 
	 while (1)
	 {
	 	ch = getchar(); /*like scanf only to one character*/
	 	
	 	switch (ch)
	 	{
	 		case 27: /*asci for esc*/
	 			system("stty icanon echo");
	 			return 0;
	 		
	 		case 'A':
	 		case 'a':
	 		     printf("A-pressed\n");
	 		     break;
	 		     
	 		case 'T':
	 		case 't':
	 		     printf("T-pressed\n");
	 		     break;
	 		     
	 		default: /*other keys*/
	 			 break;
	 	}
	 }
	 return 0;
}
	 		     
	 		     

	 		
	 
	 

