#define USE_ALB_LCD_I2C // LCD Library

#include "ArduinoLearningBoard.h"

ALB_LCD_I2C lcd;

byte step1[] = {
  B00000,
  B00110,
  B00111,
  B00110,
  B11110,
  B11110,
  B01010,
  B01001
};

byte step2[] = {
  B00110,
  B00111,
  B00110,
  B11110,
  B11110,
  B01010,
  B10010,
  B00000
};

byte cactus[] = {
  B00100,
  B00101,
  B00101,
  B10101,
  B10110,
  B10100,
  B01100,
  B00100
};

byte blank[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

int vibccnt = 1;
int btn = 13;
const int vib = 11;
int btnst = 0; 

int walk = 1;
int speed = 100;
int move = 1; // moving[1], no cactus[0]

int jmp = 1; // down[1], up[0]
int jmpst = 0;

int ppos = 15;
int i = 15;

int sct = 0; //not selected[0], selected[1]
int no = 0;
int score = 0;
int hscore = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 6000;
  unsigned long currentMillis = 0;
  unsigned long previousjmp = 0;        



void setup()
{
  pinMode(btn, INPUT_PULLUP);
    pinMode(vib, OUTPUT);

	lcd.init(); // Initialize the LCD
	lcd.clear(); // Clear the LCD (set cursor to 0, 0)
	lcd.backlight(); // Turn on the LCD backlight
	lcd.print("DINO JUMP"); // Print "Arduino Learning" on the first line
//	lcd.setCursor(5, 1); // Move the cursor to (x, y)  (y=1 is 2nd line)
//	lcd.print("Board!"); // Print "Board!" in the middle of the 2nd line
	
    lcd.createChar(0, step1);
    lcd.createChar(1, step2);
    lcd.createChar(2, cactus);
        lcd.createChar(3, blank);


	delay(3000); // Wait 3 seconds
	lcd.clear(); // Clear Display
  move = 1;
 
 start();
}
void run(){
  lcd.setCursor(3, jmp);

 walk = !walk;
 if(walk == 1){
    lcd.write(byte(0));
 }else if(walk == 0){
    lcd.write(byte(1));
 }
 delay(speed);

 score ++;
 if(score > hscore){
   hscore = score;
 }
}

void start(){
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.write(byte(1));

  for(int p = 3; p > 0; p--){
   lcd.setCursor(14, 0);
   lcd.print(p);
   delay(1000);
  }
  lcd.clear();
 score = 0;
 vibccnt = 1;

 //digitalWrite(vib, LOW);

}

void cmove(int pos){

 if(move == 1){
   ppos = pos + 1;
   lcd.setCursor(ppos, 1);
   lcd.write(byte(3));
   lcd.setCursor(pos, 1);
   lcd.write(byte(2));

   if(i <= 0){
     move = 0;
     lcd.setCursor(0, 1);
     lcd.write(byte(3));
    }
   i = i - 1;
 }
}

void over(){

if(vibccnt == 1){
   for(int vibcnt = 0; vibcnt < 3; vibcnt++){
     digitalWrite(vib, HIGH);
     delay(100);
     digitalWrite(vib, LOW);
     delay(100);
     vibccnt = 0;

    }
  }
 //digitalWrite(vib, HIGH);
  // delay(500);
  lcd.setCursor(0, 0);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.print("/ ");
    lcd.print(hscore);

    lcd.setCursor(12, 1);
    lcd.print("GAME ");
    delay(1000);
    lcd.setCursor(12, 1);
    lcd.print("OVER");



    //digitalWrite(vib, HIGH);
    delay(1000);


}

void loop()
{
  	//lcd.setCursor(5, 1); // Move the cursor to (x, y)  (y=1 is 2nd line)
  jmpst = digitalRead(btn);
  currentMillis = millis();
 
 if (sct == 0){
    no = random(1000,5000);
    sct = 1;
  }
  //interval = no;

  if(currentMillis - previousMillis >= no && move == 0){
    i = 15;
    move = 1;
    previousMillis = currentMillis;
  }


  if(jmpst == LOW){
    jmp = 0;
    lcd.setCursor(3, 1);
    lcd.write(byte(3));
  }
  if(jmp == 0 && currentMillis - previousjmp >= 1000 ){
    previousjmp = currentMillis;
    jmp = 1;
    lcd.setCursor(3, 0);
    lcd.write(byte(3));
  }

  
  
 
 while (jmp == 1 && i == 3){
   /*
   lcd.setCursor(11, 0);
    lcd.print("GAME");
    lcd.setCursor(11, 1);
    lcd.print("OVER");
    */
    jmpst = digitalRead(btn);
    if(jmpst == LOW){
      start();
      break;

    }

    over();
 }
 cmove(i);
 run();
}
 