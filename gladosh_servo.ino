#include <Servo.h>    //dodanie biblioteki serwa
#include <Keypad.h>   //dodanie biblioteki keypad

Servo servo;          //zainicjowanie serwa
int pos = 0;          //zainicjowanie pozycji serwa na 0

/*  Zainicjowanie zmiennych dla macierzy dwuwymiarowej
 *  do odczytu przyciskow klawiaturki.
 *  Z klawiatury matrix 4x4 bedziemy uzywac tylko pierwszego 
 *  rzedu i trzech pierwszych kolumn klawiszy 1-3, by 
 *  zminimalizowac liczbe potrzebnych do uzycia pinow 
 *  Datasheet:
 *  https://www.parallax.com/sites/default/files/downloads/27899-4x4-Matrix-Membrane-Keypad-v1.2.pdf
 */
const byte ROW = 1;   
const byte COLS = 3;

char keys[ROW][COLS]={
  {'1', '2', '3'}
  };

byte rowPins[ROW] = {8};
byte colPins[COLS] = {7, 6, 5};

Keypad kpd= Keypad( makeKeymap(keys), rowPins, colPins, ROW, COLS);
 

void setup() {
  servo.attach(9);  //podepniecie obslugi serwa do pinu 9
  Serial.begin(9600); //okreslenie portu seryjnego na 9600
}

void loop() {
    char input = kpd.getKey(); //odczytanie wartosci z keypadu
 // char input = Serial.read(); //odczytanie wartosci wpisanej w konsoli portu seryjnego
  if(input) {
    switch(input){
      case '1':       //przy wcisnieciu 1 serwo porusza sie o 10 
        pos += 10;    //stopni w strone przeciwna do wskazowek zegara
        servo.write(pos);       
        break;
      case '2':       //przy wcisnieciu 2 serwo porusza sie o 10
        pos -= 10;    stopni w strone zgodna ze wskazowkai zegara
        servo.write(pos);          
        break;
      case '3':     //przy wcisnieciu 3 serwo wykonuje mala serie ruchow
        pos = 0;
        for (int i = 0; i < 3; i++){  
          pos += 15;
          servo.write(pos);
          delay(100);
          pos -= 3;
          servo.write(pos);
          delay(100);
        }
        pos += 30;
        servo.write(pos);
        delay(100);
        break;
      }
    }
}
