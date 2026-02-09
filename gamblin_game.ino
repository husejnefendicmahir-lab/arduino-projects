#include "stm32f10x.h"
#include "TM1637.h"
#include "delay.h"
#include "gpio.h"
#include "ctime"
#include "cstdlib"

int broj = 0;
int main(void)
{

	tm1637Init();
	tm1637SetBrightness(8);
	
	int rendom_broj=rand()%10000;
	int rendom_broj2=rand()%10000; 
	
	bool test=true;
	bool test2=true;
	int skor=0;
	
	pinMode (A4,INPUT);
	pinMode(A7,INPUT);

	while(1)
	{
		tm1637DisplayDecimal(rendom_broj2,0);
		int val=digitalRead(A4);
		int val2=digitalRead(A7);
		
		if ((test) && (val))
		{
			if (rendom_broj>rendom_broj2){
					
				skor++;
				tm1637DisplayDecimal(skor,0);
				delaymS(4000);
			
			} else {
				
				rendom_broj=rand()%10000;
				rendom_broj2=rand()%10000;
				skor=0;
			
			}
		test = false;
		if(broj>=9999)broj=0;
		}
		
		if ((!test) && (!val))
		{
			test =true;
		}
		
		
		if (val2==1 and test2==true)
		{
			if (rendom_broj<rendom_broj2){
					
				skor++;
				tm1637DisplayDecimal(skor,0);
				delaymS(4000);
			
			} else {
				skor=0;
				rendom_broj=rand()%10000;
				rendom_broj2=rand()%10000;
			
			}
			test2=false;
		if(broj>=9999 or broj<0)broj=0;
		}
		if (test2!=true and val2!=1)
		{
			test2 =true;
		}
	
	
	}
}
