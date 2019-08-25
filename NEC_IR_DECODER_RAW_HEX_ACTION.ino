#define irKeyOne    0x00FF30CF
#define irKeyTwo    0x00FF18E7
#define irKeyThree  0x00FF7A85
#define irKeyInc    0x00FFA857
#define irKeyDec    0x00FFE01F
#define irKeyPlay   0x00FFC23D

const int irPin = 2;
const int relay1Pin = 3;
const int relay2Pin = 4;
const int relay3Pin = 5;
unsigned int m;
unsigned int dTime;
unsigned int irTimeStamp[50];
uint32_t irKeyCode = 0;
boolean isToggle = false;
boolean relay1Flag, relay2Flag, relay3Flag;

void setup() 
{
//  Serial.begin(9600); 
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(irPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(irPin), irPulse, FALLING);
  relay1Flag = relay2Flag = relay3Flag = true;
}

void loop() 
{
  if (m > 0) 
  { 
    m = 0;
    for (int n = 1; n < 33; n++)
    {
      dTime = irTimeStamp[n + 1] - irTimeStamp[n];
      if (dTime > 1100 && dTime < 1200)
        irKeyCode = irKeyCode << 1;
      else if (dTime > 2200 && dTime < 2300)
        irKeyCode = (irKeyCode << 1) | 1;
    }
//    Serial.println(irKeyCode, HEX);
    if (irKeyCode == irKeyOne)
    {
      digitalWrite(relay1Pin, relay1Flag);
      relay1Flag = !relay1Flag;
    }
    else if (irKeyCode == irKeyTwo)
    {
      digitalWrite(relay2Pin, relay2Flag);
      relay2Flag = !relay2Flag;
    }
    else if (irKeyCode == irKeyThree)
    {
      digitalWrite(relay3Pin, relay3Flag);
      relay3Flag = !relay3Flag;
    }
    else if (irKeyCode == irKeyInc)
    {
      digitalWrite(relay1Pin, HIGH);
      digitalWrite(relay2Pin, HIGH);
      digitalWrite(relay3Pin, HIGH);
      relay1Flag = relay2Flag = relay3Flag = false;
    }
    else if (irKeyCode == irKeyDec)
    {
      digitalWrite(relay1Pin, LOW);
      digitalWrite(relay2Pin, LOW);
      digitalWrite(relay3Pin, LOW);
      relay1Flag = relay2Flag = relay3Flag = true;
    }
    else if (irKeyCode == irKeyPlay)
      isToggle = !isToggle;  
    irKeyCode = 0;
  }
  if(isToggle)
  {
    digitalWrite(relay1Pin, relay1Flag);
    digitalWrite(relay2Pin, relay2Flag);
    digitalWrite(relay3Pin, relay3Flag);
    relay1Flag = !relay1Flag;
    relay2Flag = !relay2Flag;
    relay3Flag = !relay3Flag;
  }
  delay(1000);
}

void irPulse() 
{
  irTimeStamp[m++] = micros();
}