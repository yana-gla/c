#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
	
	
typedef void (*ArrPtrTFun)();

void a_press()
{
	printf ("A-presses\n");
}
void t_press()
{
    printf("T-pressed\n");
}
void Esc_press()
{
	system("stty icanon echo");
	exit(0) ;	
}
void other_press()
{
}

/*LUT*/


int main(void)
{	

	/*example to poiner to function array
	void (*functions[3])(void);*/

	char ch = '\0';	
	int i = 0;
	ArrPtrTFun keys[256];
	system("stty -icanon -echo");
	printf("Press 'A', 'T', or 'Esc' (to exit):\n");

	 
	 /*option switch
	 while (1)
	 {
	 	ch = getchar(); /*like scanf only to one character
	 	
	 	switch (ch)
	 	{
	 		case 27: /*asci for esc
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
	 		     
	 		default: /*other keys
	 			 break;
	 	}
	 }
	 */
	 
	 	/*option if-else
	 	while(1)
	 	{
	 		ch = getchar();
	 		
	 		if(27 == ch)
	 		{
	 			system("stty icanon echo");
	 			return 0;	
	 		}
	 		else if ('A' == ch || 'a' == ch)
	 		{
	 			 printf("A-pressed\n");
	 		}
	 		else if ('T' == ch || 't' == ch)
	 		{
	 			 printf("T-pressed\n");
	 		}
	 		else 
	 		{
	 		}
	 	}
	 	*/
	 	
	 	/*Using LUT*/

	 	
	 	for (i = 0; i < 256; i++)
	 	{
            keys[i] = other_press;
        }
        
	 	keys['A'] = keys['a'] = a_press;
	 	keys['T'] = keys['t']= t_press;
	 	keys[27] =  Esc_press;
	 	
	 	while(1)
	 	{
	 		ch = getchar();
	 		keys[ch]();
	 	}
	 		
	 	system("stty icanon echo");
	 	
	 return 0;
}
	 		     
	 		     


