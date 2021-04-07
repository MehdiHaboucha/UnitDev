/*
**Programme Test CLX2-433-19 Action Recepteur
**SmarTracker
**Anass Ouadif
*/

#define THRESHOLD 400 
int BUFFER = 0;              // Variable reception série
int compteur = 0;            // Variable compteur
int Accuse = 0;              // Variable accusé de reception
int etat=0;                  // Variable etat du bouton
int state = -1; //-1 idle, 0 just pushed, 1 just released
unsigned long millisStart;
boolean longPush;
void Reagir() {
  state = digitalRead(2);
}


void setup() {
  Serial.begin(19200);     // Configure débit à 19200 bauds 
  attachInterrupt(0, Reagir, CHANGE);
  pinMode(2, INPUT_PULLUP); //Configure port 2 en sortie Bouton  
  pinMode(4, OUTPUT);      // Configure port 4 en sortie LED 1W  
  digitalWrite(4, LOW);    // LED 1W OFF
  pinMode(6, OUTPUT);      // Configure port 6 en sortie Sirene  
  digitalWrite(6, LOW);    // Sirene OFF
  pinMode(5, OUTPUT);      // port 5 en sortie LED (Module)
  digitalWrite(5, LOW);    // LED OFF
  delay(500);              // Tempo 
}

void loop() {

  if (state == 0) {
    state = -1;
    millisStart = millis();
  }
  if  (state == 1) {
    state = -1;
    longPush = (millis() - millisStart) > THRESHOLD;
    if(longPush){
        Accuse=0;
       digitalWrite(4, LOW);    // LED OFF
       digitalWrite(5, LOW);    // LED OFF
       digitalWrite(6, LOW);    // Sirene OFF
    }else{
       Accuse=0;
       if (Accuse == 0) 
       {
          Serial.write(23);             // Envoi ordre à l'autre CLX2 
          delay(1000);                  // Tempo 1 sec
       }

    }
  }
     if (Serial.available() > 0) // As t'on reçu un ordre ?
   {  
      BUFFER = Serial.read();       // lit l'octet arrivé
      if (BUFFER == 23) 
      {
          Serial.write(99);        //Envoie d'accusé de reception
          digitalWrite(6, HIGH);   // Sirene ON 
          while(compteur<10)        //Pendant 10 sec
          {        
            digitalWrite(4, HIGH);   // LED ON 
            delay(700);              //Pendant 0.7 sec         
            digitalWrite(4, LOW);    // LED OFF
            delay(300);              //Pendant 0.3 sec 
            compteur++;
          }
          digitalWrite(6, LOW);   // Sirene OFF 
      }
      if (BUFFER == 99)
      {
          digitalWrite(5, HIGH);            // LED ON
          Accuse++;
          delay(5000);                  // Tempo 5 sec
          digitalWrite(5, LOW);            // LED OFF
      }
  }

}
