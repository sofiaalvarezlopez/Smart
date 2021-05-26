int televisor = 8;
int radio = 9;

//Representa el texto leído por el módulo Bluetooth desde la aplicación en AppInventor.
String readString;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(televisor, OUTPUT);
  pinMode(radio,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
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
}

void prender_y_apagar(String texto){
  int voltaje = texto.startsWith("prende") ? HIGH : LOW;
  
  if(texto.endsWith("televisor"))
  {
  digitalWrite(televisor, voltaje);
  }
  else if(texto.endsWith("radio"))
  {
  digitalWrite(radio, voltaje);
  }
  else if(texto.endsWith("todo"))
  {
    digitalWrite(televisor, voltaje);
    digitalWrite(radio, voltaje);
  }
  readString = "";
}
