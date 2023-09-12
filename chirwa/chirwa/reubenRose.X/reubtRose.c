/*
 * File:   reubtRose.c
 * Author: rbn
 *
 * Created on June 13, 2023, 6:41 PM
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#define Mr_LCD PORTB

#define EN 0
#define RS 2
#define RW 1
uint8_t z=0;
int x;
int one, zero, two, three, four, five;
int a=3;
int b=4;
int c =5; 
int d =6;
int e = 0b11110000;
int main(void) {
    iniT();
  
   LCD_by_Pos(0, 0, "WELCOME");
   //lcd_Num(x);
//send_A_String("Welcome!!!");
    _delay_ms(100);

 
    while (1) {
        functionalization();
        _delay_ms(50);
    }
    return 0;
}
void Send_Command(unsigned char Command) {
    PORTD &= ~(1 << RS);
    PORTD &= ~(1 << RW);
    Mr_LCD = Command & 0xF0;
    PORTD |= (1 << EN);
  
    _delay_ms(1);
    PORTD &= ~(1 << EN);
    Mr_LCD = Command << 4;
    PORTD |= (1 << EN);
    _delay_ms(1);
    PORTD &= ~(1 << EN);
     _delay_ms(1);

}

void Send_Character(unsigned char data) {
    PORTD |= (1 << RS);
    PORTD &= ~(1 << RW);
    Mr_LCD = data & 0xF0;
    PORTD |= (1 << EN);
  _delay_ms(1);
    PORTD &= ~(1 << EN);
    Mr_LCD = data << 4;
    PORTD |= (1 << EN);
    _delay_ms(1);
    PORTD &= ~(1 << EN);
     _delay_ms(1);

}

void iniT() {
    DDRB = 0xff;
    DDRD = 0xff;
    DDRC = 0x00;
    PORTD &= ~(1 << EN);
    Send_Command(0x33);
    Send_Command(0x32);
    Send_Command(0x28);
  Send_Command(0x0e);
    Send_Command(0x01);
    Send_Command(0x06);
     _delay_ms(1);
}
void send_A_String(const char *str){
    unsigned char a=0;
    while(str[a]!=0){
        Send_Character(str[a]);
        a++;
    }
}


void LCD_Go_To(unsigned char x, unsigned char y) {
    unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
    Send_Command(firstCharAdr[y - 1] + x - 1);
    _delay_ms(20);
}
void LCD_by_Pos(char row, char pos, const char *string1){
    if(row == 0 && pos < 16){
        Send_Command((pos & 0x0F)|0x80);
        send_A_String(string1);
    }
    if(row == 1 && pos < 16){
        Send_Command((pos & 0x0F)|0xC0);
        send_A_String(string1);
    }
    else if(row == 2 && pos < 16){
        Send_Command((pos & 0x0F)|0x94);
        send_A_String(string1);
    }
    else if(row == 2 && pos < 16){
        Send_Command((pos & 0x0F)|0xD4);
        send_A_String(string1);
    }
  
    
}

void lcd_Num(uint8_t num){
    num = 0;
    char buffer[16];
    sprintf(buffer, "%d", num);
    send_A_String(buffer);
}
// calculations for mode 0
void calculation4M_0(){
       char answer1[10];
       int  x = (a*b)+(~e);
        LCD_by_Pos(2, 1, "(a*b)+(~e)=");
        sprintf(answer1, "%d", x);
      LCD_by_Pos(2,13,answer1);
}
// calculations for mode 1
  calculation4M_1(){
              char answer1[10];
       int  x = a+c+ ~e;
        LCD_by_Pos(2, 0, "a+c+ ~e=");
        sprintf(answer1, "%d", x);
      LCD_by_Pos(2,13,answer1);
  }
  // calculations for mode 2
  calculation4M_2(){
              char answer1[10];
       int  x = a+ (c|d);
        LCD_by_Pos(2, 0, "a+ (c|d)=");
        sprintf(answer1, "%d", x);
      LCD_by_Pos(2,13,answer1);
  }
  // calculations for mode 3
    calculation4M_3(){
              char answer1[10];
       int  x = a+ (c|d);
        LCD_by_Pos(2, 0, "a+ (c|d)=");
        sprintf(answer1, "%d", x);
      LCD_by_Pos(2,13,answer1);
  }
    // calculations for mode 4
     calculation4M_4(){
              char answer1[10];
       int  x = b+ (c|d) +~e;
        LCD_by_Pos(2, 0, "b+ (c|d)=");
        sprintf(answer1, "%d", x);
      LCD_by_Pos(2,13,answer1);
  }
     // calculations for mode 5
       calculation4M_5(){
              char answer1[10];
       int  x = b+ (c|d);
        LCD_by_Pos(2, 0, "b+ (c|d)=");
        sprintf(answer1, "%d", x);
      LCD_by_Pos(2,13,answer1);
  }
       //modes program
void functionalization(){
     DDRC = 0x00;
     PORTC |=(1<<PINC);
      
     //for mode 0
     if((PINC &(1<<PC2)) && (PINC &(1<<PC1)) && (PINC &(1<<PC0))){
           LCD_by_Pos(1, 0, "MODE: 0");
        
         //arithmetic ABE
        calculation4M_0();
        
     } 
    //for mode 1
     else if( !( PINC &(1<<PC2)) && (PINC &(1<<PC1)) && (PINC &(1<<PC0))){
           LCD_by_Pos(1, 0, "MODE: 1");
       
         //arithmetic ABE
        calculation4M_1();
    
     }
      //for mode 2
      else if( ( PINC &(1<<PC2)) && !(PINC &(1<<PC1)) && (PINC &(1<<PC0))){
           LCD_by_Pos(1, 0, "MODE: 2");
       
         //arithmetic ACD
        calculation4M_2();
    
     }
      //for mode 3
       else if( !( PINC &(1<<PC2)) && !(PINC &(1<<PC1)) && (PINC &(1<<PC0))){
           LCD_by_Pos(1, 0, "MODE: 3");
       
         //arithmetic ACD
        calculation4M_3();
    
     }
     
      //for mode 4
     else if( ( PINC &(1<<PC2)) && (PINC &(1<<PC1)) && !(PINC &(1<<PC0))){
           LCD_by_Pos(1, 0, "MODE: 4");
       
         //arithmetic ACD
        calculation4M_4();
    
     }
      //for mode 5
       else if( !( PINC &(1<<PC2)) && (PINC &(1<<PC1)) && !(PINC &(1<<PC0))){
           LCD_by_Pos(1, 0, "MODE: 5");
       
         //arithmetic ACD
        calculation4M_5();
    
     }
     
     else{
         Send_Command(0x01);
     }
      
        

}