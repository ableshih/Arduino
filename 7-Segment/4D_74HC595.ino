/*
 * https://sites.google.com/site/csjhmaker/c-hu-dong-pian/4wei-qi-duan-xian-shi-qi
 4-Digit 7-Segment display driver.
 2x 74HC595 wired to 2x 4-digit 7-segment displays
 bits 0-7 select a digit
 bits 8-14 A-G
 顯示文字showText('A','B','C','D');
 顯示數字showText(1,2,3,4);
 若要顯示小數點：該位數字＋10
 */

#if 1
char disp_c[8] ;
const int SCLK_pin=6; 
const int RCLK_pin=7;
const int DIO_pin =5;
int  disp[8];

//time values for delay workaround
unsigned long prev =0;
unsigned long waitMS=0;

void setup(){
	pinMode(RCLK_pin,OUTPUT);
	pinMode(DIO_pin,OUTPUT);
	pinMode(SCLK_pin,OUTPUT);

	showText('O','P','E','N'); delay(3000);

  int x=9512;
   
  showText(x/1000, x%1000/100, x%100/10, x%10); 
  
  //showText((n/1000)%10+10, (n/100)%10, (n/10)%10, n%10);

  wait(3000);

} 
 
int n;
unsigned long start=millis();
byte b = 0;

void loop(){

	showDisplay();

	if(b==0){
		b++;
		wait(1000);    
	} else{
			if ( millis() > (prev + waitMS)) {
				showText((n/1000)%10+10,(n/100)%10,(n/10)%10,n%10); 
				n++;
				if(n>10000) {
					n=0;
				}
				wait(100);
			}
	}
  
}

void showText(char a, char b , char c,char d){
	disp_c[0] = d;
	disp_c[1] = c;
	disp_c[2] = b;
	disp_c[3] = a;
}

void showDisplay(){
	setDisp();
	for(int i=0; i<8; i++) {
		setDigit(i,disp[i]);
	}
}

void setDigit(int dig, int character){
	int digits[]= {128,64,32,16,8,4,2,1};

	//character set (0-9)0-9
	//            (10-19)0.-9.
	//            (20-45)A-Z
	//            (46-71)a-z
	//            (72)- (73) space
	int characters[]= {
	3,159,37,13,153,73,65,31,1,9,2,158,36,12,152,72,64,30,0,8,
	17,1,99,3,97,113,67,145,243,135,145,227,85,19,3,49,25,115,73,31,129,129,169,145,137,37,
	5,193,229,133,33,113,9,209,247,143,81,227,85,213,197,49,25,245,73,225,199,199,169,145,137,37,253,255};

	digitalWrite(RCLK_pin, LOW);
	shiftOut(DIO_pin, SCLK_pin, LSBFIRST, characters[character]);
	shiftOut(DIO_pin, SCLK_pin, LSBFIRST, digits[dig]);
	digitalWrite(RCLK_pin, HIGH);
}

void setDisp(){
	for (int i=0; i<8;i++) {
		int val = disp_c[i];
		if((val >= 32)&&(val <= 47)){ 
			switch (val){
				case 45 :
					val = 72;
					break;  
				default :
					val = 73;
					break;  
			}
		} else if((val >= 48)&&(val <= 57)){ //0-9
			val -= 48;
		}
		else if((val >= 65)&&(val <= 90)){ //A-Z
			val -= 45;
		}
		else if((val >= 97)&&(val <= 122)){ //a-z
			val -= 51;
		}
		disp[i] = val;
	}
}   

void wait( unsigned long milsec){
	prev = millis();
	waitMS = milsec;
}

#endif


#if 0
//控制碼2

const int RCLK = 7; //RCLK 
const int SCLK = 6; //SCLK
const int DIO = 5;  //DIO

char disp_c[8] ;

byte value[] ={ B11000000, // 0
                B11111001, // 1
                B10100100, // 2
                B10110000, // 3
                B10011001, // 4
                B10010010, // 5
                B10000010, // 6
                B11111000, // 7
                B10000000, // 8
                B10010000, // 9
                B01000000, // 0.
                B01111001, // 1.
                B00100100, // 2.
                B00110000, // 3.
                B00011001, // 4.
                B00010010, // 5.
                B00000010, // 6.
                B01111000, // 7.
                B00000000, // 8.
                B00010000, // 9.
                B10111111, // -
                B11111111};// display nothing

byte digit[] ={ B00000000,
                B00000001, // left segment
                B00000010,
                B00000100,
                B00001000,
                B00010000,
                B00100000,
                B01000000,
                B10000000}; // right segment

void setup() {
	Serial.begin(9600);
	pinMode(SCLK, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(DIO, OUTPUT);
}

void loop(){
	//sign(1);  
	//disp(2,15);
	//disp(3,6);
  showText('A','B','C','D');
}

void showText(char a, char b , char c,char d){
  disp_c[0] = d;
  disp_c[1] = c;
  disp_c[2] = b;
  disp_c[3] = a;
}

void disp(int d , int num ){          //透過本動作函數 disp( 位數， 數字 ); 依序顯示
	digitalWrite(RCLK,LOW);
	shiftOut(DIO,SCLK,MSBFIRST,B11111111); // select all segments
	shiftOut(DIO,SCLK,MSBFIRST,B11111111); // display nothing
	digitalWrite(RCLK,HIGH); 

	digitalWrite(RCLK,LOW);
	// select the fourth segment from left
	shiftOut(DIO,SCLK,MSBFIRST,value[num]); 
	shiftOut(DIO,SCLK,MSBFIRST,digit[5-d]);  
	digitalWrite(RCLK,HIGH);
}

void sign(int d ){                            //透過本動作函數 sign( 位數 ) ; 加上負號
	digitalWrite(RCLK,LOW);
	shiftOut(DIO,SCLK,MSBFIRST,B11111111); // select all segments
	shiftOut(DIO,SCLK,MSBFIRST,B11111111); // display nothing
	digitalWrite(RCLK,HIGH); 

	digitalWrite(RCLK,LOW);
	// select the fourth segment from left
	shiftOut(DIO,SCLK,MSBFIRST,value[20]);  
	shiftOut(DIO,SCLK,MSBFIRST,digit[5-d]); 
	digitalWrite(RCLK,HIGH);
}
#endif
