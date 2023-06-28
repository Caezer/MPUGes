
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int ENA = 3;
int ENB = 9;
int MotorA1 = 4;
int MotorA2 = 5;
int MotorB1 = 6;
int MotorB2 = 7;

RF24 radio(8, 10);

const byte address[6] = "00001";

/*struct data {
  String pitch;
  String roll;

};
data receive_data;*/
float roll;
float pitch;



void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
radio.begin();
radio.openReadingPipe(0,address);
radio.setPALevel(RF24_PA_MIN);
radio.setDataRate(RF24_250KBPS);
radio.startListening();
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);
pinMode(MotorA2, OUTPUT);
pinMode(MotorB1, OUTPUT);
pinMode(MotorB2, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly 
 while(radio.available()) {
    float rpitchr[2];
    radio.read(&rpitchr, sizeof(rpitchr));
    roll = rpitchr[0];
    pitch = rpitchr[1];
    //Serial.println("received");
    Serial.println(roll);
    Serial.println(pitch);
 if(roll > 40) {
  Serial.println("Forward");
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
}else if(pitch > 40) {
  Serial.println("Left");
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
} else if(roll < -40){
  Serial.println("Backward"); 
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else if(pitch < -40){
  Serial.println("Right");
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  }
 }
}
