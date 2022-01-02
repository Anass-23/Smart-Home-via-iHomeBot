
// --- Python --- //
  unsigned int dada; // Variable "dada" és on es guradaran els valors rebuts des de Python

  
// --- Llums --- //

   //Menjador - Cuina
    int led2 = A0; 
    int led3 = A1;
    int led4 = A2;
    int led5 = A3;

   //Pasasdís
    int led1 = A4;
    int led6 = A5;
    
   //Habitació 1
    int led7 = A6;
    int led8 = A7;
   
   //Bany
    int led9 = A8;
    int led10 = A9;
           
   //Habitació 2
    int led11 = A10;
    int led12 = A11;
    int led13 = A12;
    
   //Exterior
    int led14 = 2;   //A13 ==> Sensor LDR
    int led15 = 3;   //A14 ==> Sensor DHT
    int led16 = 4;   //A15 ==> ?

// ---------- Timbre ---------- //

   const int boto_timbre = 5;
   const int timbre = 6;

// ---------- Sensor LDR (Lluminositat) ---------- //
    const int ldr = A13;
  
// ---------- Sensor DHT11 (Temperatura i Humitat) ---------- //
  #include <DHT.h>
    const int sensorDHT = A14;
    int temperatura, humitat;
    DHT dht(sensorDHT, DHT11); //Objecte amb les variables definides anteriorment.


// ---------- Teclat 4x4 ---------- //
  #include <Keypad.h>
  #include <Password.h>
  
    Password password = Password( "123A" ); //Definim la nostra contrasenya
    
    const byte FILES = 4; // Quatre Files
    const byte COLUMNES = 4; // Quatre Columnes
// Definimos el Keymap
    char tecles[FILES][COLUMNES] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

    byte filesPins[FILES] = { 21, 20, 19, 18};// Conectar Columnes [ROW1, ROW2, ROW3 y ROW4] als pins
    byte columnesPins[COLUMNES] = { 17, 16, 15, 14};// Conectar Files [COL1, COL2, COL3 y COL4] als pins

    Keypad keypad = Keypad( makeKeymap(tecles), filesPins, columnesPins, FILES, COLUMNES );


// --- Sensor IR --- //
  #include <IRremote.h>
    const int receptorIR = 10;
    IRrecv irrecv(receptorIR);
    decode_results Codis;
 

  // --- Servos ---  //
  #include <Servo.h>
    Servo Porta_Exterior;
    Servo Porta_Interior;
 
  // ---------- Sensor PIR (Moviment) ---------- //
    const int pir = 9;


// --- Motors pas a pas  --- //
  #include "Stepper.h"
    int voltes = 2048;  //--> 1 Volta = 2048
    const int PASSOS = 35;
    
    Stepper motor_menj_1 (PASSOS, 48, 47, 46, 45); // In1, In2, In3, In4 en una seqüència de 1-3-2-4
    Stepper motor_menj_2 (PASSOS, 44, 43, 42, 41 );
      int mem_menjador = 0;
      
    Stepper motor_passadis (PASSOS, 40, 39, 38, 37);
      int mem_passadis = 0;
      
    Stepper motor_hab_1 (PASSOS, 36, 35, 34, 33);
      int mem_hab_1 = 0;
      
    Stepper motor_hab_2 (PASSOS, 32, 31, 30, 29);
      int mem_hab_2 = 0;
      
    Stepper motor_garatge (PASSOS, 28, 27, 26, 25);
      int mem_garatge = 0;
    


// --- Sensor RFID ( Ocupa els pins --> 53, 52, 51, 50, --, [GND], 49, [3.3V] ) --- //
  #include <SPI.h>
  #include <MFRC522.h>
  const int SS_PIN = 53; // *#define*
  const int RST_PIN = 49; // *#define*
  MFRC522 RFID (SS_PIN, RST_PIN); //Objecte amb les variables definides anteriorment.

//-------------------------------------------- Accions Programades --------------------------------------------//
  void setup() {
    Serial.begin (9600);
    SPI.begin();
    
  // -- Sensors -- //
    pinMode(ldr, INPUT); // LDR --> Llum --> A13
    pinMode(pir, INPUT);  // PIR --> Sensor de Moviment --> 9
    irrecv.enableIRIn(); // Control IR --> Infraroigos --> 10
    RFID.PCD_Init();     // RFID --> Magnètic -->
    dht.begin ();        // DHT11 --> Humitat && Temperatura -->
    
  // -- Llums -- //
    pinMode(led2,OUTPUT);   // --> A0
    pinMode(led3,OUTPUT);   // --> A1
    pinMode(led4,OUTPUT);   // --> A2
    pinMode(led5,OUTPUT);   // --> A3
    
    pinMode(led1,OUTPUT);   // --> A4
    pinMode(led6,OUTPUT);   // --> A5
    
    pinMode(led7,OUTPUT);   // --> A6
    pinMode(led8,OUTPUT);   // --> A7
    
    pinMode(led9,OUTPUT);   // --> A8
    pinMode(led10,OUTPUT);  // --> A9
    
    pinMode(led11,OUTPUT);  // --> A10
    pinMode(led12,OUTPUT);  // --> A11
    pinMode(led13,OUTPUT);  // --> A12
    
    pinMode(led14,OUTPUT);  // --> 2 
    pinMode(led15,OUTPUT);  // --> 3 
    pinMode(led16,OUTPUT);  // --> 4

  // -- Timbre -- //
    pinMode(boto_timbre, INPUT); // Polsador --> 5
    pinMode(timbre, OUTPUT);     // Buzzer --> 6

  // -- Teclat Matricial (4x4) -- //
    keypad.addEventListener(keypadEvent);
    // Servo en funció del teclat
    Porta_Exterior.attach(7);   // Exterior --> 7
    Porta_Interior.attach(8);   // Interior --> 8

  }
 
  void loop() { 

// -------------- AUTOMATITZACIÓ DES DE PYTHON -------------- //
    
    while (Serial.available()>0){  // Comprobem que la comunicació derial estigui disponible
       
       dada = Serial.read();
     
// ----------- Exterior (Pati) ----------- //
      if(dada == 'A') {             //Obrir Porta Exterior
          Porta_Exterior.write(90);
                     break;
      }

      
      if(dada == 'B') {              //Tancar Porta Exterior
          Porta_Exterior.write(0);
      }


      if (mem_garatge != 1){       //Obrir Porta Garatge
        if (dada == 'C'){
          
          motor_garatge.setSpeed(500);
            motor_garatge.step(voltes);
          
          mem_garatge = 1;
       }
    }

      if (mem_garatge != 0){        //Tancar Porta Garatge   
        if (dada == 'D'){
            
        motor_garatge.setSpeed(500);
           motor_garatge.step(-voltes);
        
        mem_garatge = 0;
       }
    }
    
      if(dada == 'E') {                     //Encendre Llums Entrada
        digitalWrite (led14, HIGH);
          digitalWrite (led15, HIGH);
            digitalWrite (led16, HIGH);
      }
      if(dada == 'F') {                     //Apagar Llums Entrada
        digitalWrite (led14, LOW);
          digitalWrite (led15, LOW);
            digitalWrite (led16, LOW);
      }

// ----------- Passadís ----------- // 
      if(dada == 'G') {                      //Encendre Llums Passadís
        digitalWrite (led1, HIGH);
          digitalWrite (led6, HIGH);
      } 
      if(dada == 'H') {                      //Apagar Llums Passadís
        digitalWrite (led1, LOW);
          digitalWrite (led6, LOW);
      }
      
      
      if (mem_passadis != 0){                //Pujar Persiana Passadís
        if (dada == 'I')
        motor_passadis.setSpeed(500);
          motor_passadis.step(voltes);
            delay(500);
        
        mem_passadis = 0;
        }
      }             
        if (mem_passadis != 1){             //Baixar Persiana Passadís
          if(dada == 'J') {
        motor_passadis.setSpeed(500);
          motor_passadis.step(-voltes);
            delay(500);
            
        mem_passadis = 1;
        }
      }

// ----------- Menjador ----------- //
      if(dada == 'K') {                     //Encendre Llums Menjador
        digitalWrite (led2, HIGH);
        digitalWrite (led3, HIGH);
        digitalWrite (led4, HIGH);
        digitalWrite (led5, HIGH);
      }
      if(dada == 'L') {                     //Apagar Llums Menjador
        digitalWrite (led2, LOW);
        digitalWrite (led3, LOW);
        digitalWrite (led4, LOW);
        digitalWrite (led5, LOW);
      }

      if (mem_menjador != 0){
      if(dada == 'M') {                     //Pujar Persianes Menjador
        motor_menj_1.setSpeed (500);
          motor_menj_2.setSpeed (500);
        motor_menj_1.step(voltes);
          motor_menj_2.step(voltes);

        mem_menjador = 0;
      }
      }
      if (mem_menjador != 1){
      if(dada == 'N') {                     //Baixar Persianes Menjador
        motor_menj_1.setSpeed (500);
          motor_menj_2.setSpeed (500);
        motor_menj_1.step(-voltes);
          motor_menj_2.step(-voltes);

        mem_menjador = 1;
      }
      }

// ----------- Habitació 1 ----------- //
      if(dada == 'O') {                     //Encendre Llums Habitació 1
        digitalWrite (led7, HIGH);
        digitalWrite (led8, HIGH);
      }
      if(dada == 'P') {                     //Apagar Llums Habitació 1
        digitalWrite (7, LOW);    
        digitalWrite (8, LOW);
      }

      if (mem_hab_1 != 0){
        if(dada == 'Q') {                    //Pujar Persianes Habitació 1
        motor_hab_1.setSpeed(500);
          motor_hab_1.step(voltes);
          
        mem_hab_1 = 0;
      }
      }
      if (mem_hab_1 != 1){
        if(dada == 'R') {                    //Pujar Persianes Habitació 1
        motor_hab_1.setSpeed(500);
          motor_hab_1.step(voltes);
          
        mem_hab_1 = 1;
      }
      }

// ----------- Habitació 2 ----------- //      
      if(dada == 'S') {                    //Encendre Llums Habitació 2
        digitalWrite (11, HIGH);
        digitalWrite (12, HIGH);
        digitalWrite (13, HIGH);
      }
      if(dada == 'T') {                    //Apagar Llums Habitació 2
        digitalWrite (11, LOW);
        digitalWrite (12, LOW);
        digitalWrite (13, LOW);
      }

      if (mem_hab_2 != 0){
      if(dada == 'U') {                    //Pujar Persianes Habitació 2
        motor_hab_2.setSpeed(500);
          motor_hab_2.step(voltes);

        mem_hab_2 = 0;
        }
      }
      if (mem_hab_2 != 1){
      if(dada == 'V') {                    //Baixar Persianes Habitació 2
        motor_hab_2.setSpeed(500);
          motor_hab_2.step(-voltes);

        mem_hab_2 = 1;
        }
      }

      


  //Sensors  
        
      if (dada =='W') {             //Enviar Temperatura 
         float temperatura = dht.readTemperature();
          Serial.println (temperatura + String("°C"));
        }

  //Enviar Humitat
      if (dada =='X'){             //Enviar Humitat
         float humitat = dht.readHumidity();
          Serial.println (humitat + String("%"));
        }

       

// ----------------------------- AUTOMATITZACIÓ DES D'ARDUINO ----------------------------- //

     char eKey = keypad.getKey(); //Variable en funcio de keypadEvent
    
  // --------------------- Receptor IR ----------------------- //
  
      if (irrecv.decode(&Codis))  {
      switch (Codis.value)  {

        // ----- Llums ----- //
          case 0xFF30CF:                             // Passadís (Button 1)
    
             if (digitalRead(led1) and digitalRead(led6)) { 
                    digitalWrite(led1, LOW);
                      digitalWrite(led6, LOW);
                    }
                else{
                     digitalWrite(led1, HIGH);
                      digitalWrite(led6, HIGH);
                     }

                    break;
                                                               
          case 0xFF18E7:                             // Menjador (Button 2)

              if (digitalRead(led2) and digitalRead(led3) and digitalRead(led4) and digitalRead(led5)) { 
                    digitalWrite(led2, LOW);
                      digitalWrite(led3, LOW);
                        digitalWrite(led4, LOW);
                          digitalWrite(led5, LOW);
                    }
                else{
                     digitalWrite(led2, HIGH);
                      digitalWrite(led3, HIGH);
                        digitalWrite(led4, LOW);
                          digitalWrite(led5, LOW);
                     }
                          
                          break;
         
          case 0xFF7A85:                             // Habitació 1 (Button 3)

              if (digitalRead(led7) and digitalRead(led8)) { 
                    digitalWrite(led7, LOW);
                      digitalWrite(led8, LOW);
                    }
                else{
                     digitalWrite(led7, HIGH);
                      digitalWrite(led8, HIGH);
                     }
                          
                          break;
            
          case 0xFF10EF:                             // Bany (Button 4)

              if (digitalRead(led9) and digitalRead(led10)) { 
                    digitalWrite(led9, LOW);
                      digitalWrite(led10, LOW);
                    }
                else{
                     digitalWrite(led9, HIGH);
                      digitalWrite(led10, HIGH);
                     }
                          
                          break;
                          
           case 0xFF38C7:                             // Habitació 2 (Button 5)

              if (digitalRead(led11) and digitalRead(led12) and digitalRead(led13)) { 
                    digitalWrite(led11, LOW);
                      digitalWrite(led12, LOW);
                        digitalWrite(led13, LOW);
                    }
                else{
                     digitalWrite(led11, HIGH);
                      digitalWrite(led12, HIGH);
                        digitalWrite(led13, LOW);
                     }   
                          
                          break;

                
    // ----- Motor Garatge ----- //       
          case 0xFF906F:                              // Botó Pujar
          
            if (mem_garatge != 0){
               motor_garatge.setSpeed(500);
               motor_garatge.step(voltes);           
                mem_garatge = 0;
                      break;
            }
                      
          case 0xFFE01F:                              // Botó Baixar
          
            if (mem_garatge != 1){
               motor_garatge.setSpeed(500);
               motor_garatge.step(-voltes);           
                mem_garatge = 1;
                      break;        
            }
      delay(150);
      irrecv.resume();
    }
  }


  // --------------------- RFID ----------------------- //
  
    if ( ! RFID.PICC_IsNewCardPresent()) { //Comprova si hi ha alguna targeta nova
      return;
  }       
  // Select one of the cards
    if ( ! RFID.PICC_ReadCardSerial()) { // Selecciona una targeta
      return;
  }
  
    String valor= "";
    byte letter;
    for (byte i = 0; i < RFID.uid.size; i++) 
    
  {
     valor.concat(String(RFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
     valor.concat(String(RFID.uid.uidByte[i], HEX));
  }
  
  valor.toUpperCase();
  
  if (valor.substring(1) == "0E 0D B3 73") // Targetes amb accès
  {
   motor_garatge.setSpeed(500);
    motor_garatge.step(voltes);
    delay (5000);
    motor_garatge.step(-voltes);
  }
 
  if (valor.substring(1) == "10 F0 8F A6") {  // Accés porta entrada exterior
  Porta_Exterior.write(90);
  delay (5000);
  Porta_Exterior.write(0);
  }
}

void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
  switch (eKey){
    case '*': checkPassword(); break;
   
    case '#': {
      digitalWrite (10, HIGH);
      digitalWrite (11, LOW);
      delay(1000);
      Porta_Interior.write (0);
      break;
    }
    default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Porta_Interior.write (90);
    Serial.println ("Success");
    password.reset();
  
  }else{
    delay (1000);
    Porta_Interior.write (0);
    Serial.println ("Denied");
    password.reset();
  }
}

