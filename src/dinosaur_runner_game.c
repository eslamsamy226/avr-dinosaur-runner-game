
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include <stdlib.h>
#include "std_macros.h"
#include "Button.h"
#define  F_CPU 8000000UL

char dino1[8] = {0b00111,0b00111,0b00100,0b01111,0b01110,0b11110,0b01010,0b01010};
char tree[8] = {0b10101,0b10101,0b10101,0b10101,0b11111,0b00100,0b00100,0b00100};
struct ob{
	char active;
	char x;
};
int mx_score=0,score=0;
void move(char x){
	LCD_movecursor(2,x);
	LCD_vSend_char(0x20);
	
	if(x>1){ 
		LCD_movecursor(2,x-1);
		LCD_diplay_custom_char(4);		
	}
	
}


void display_max_score(){
	LCD_movecursor(2,1);
	LCD_vSend_string("Max Score : ");
	int s=mx_score;
	LCD_movecursor(2,16);
	char cc='0'+s%10;
	LCD_vSend_char(cc);
	s/=10;
	LCD_movecursor(2,15);
	cc='0'+s%10;
	LCD_vSend_char(cc);
	s/=10;
	LCD_movecursor(2,14);
	cc='0'+s%10;
	LCD_vSend_char(cc);
	s/=10;
	LCD_movecursor(2,13);
	cc='0'+s%10;
	LCD_vSend_char(cc);

}
void display_score(){
	score++;
	if(score>mx_score)mx_score=score;
	int s=score;
	LCD_movecursor(1,16);
	char cc='0'+s%10;
	LCD_vSend_char(cc);
	s/=10;
	LCD_movecursor(1,15);
	cc='0'+s%10;
	LCD_vSend_char(cc);
	s/=10;
	LCD_movecursor(1,14);
	cc='0'+s%10;
	LCD_vSend_char(cc);
	s/=10;
	LCD_movecursor(1,13);
	cc='0'+s%10;
	LCD_vSend_char(cc);

}
char mx=0,up=0,lost=0;
unsigned char d=0;
int main(void)
{
	
		
	
	struct ob trs[3]={{0,17},{0,17},{0,17}};	
	LCD_vInit();
	LCD_store_custom_char(1,dino1);

	LCD_store_custom_char(4,tree);
	button_vInit('D',2);
	DIO_vconnectpullup('D',2,1);

	Buzzer_vInit('C',0);

while(1){
	if (lost)
	{
		while(IS_BIT_SET(PIND,2));
		_delay_ms(800);	
	}
	for (char i=0;i<3;i++){
		trs[i].x=17;
		trs[i].active=0;
	}		
	 mx=0,up=0,lost=0;
	LCD_vSend_cmd(CLR_SCREEN);
	LCD_movecursor(1,3);
	LCD_vSend_string("DINO RUNNER");
	display_max_score();
	while(IS_BIT_SET(PIND,2));
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(800);
	LCD_movecursor(2,3);
	LCD_diplay_custom_char(1);
    while(1)
    {
      _delay_ms(400);
	  if (up==4)
	  {
		  	LCD_movecursor(1,3);
		  	LCD_vSend_char(0x20);
		  	LCD_movecursor(2,3);
		  	LCD_diplay_custom_char(1);
		  up=0;
	  }
	  if(up>0) up++;
	  char cur_mx=0;
	  if (d%10==0)
	  {
		 display_score();
	  }
		d++;
		for (char i=0;i<3;i++)
		{
			if (trs[i].active==0 && mx<14 && rand()%2==0)
			{
				trs[i].active=1;
			}
			if (trs[i].active)
			{
				move(trs[i].x);
				trs[i].x--;
				if(trs[i].x>cur_mx) cur_mx=trs[i].x;
				if (trs[i].x<=0)
				{
					trs[i].x=17;
					trs[i].active=0;
				}
			}
			if (trs[i].active==1 && trs[i].x==3 && up==0)
			{
				lost=1;
			}
		}
		mx=cur_mx;
		if (lost)
		{
			LCD_vSend_cmd(CLR_SCREEN);
			LCD_movecursor(1,4);
			LCD_vSend_string("GAME OVER");
			score=0;
			_delay_ms(650);
			break;
		}
		if (IS_BIT_CLR(PIND,2))
		{
			Buzzer_vOn('C',0);
	LCD_movecursor(2,3);
	LCD_vSend_char(0x20);
	LCD_movecursor(1,3);
	LCD_diplay_custom_char(1);
	up=0;
	up++;
	}
	  _delay_ms(900);  
	  Buzzer_vOff('C',0);
	  display_score();
    }
}
}

