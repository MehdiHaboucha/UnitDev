// Programme donne a titre d'exemple. A utiliser dans le cadre d'une initiation aux modules Arduino™
// l utilisation commerciale de ce programme est interdite). Lextronic decline toute responsabilite en
// cas de prejudice resultant de l'utilisation de cette note d'application.

int BP = 1;                              // Initialise variable entree poussoir
    int BUFFER = 0;                     // Variable reception série
    void setup() {
      Serial.begin(19200);            // Configure débit à 9600 bauds
      pinMode(4, INPUT);              // Port 4 en entrée
      pinMode(5, OUTPUT);          // Configure port 5 en sortie 
      digitalWrite(5, LOW);           // Eteind la Led
      delay(500);                         // Tempo 
   }

   void loop() {
      BP = digitalRead(4);            // Lecture BP 
      if (BP == LOW) {                // Si on active le poussoir
         Serial.write(80);             // Envoi ordre à l'autre CLX2 
         delay(1000); 
   } 

   if (Serial.available() > 0) {    // As t'on reçu un accuse de réception ?
      BUFFER = Serial.read();   // lit l'octet arrivé
     if (BUFFER == 81) 
  {
  digitalWrite(5, LOW);             // Eteind la Led
  }
  if (BUFFER == 82) 
  {
  digitalWrite(5, HIGH);            // Allume la Led
  } 
  } 
  } 
