#define PIR 5 // GPIO05, Digital Pin D1
#define LED 4 // GPIO04, Digital Pin D2

void setup()
{
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  int trigger = digitalRead(PIR);

  if (trigger)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  delay(500);
}