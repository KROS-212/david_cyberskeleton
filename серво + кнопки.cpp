#define dataPin  10  // пин подключен к входу DS
#define latchPin 11  // пин подключен к входу ST_CP
#define clockPin 12  // пин подключен к входу SH_CP

int pos = 500;
int incomingByte = 0;
int left_pos = 0;
int right_pos = 0;
int old_pos = 0;

void setup() {
	pinMode(6, OUTPUT);  //right_pos
	pinMode(7, OUTPUT);  //left_pos
	Serial.begin(9600);
   // устанавливаем режим работы пинов OUTPUT
   pinMode(latchPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
   pinMode(dataPin, OUTPUT);
   // ставим HIGH на "защёлку", чтобы регистр не принимал сигнал
   digitalWrite(latchPin, HIGH);
   
}

void loop() {
	
  
digitalWrite(latchPin, LOW);                                        // ставим LOW на "защёлку"
shiftOut(dataPin, clockPin, LSBFIRST, B00000000); // отправляем байт в двоичном виде
digitalWrite(latchPin, HIGH);	
	if (digitalRead(6) == HIGH || digitalRead(7) == HIGH) 
	{
		if (digitalRead(6) == HIGH) {right_pos = 1;}
		if (digitalRead(7) == HIGH) {left_pos = 1;}
		if (pos < 400) {pos = 400;}
		if (pos > 2300) {pos = 2300;}
		Serial.print("move: ");Serial.println(pos, DEC);Serial.print(" - ");Serial.println(pos, DEC);
		//for (int i=1;i<=180;i++){        
			  digitalWrite(latchPin, LOW);                                        // ставим LOW на "защёлку"
			  shiftOut(dataPin, clockPin, LSBFIRST, B11111111); // отправляем байт в двоичном виде
			  digitalWrite(latchPin, HIGH);
          delayMicroseconds(pos);
			  digitalWrite(latchPin, LOW);                                        // ставим LOW на "защёлку"
			  shiftOut(dataPin, clockPin, LSBFIRST, B00000000); // отправляем байт в двоичном виде
			  digitalWrite(latchPin, HIGH);
          delayMicroseconds(20000-pos);
          delay(1);
		  pos = pos + right_pos*10 - left_pos*10;
		//}
		//old_pos = pos + right_pos*10 - left_pos*10;
		//pos=0;
		right_pos = 0;
		left_pos = 0;
    }
}