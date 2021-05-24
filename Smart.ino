/**
 * Proyecto Electronica para Ciencias
 * Juan Sebastian Rodriguez Paez - 201812327
 * Maria Sofia Alvarez Lopez - 201729031
 */


String readString;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(6, OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
Serial.println("Texto");

}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available()){
  delay(3);
  char c = Serial.read();
  readString+=c;
}

if(readString.length() >0)
{
  Serial.println(readString);
  
  if(readString == "prende cocina")
  {
  digitalWrite(7, HIGH);
  }
 else if(readString == "apaga cocina")
  {
  digitalWrite(7, LOW);
  }
  else if(readString == "prende alcoba")
  {
  digitalWrite(6, HIGH);
  }
  else if(readString == "apaga alcoba")
  {
  digitalWrite(6, LOW);
  }
  else if(readString == "prende comedor")
  {
  digitalWrite(9, HIGH);
  }
  else if(readString == "apaga comedor")
  {
  digitalWrite(9, LOW);
  }
  else if(readString == "prende sala")
  {
  digitalWrite(8, HIGH);
  }
  else if(readString == "apaga sala")
  {
  digitalWrite(8, LOW);
  }
  else if(readString == "prende todo")
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }
  else if(readString == "apaga todo")
  {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  readString = "";
}
}
