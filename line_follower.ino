//Motors
int motorR = 8;
int motorL = 7;
//Analog Pins
int analogR = 1;
int analogL = 0;
//ADvalReaders
int ADvalL = 0; // A/D value
int ADvalR = 1; // A/D value
//Voltage into the car
int Vin = 5; // reference voltage
//Voltage out from left and right motor
float VoutL = 0; 
float VoutR = 0; 
//Resistor used for ground in photoresistor
float R2 = 10000;
//Photoresistor Resistances
float R1L = 0; 
float R1R = 0;
//Left and right temp Buffers
float bufferL = 0; 
float bufferR = 0; 
// setup function
void setup()
{
Serial.begin(9600);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(analogR, INPUT);
  pinMode(analogL,INPUT);
}
// infinite loop function
void loop()
{
  //See values for left and right wheel
ADvalL = analogRead(analogL); 
ADvalR = analogRead(analogR); 

if(ADvalL && ADvalR)//Once both can read start doing calculations
{
//Left Side
Serial.print("ADval Left: ");
Serial.println(ADvalL);
bufferL = ADvalL * Vin;//Left Buffer
VoutL = (bufferL)/1024.0; // 10 bit AD conversion to get Vmeasured
bufferL = VoutL/5;//Reverse Voltage Expression Divide Vout by 5V
bufferL = bufferL/R2;//Storing temp data to solve for R1(Ohms on left side)
bufferL = 1.0/bufferL; 
R1L = bufferL - R2; 
Serial.print("Vout Left: "); 
Serial.println(VoutL);
Serial.print("R1 Left: "); 
Serial.println(R1L);
Serial.println("\n");
//Right Side
Serial.print("ADval Right: "); //print AD value
Serial.println(ADvalR);
bufferR = ADvalR * Vin;
VoutR = (bufferR)/1024.0; // 10 bit AD conversion to get Vmeasured
bufferR = VoutR/5;//Reverse Voltage Expression Divide Vout by 5V
bufferR = bufferR/R2;//Storing temp data to solve for R1(Ohms on left side)
bufferR = 1.0/bufferR; 
R1R = bufferR - R2; 
Serial.print("Vout Right: ");
Serial.println(VoutR);
Serial.print("R1 Right: ");
Serial.println(R1R);
Serial.println("\n");
}
//Move forward and turn both motors on if both sensors see light
if(R1L < 2700 && R1R < 2700){
  digitalWrite(motorL, HIGH);
  digitalWrite(motorR, HIGH);
  delay(50);
  digitalWrite(motorL, LOW);
  digitalWrite(motorR, LOW);
}
//Turn Left
else if(R1L < 2700){
  digitalWrite(motorL, HIGH);
  delay(50);
  digitalWrite(motorL, LOW);
}
//Turn Right
else if(R1R < 2700){
  digitalWrite(motorR, HIGH);
  delay(50);
  digitalWrite(motorR, LOW);
}
delay(300);//delay to let get clear readings
}