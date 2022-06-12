
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobot_PH.h>
#include <EEPROM.h>

//PH
#define PH_PIN A1
float voltage, phValue, temperature = 25; 
DFRobot_PH ph; 

// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 13;
//Volumen
const int PinTrigVol = 7;
const int PinEchoVol = 6;

//bomba y sensor de proximidad.
int PinTrigBomba = 9;
int PinEchoBomba = 10;
int Relay = 4;
int TiempoBomba;
int DistanciaBomba;

// Constante velocidad sonido en cm/s
const float VelSon = 34000.0;
 
float distancia;
// Distancia a los 100 ml y vacío
const float distancia100 = 1.49;
//const float distanciaVacio = 15.32;
const float distanciaVacio = 14.77;

 
// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
 
void setup() {
    // Iniciamos la comunicación serie
    Serial.begin(115200);
    // Iniciamos el bus 1-Wire
    sensorDS18B20.begin();
  
    pinMode(PinTrigVol, OUTPUT);
    // Ponemos el pin Echo en modo entrada
    pinMode(PinEchoVol, INPUT);

    pinMode(PinTrigBomba, OUTPUT);
    pinMode(PinEchoBomba, INPUT);
    pinMode(Relay, OUTPUT);
    ph.begin();
}
 
void loop() {
    // Mandamos comandos para toma de temperatura a los sensores
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print("Temperatura: ");
    Serial.println(sensorDS18B20.getTempCByIndex(0));


    iniciarTrigger();

   // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
    unsigned long tiempo = pulseIn(PinEchoVol, HIGH);
    
    // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
    // por eso se multiplica por 0.000001
    distancia = tiempo * 0.000001 * VelSon / 2.0;
  Serial.print(distancia);
    Serial.print("cm");
    Serial.println();
    delay(500);
 
    float distanciaLleno = distanciaVacio - (distancia - 4.54);
    float cantidadLiquido = distanciaLleno * 100 / distancia100;
   if(cantidadLiquido > 1000){
        cantidadLiquido = cantidadLiquido/1000;
        Serial.print(cantidadLiquido);
        Serial.println(" Litros");
        delay(500);
    }
    if(distancia > 14.57 and distancia < 14.75){
        Serial.println("0 ml");
        delay(500); 
    }
    else{
      Serial.print(cantidadLiquido);
      Serial.println(" ml");
      delay(500);   
    }
    
    digitalWrite(PinTrigBomba, HIGH);
    delay(1);
    digitalWrite(PinTrigBomba, LOW);
    TiempoBomba = pulseIn(PinEchoBomba, HIGH);
    DistanciaBomba = TiempoBomba/58.2;
    //Serial.print("Distancia gato: " );
    //Serial.println(DistanciaBomba);
    if (10 > DistanciaBomba){
      digitalWrite(Relay, HIGH);
    }
    else{
      digitalWrite(Relay, LOW);
    }


    static unsigned long timepoint = millis();
    if(millis() - timepoint > 1000U){ //intervalo de tiempo: ls
    //
    timepoint = millis();
    voltage = analogRead(PH_PIN)/ 1024.0*5000;

   
    //phValue = ph.readPH(voltage,temperature);
    
    phValue = ph.readPH(voltage,temperature);
    Serial.print("ph:");
    Serial.println(phValue,2);
    }
    ph.calibration(voltage,temperature);
    
    delay(1000);
}

void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrigVol, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrigVol, HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrigVol, LOW);
}
