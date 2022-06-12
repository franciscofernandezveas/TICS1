//Codigo para ph, con luces led en protoboard
//Conexiones en Arduino: rojo en 5V, negro en GND, azul en A1

#include <DFRobot_PH.h>
#include <EEPROM.h>


#define PH_PIN A1
float voltage, phValue, temperature = 25; 
DFRobot_PH ph; 
int ledacido = 3;
int ledneutro = 2;
int ledalcalino = 4; 
void setup() {
  pinMode(ledacido, HIGH);
  pinMode(ledneutro, HIGH);
  pinMode(ledalcalino, HIGH);
  digitalWrite(ledacido , LOW);
  digitalWrite(ledneutro , LOW);
  digitalWrite(ledalcalino , LOW);


  Serial.begin(115200);
  ph.begin();
}

void loop() {
  static unsigned long timepoint = millis();
  if(millis() - timepoint > 1000U){ //intervalo de tiempo: ls
    //
    timepoint = millis();
    voltage = analogRead(PH_PIN)/ 1024.0*5000;

   
    phValue = ph.readPH(voltage,temperature);
    Serial.print("temepratura:");
    Serial.print(temperature,1);
    Serial.print("^C");
    
    phValue = ph.readPH(voltage,temperature);
    Serial.print("ph:");
    Serial.println(phValue,2);
      if(phValue>6.8&&phValue<15){
        digitalWrite(ledacido,LOW);
        digitalWrite(ledneutro, LOW);
        digitalWrite(ledalcalino, HIGH);
      }
      if(phValue>5.1&&phValue<6.79){
      digitalWrite(ledacido,LOW);
      digitalWrite(ledneutro, HIGH);
      digitalWrite(ledalcalino, LOW);
     }
     if(phValue>0&&phValue<5){
      digitalWrite(ledacido,HIGH);
      digitalWrite(ledneutro, LOW);
      digitalWrite(ledalcalino, LOW);
      }
    }
    ph.calibration(voltage,temperature);
}
