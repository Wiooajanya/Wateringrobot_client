/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "wioopikings";           // SSID of your home WiFi
char pass[] = "wiooadmin@9090"; // password of your home WiFi



/* WIFI settings */



/* define L298N or L293D motor control pins */

int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */



int rightMotorForward = 0; /* GPIO0(D3) -> IN4   */
int sensor1= 14;
int sensor2=12;
int flag1=0;
int flag2=0;
int s1=0;
int s2=0;
int s3=0;




unsigned long askTimer = 0;

IPAddress server1(192,168,1,80);// the fix IP address of the server
IPAddress server2(192,168,1,81);
IPAddress server3(192,168,1,83);
WiFiClient client;
void linefollower()
{
    delay(10);
  if(digitalRead(sensor1)==0&&digitalRead(sensor2)==0)
  {

  digitalWrite(leftMotorForward,HIGH);

  digitalWrite(rightMotorForward,HIGH);
  }
   if(digitalRead(sensor1)==1&&digitalRead(sensor2)==0)
  {

  digitalWrite(leftMotorForward,HIGH);

  digitalWrite(rightMotorForward,LOW);
  }
   
  

 
if(digitalRead(sensor1)==0&&digitalRead(sensor2)==1)
{
  digitalWrite(leftMotorForward,LOW);

  digitalWrite(rightMotorForward,HIGH);
}

  
 

 if(digitalRead(sensor1)==1&&digitalRead(sensor2)==1)
 {

  digitalWrite(leftMotorForward,LOW);

  digitalWrite(rightMotorForward,LOW);
  s1=0;
  s2=0;
  s3=0;
  
 }
  }



void setup() {
   pinMode(leftMotorForward, OUTPUT);

  pinMode(rightMotorForward, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  digitalWrite(leftMotorForward,LOW);

  digitalWrite(rightMotorForward,LOW);
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("wifi..");
    delay(500);
  }
 Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  pinMode(ledPin, OUTPUT);
}

void loop ()
{
  //server1
  if(s1==0&&s2==0&&s3==0)
  {
  client.connect(server1, 80);   // Connection to the server
  Serial.println("helloi");
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  String answer1 = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server1: " + answer1);
  if(answer1=="1")
  {
    s1=1;
  }
  client.flush();
  }
  //server2
  /*client.connect(server2, 80);   // Connection to the server
  Serial.println("helloi");
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  String answer2 = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server2: " + answer2);
  /*if(answer2=="1")
  {
    s2=1;
  }
  client.flush();
  //server3
   client.connect(server3, 80);   // Connection to the server
  Serial.println("helloi");
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  String answer3 = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server3: " + answer3);
  //if(answer3="1")
 // {
   // s3=1;
 // }
  client.flush(); 
  }*/
  
  
  if(s1==1||s2==1||s3==1) //check any one of the server requests for water
  {
    
    while(digitalRead(sensor1)==1&&digitalRead(sensor2)==1)
    {
      delay(10);
      Serial.println("GET");
      digitalWrite(leftMotorForward,HIGH);
      digitalWrite(rightMotorForward,HIGH);
      
    }
     digitalWrite(leftMotorForward,LOW);
     digitalWrite(rightMotorForward,LOW);

  }
  while(s1==1||s2==1||s3==1)
  {
     delay(10);
     Serial.println("iam");
     linefollower();
    
     

  }
  }

 
