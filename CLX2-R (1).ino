// Programme donne a titre d'exemple. A utiliser dans le cadre d'une initiation aux modules Arduino™
// l utilisation commerciale de ce programme est interdite). Lextronic decline toute responsabilite en
// cas de prejudice resultant de l'utilisation de cette note d'application.
 
int BUFFER = 0;          // Variable reception série
int etat = 0;            // Variable d'état de la Led
   
void setup() {
  Serial.begin(19200);     // Configure débit à 9600 bauds
  pinMode(5, OUTPUT);     // Configure port 5 en sortie 
  digitalWrite(5, LOW);  // Eteind la Led
  delay(500);            // Tempo 
}
void loop() {
  
 if (Serial.available() > 0) { // As t'on reçu un ordre ?
   BUFFER = Serial.read();   // lit l'octet arrivé
    if (BUFFER == 80) {
     
   switch (etat) {
     case 0:    // Led précédement éteinte
        digitalWrite(5, HIGH);   // Active la Led
        Serial.write(82);        // Envoi accusé de réception à l'autre CLX2 (Led allumée) 
        etat = 1;                // Change l'état de la variable de l'état de la Led 
        break;
  case 1:    // your hand is close to the sensor
        digitalWrite(5, LOW);   // Active la Led
        Serial.write(81);        // Envoi accusé de réception à l'autre CLX2 (Led teinte) 
        etat = 0;               // Change l'état de la variable de l'état de la Led 
        break;
  } 
delay(50);            // Tempo 
} 
} 
}


