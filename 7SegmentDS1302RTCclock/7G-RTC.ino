/*
UNO DS1302
2   CLK
3   DAT
4   RST
5V  VCC
GND GND

UNO MAX7219
10  CS
11  CLK
12  DIN
5V  VCC
GND GND
*/


//#include <RTClib.h>
#include <LedControl.h>
//=======================================================================================
// data pin, clock, latch
// CONNECTIONS:
// DS1302 CLK/SCLK --> 2
// DS1302 DAT/IO --> 3
// DS1302 RST/CE --> 4
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(3,2,4); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

double hold;

LedControl lc = LedControl(12, 11, 10, 1);
//RTC_DS1307 rtc;

//========================================================================================

void setup() {

  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  } 
    

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

  
//	rtc.begin();
	lc.shutdown(0, false);
	lc.setIntensity(0, 8); // display brightness
	lc.clearDisplay(0); // erase display
//	rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //set clock as computer clock
//	rtc.adjust(DateTime(2020, 4, 16, 3, 0, 0));

}

//========================================================================================
void loop() {
	hold = millis();
	while ((hold + 20000) > millis() ) {
		//DateTime now = rtc.now();
   RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
   
   //Serial.println(DateTime);
		setCol3(now.Hour());
		setCol2(now.Minute());
		setCol1(now.Second());
		lc.setChar (0, 2, '-', false);
		lc.setChar (0, 5, '-', false);
	}

	hold = millis();
	while ((hold + 5000) > millis() ) {
		//DateTime now = rtc.now();
   RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
		setCol1(now.Day());
		setCol2(now.Month());
		setCol3(now.Year() - 2000);
		lc.setChar (0, 2, '-', false);
		lc.setChar (0, 5, '-', false);
	}
}
#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
//========================================================================================
void setCol1 (byte jam) {
	String strBuffer = Konversi(jam);
	byte pjg = strBuffer.length() + 1;
	char val[pjg];
	strBuffer.toCharArray(val, pjg);
	lc.setChar (0, 1, val[0], false);
	lc.setChar (0, 0, val[1], false);
}

//========================================================================================
void setCol2 (byte mnt) {
	String strBuffer = Konversi(mnt);
	byte pjg = strBuffer.length() + 1;
	char val[pjg];
	strBuffer.toCharArray(val, pjg);
	lc.setChar (0, 4, val[0], false);
	lc.setChar (0, 3, val[1], false);
}

void setCol3 (byte dtk) {
	String strBuffer = Konversi(dtk);
	byte pjg = strBuffer.length() + 1;
	char val[pjg];
	strBuffer.toCharArray(val, pjg);
	lc.setChar (0, 7, val[0], false);
	lc.setChar (0, 6, val[1], false);
}

String Konversi(int nilai) {
	if (nilai < 10) {
		return "0" + String(nilai);
	}
	else {
		return String(nilai);
	}
}
