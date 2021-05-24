/**
 * Smart: Proyecto Electronica para Ciencias
 * Juan Sebastian Rodriguez Paez - 201812327
 * Maria Sofia Alvarez Lopez - 201729031
 */

 /*
  * Variables Globales
  */

//Representa el pin D6 del Arduino. En este caso, conectado a la alcoba.
int alcoba = 6;
//Representa el pin D7 del Arduino. En este caso, conectado a la cocina.
int cocina = 7;
//Representa el pin D8 del Arduino. En este caso, conectado a la sala.
int sala = 8;
//Representa el pin D8 del Arduino. En este caso, conectado al comedor.
int comedor = 9;
//Representa el texto leído por el módulo Bluetooth desde la aplicación en AppInventor.
String readString;

// put your setup code here, to run once:
void setup() {
  
Serial.begin(9600);
//Cada PIN corresponde a una señal de salida: 0V o 5V para prender/apagar el relé.
pinMode(alcoba, OUTPUT);
pinMode(cocina,OUTPUT);
pinMode(sala,OUTPUT);
pinMode(comedor,OUTPUT);

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
  Serial.println(readString);
  prender_y_apagar(readString);
}
}

void prender_y_apagar(String texto){
  int voltaje = texto.startsWith("prende") ? HIGH : LOW;
  
  if(texto.endsWith("alcoba"))
  {
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
