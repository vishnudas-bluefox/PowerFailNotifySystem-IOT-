/*
  vishnudas
  github: https://github.com/vishnudas-bluefox
  portfolio: http://vishnudasbluefox.co/
  ZMPT101B - AC Voltage sensor
  Calculate Voltage and write to serial port
*/

// initialize the variables
double sensorValue1 = 0;
double sensorValue2 = 0;
int crosscount = 0;
int climb_flag = 0;
int val[100];
int max_v = 0;
int ledGreen = 12;
int ledRed = 13;
double VmaxD = 0;
double VeffD = 0;
double Veff = 0;

// initialize the serial port
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  // intialize the leds
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed,OUTPUT);
}
// read the voltage from the sensor and calculate the effective voltage and write to serial port
void loop() {

  for ( int i = 0; i < 100; i++ ) {
    sensorValue1 = analogRead(A0);
    if (analogRead(A0) > 511) {
      val[i] = sensorValue1;
    }
    else {
      val[i] = 0;
    }
    delay(1);
  }

  max_v = 0;

  for ( int i = 0; i < 100; i++ )
  {
    if ( val[i] > max_v )
    {
      max_v = val[i];
    }
    val[i] = 0;
  }
  if (max_v != 0) {


    VmaxD = max_v;
    VeffD = VmaxD / sqrt(2);
    Veff = (((VeffD - 420.76) / -90.24) * -210.2) + 210.2;
  }
  else {
    Veff = 0;
  }

    if(Veff >60 && Veff < 100){
      Veff = 0;
  }
//  for see the voltage uncomment the below lines
//Serial.print("Voltage: ");
// Serial.println(Veff);
  VmaxD = 0;

  delay(1000);
 
  if (Veff==0){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    Serial.write('n');

  }
  else if(Veff>200){
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
  }
}
