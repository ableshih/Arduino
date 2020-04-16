
# MAX7219 4x2

```
硬體	UNO
5V	5V
GND	GND
DIN	12
CS	10
CLK	11

可顯 . - 0 1 2 3 4 5 6 7 8 9 A b c d E F H L P n o 

0 1 2 3 4 5 6 7 8 9 . -
v v v v v v v v v v v v

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 
v b c d v v x v x x x v x n o v x x x x x x x x x x

a b c d e f g h i j k l m n o p q r s t u v w x y z
A v v v E F x H x x x L x v v P x x x x x x x x x x

LedControl lc=LedControl(12,11,10,1);DIN,CLK,CS,有幾顆IC

#include "LedControl.h"

lc.setChar(0,7,'0',false);第一個，第8位顯
lc.setChar(0,6,'A',false);第一個，第7位顯
lc.clearDisplay(0);清除


Arduino
void writeArduinoOn7Segment() {
  lc.setChar(0,7,'a',false);  //A
  lc.setRow(0,6,0x05);        //r
  lc.setChar(0,5,'d',false);  //d
  lc.setRow(0,4,0x1c);        //u
  lc.setRow(0,3,B00010000);   //i   lc.setRow(0,3,0x10);
  lc.setRow(0,2,0x15);        //n
  lc.setRow(0,1,0x1D);        //o
  delay(delaytime+5000);
  lc.clearDisplay(0);
} 


 -	     A
| |   	F B
 -	     G
| |   	E C
 - .	   D DP

D7 D6 D5 D4 D3 D2 D1 D0
DP A  B  C  D  E  F  G

全亮 0xff
.  0x80
1  0x30
6  0x5f
U  0x3e
```
