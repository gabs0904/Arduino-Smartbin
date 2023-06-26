
#include<Servo.h>
const int trigPin = 9;//Trig pin na 9
const int echoPin = 10;//Echo pin na 10
const int trigPin1 = 11;
const int echoPin1 = 12;
const int servoPin = 3;//Servo motor na pin 3

long duration;
int distance;
long duration1;
int distance1;
int Dist;int pos = 0; 
Servo Servo_Motor;

int sound_sensor = A0;    // Assign to pin A0
int threshold = 85;       // Sound threshold value
int servoPin1 = 4;         // Servo motor pin
int servoAngle = 120;      // Angle to rotate the servo
int initialAngle = 90;     // Initial angle of the servo

Servo servoMotor1;





int MeasureDistance();


void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    Servo_Motor.attach(servoPin);
    servoMotor1.attach(servoPin1); 
    Serial.begin(9600);
}

void loop()
{
     digitalWrite(trigPin, LOW);
     delayMicroseconds(2);
     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     distance = duration * 0.034 / 2; 
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

   digitalWrite(trigPin1, LOW);
     delayMicroseconds(2);
     digitalWrite(trigPin1, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigPin1, LOW);
     duration1 = pulseIn(echoPin1, HIGH);
     distance1 = duration1 * 0.034 / 2; 
    Serial.print("Distance1: ");
    Serial.print(distance1);
    Serial.println(" cm");

   Servo_Motor.detach(); // Detach the Servo_Motor before soundcheck
  soundcheck();
  Servo_Motor.attach(servoPin); // Reattach the Servo_Motor after soundcheck


      if (distance < 30 )// if distance is less than 30cm and the bin isn't full
      {
        if(distance1>5){
            //open ();
         
             Servo_Motor.write(95);  
            
           delay (1000);
        }
      }
      else
      {
        //close(); 
        
         Servo_Motor.write(0);  
       
        
        delay(500);  
      }  
}

void open ()
{
   Servo_Motor.attach(servoPin); 
   Servo_Motor.write(90);  
   delay(1000);
   Servo_Motor.detach();     
}  

void close()
{
   Servo_Motor.attach(servoPin);
   Servo_Motor.write(5);  
   delay(1000);
   Servo_Motor.detach();     //mozhe treba da go trgnam
    
}

void soundcheck(){
   int soundValue = 0;             // Variable to store multiple readings

  for (int i = 0; i < 32; i++)    // Read the sound sensor multiple times
  {
    soundValue += analogRead(sound_sensor);
  }

  soundValue >>= 5;               // Calculate average by bitshifting

  Serial.println(soundValue);     // Print the value of the sound sensor

  if (soundValue > threshold)     // If sound level exceeds the threshold
  {
    // Rotate the servo motor to the specified angle
    servoMotor1.write(180);
    delay(1000);                  // Wait for 1 second

    // Return the servo motor to its initial position
    servoMotor1.write(initialAngle);
    delay(500);                  // Wait for 1 second
  }

  delay(50);                      // A shorter delay between readings
}
