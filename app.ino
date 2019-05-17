#define PIR_SENSOR D1

void setup()
{
  pinMode(PIR_SENSOR, INPUT);
  pinMode(LED_BUILTIN, LOW);
}

void loop()
{
  if (PIR_SENSOR == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(500);
}
