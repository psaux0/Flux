#define AVOLTAGE 4.60

int ledPin = 8;
int ledState = LOW;
int sensorState = 0;
char c;
int t;
float s;

void setup()
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  Serial.begin(9600);
}

void loop()
{
  t = analogRead(2);
  s = (t*AVOLTAGE/1024.0-0.5)*100;
  while(Serial.available()){
    c = Serial.read();
    if(c == '1')
    {
      ledState = HIGH;
    }
    if(c == '0')
    {
      ledState = LOW;
    }
    if(c == '2')
    {
      Serial.println(s);
    }
    if(c == '3')
    {
      sensorState = 1;
    }
    if(c == '4')
    {
       sensorState = 0;
    }
  }
  if (sensorState) {
    if( s > 30 ) ledState = LOW;
    if( s < 15 ) ledState = HIGH;
  }
  digitalWrite(ledPin,ledState);
}
