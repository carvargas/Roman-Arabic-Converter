#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

//FOR SERVER PROGRAM

/* Conditions: 
  -- I placed before V or X indicates one less
  -- X placed before L or C indicates ten less
  -- C placed before D or M indicates a hundred less
 */
 
int convertToArabic(char * numeral, int len)
{
	/*look at first two, if doesnt match conditions, store first number, then look at next two (including the second number from first comparison)*/
	int count = 0;
	
	int arabic_num = 0;
	
	int i = 0;
	
	char check_char;
	
	while(count < len)
	{
		check_char = numeral[count];
		
		switch(check_char)
		{
			case 'i':
			case 'I': 
			{
				if(subOrAdd(1, numeral[count + 1]) == 1)
				{
					arabic_num += sub(1, numeral[count + 1]);
					count = count + 2;
					break;		
				}
				else
				{
					arabic_num += 1;
					count = count + 1;
					break;
				}
			}
			case 'x':
			case 'X': 
			{
				if(subOrAdd(10, numeral[count + 1]) == 1)
				{
					arabic_num += sub(10, numeral[count + 1]);
					count = count + 2;
					break;		
				}
				else
				{
					arabic_num += 10;
					count = count + 1;
					break;
				}
			}
			case 'c':
			case 'C': 
			{
				if(subOrAdd(100, numeral[count + 1]) == 1)
				{
					arabic_num += sub(100, numeral[count + 1]);
					count = count + 2;
					break;		
				}
				else
				{
					arabic_num += 100;
					count = count + 1;
					break;
				}
			}
			case 'v':
			case 'V':
			{
				arabic_num += 5;
				count = count + 1;
				break;
			}
			case 'l':
			case 'L':
			{
				arabic_num += 50;
				count = count + 1;
				break;
			}
			case 'd':
			case 'D':
			{
				arabic_num += 500;
				count = count + 1;
				break;
			}
			case 'm':
			case 'M':
			{
				arabic_num += 1000;
				count = count + 1;
				break;
			}
			default:
			{
				fprintf(stderr, "Error -- not a roman numeral\n");
				break;
			}
		}
	}
	
	return arabic_num;
	
}