/**
 * Smart: Proyecto Electronica para Ciencias
 * Juan Sebastian Rodriguez Paez - 201812327
 * Maria Sofia Alvarez Lopez - 201729031
 */

 /*
  * Variables Globales
  */
#include <SoftwareSerial.h> 
#include "dht.h"
SoftwareSerial bt(0,1); // RX, TX

//Representa el pin D6 del Arduino. En este caso, conectado a la alcoba.
int alcoba = 6;
//Representa el pin D7 del Arduino. En este caso, conectado a la cocina.
int cocina = 7;
//Representa el pin D8 del Arduino. En este caso, conectado a la sala.
int sala = 8;
//Representa el pin D8 del Arduino. En este caso, conectado al comedor.
int comedor = 9;
//Representa el pin D12 del Arduino, conectado al pin TRIG del sensor ultrasónico.
int trig = 12;
//Representa el pin D13 del Arduino, conectado al pin ECHO del sensor ultrasónico.
int echo = 13;
//Representa el pin D2 del Arduino, al que esta conectado el sensor tactil.
int tactil = 2;
//Representa el voltaje que hay en el comedor.
int voltaje_comedor = LOW;
//Representa el voltaje que hay en el cuarto.
int voltaje_cuarto = LOW;
//Representa el puerto A0 donde recibimos la informacion de temperatura y humedad.
int pin_datos = A0;
//Representa al sensor de humedad y temperatura y es una instancia de dht.
dht DHT;
//Representa la temperatura que medira el sensor DHT 11.
double temperatura;
//Representa la humedad que medira el sensor DHT 11.
double humedad;
//Contador temperatura
int contador_temp = 0;
//Contador proximidad
int contador_prox = 0;

//Representa el texto leído por el módulo Bluetooth desde la aplicación en AppInventor.
String readString;

// put your setup code here, to run once:
void setup() {
  
Serial.begin(9600);
bt.begin(9600);
//Cada PIN corresponde a una señal de salida: 0V o 5V para prender/apagar el relé.
pinMode(alcoba, OUTPUT);
pinMode(cocina,OUTPUT);
pinMode(sala,OUTPUT);
pinMode(comedor,OUTPUT);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(tactil,INPUT);
pinMode(pin_datos, INPUT);

}

void loop() {
//Lee cada caracter del texto traido por bluetooth y dicho por voz en la aplicación móvil.
while(Serial.available()){
  delay(3);
  char c = Serial.read();
  readString+=c;
}

if(readString.length() > 0)
{
  //Serial.println(readString);
  prender_y_apagar(readString);
}
long distancia = calcular_distancia_ultrasonico(trig, echo);
prender_cuarto_tactil(tactil,alcoba);

if (contador_prox == 100 || contador_prox == 0){
  prender_comedor_ultrasonico(distancia, comedor);
  contador_prox = 0;
}

if (contador_temp == 1000 || contador_temp == 0){
  medir_temperatura_humedad(pin_datos);
  contador_temp = 0;
}
contador_temp += 1;
contador_prox += 1;
}

// Esta parte corresponde a si decide prender o no según la condición que se le alimenta.
void prender_y_apagar(String texto){
  int voltaje = texto.startsWith("prende") ? HIGH : LOW;
  
  if(texto.endsWith("alcoba"))
  {
   voltaje_cuarto = voltaje;
  digitalWrite(alcoba, voltaje);
  }
  else if(texto.endsWith("cocina"))
  {
  digitalWrite(cocina, voltaje);
  }
  else if(texto.endsWith("comedor"))
  {
  digitalWrite(comedor, voltaje);
  }
  else if(texto.endsWith("sala"))
  {
  digitalWrite(sala, voltaje);
  }
  else if(texto.endsWith("todo"))
  {
    digitalWrite(alcoba, voltaje);
    digitalWrite(cocina, voltaje);
    digitalWrite(comedor, voltaje);
    digitalWrite(sala, voltaje);
  }
  readString = "";
}

// Parte del código para calcular la distancia medida por el sensor ultrasónico.
long calcular_distancia_ultrasonico(int trig, int echo){
  long dur;
  long dis;
  long tocm;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  dur=pulseIn(echo,HIGH);
  tocm= dur/29/2;
  //Serial.println(String(tocm));
  return tocm;
}

// Parte del código que decide prender o no el bombillo del comedor según la distancia que se calcula.
void prender_comedor_ultrasonico(long distancia, int comedor){
  if (distancia < 5){
    //Serial.println("entre");
  voltaje_comedor = voltaje_comedor == LOW ? HIGH : LOW;
  digitalWrite(comedor,voltaje_comedor);
}
}

// Parte del código asignada al sensor Touch
//Invierte el voltaje que haya: si se toca y está encendido, lo apaga y viceversa.
void prender_cuarto_tactil(int tactil, int cuarto){
  long tiempo = 0;
  long debounce = 200;
  int p = LOW;
  int medida = digitalRead(tactil);
  if (medida == HIGH && p == LOW && millis() - tiempo > debounce) {
    voltaje_cuarto = voltaje_cuarto == HIGH ? LOW : HIGH;
    tiempo = millis();   
    digitalWrite(cuarto, voltaje_cuarto); 
  }
  p = medida;
}

// Parte del código asignada a la medición de la temperatura y la humedad del ambiente. 
void medir_temperatura_humedad(int pin_datos){
  int leer_datos = DHT.read11(pin_datos);
  temperatura = DHT.temperature;
  humedad = DHT.humidity;
 Serial.print(temperatura); //send distance to MIT App
 Serial.print(";");
 Serial.print(humedad); //send distance to MIT App 
 Serial.println(";");
  
}
