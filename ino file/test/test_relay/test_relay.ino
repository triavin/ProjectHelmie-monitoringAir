// inisialisasi variabel relay

const int Relay1 = 4;
const int Relay2 = 5;
const int Relay3 = 6;
const int Relay4 = 7;
const int Relay5 = 8;
const int Relay6 = 9;
const int Relay7 = 10;

void setup() {
  // set pin mode to output

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Relay5, OUTPUT);
  pinMode(Relay6, OUTPUT);
  pinMode(Relay7, OUTPUT);

  relayOff();
}

void relayOnAndOff(){
  digitalWrite(Relay1, LOW);
  delay(3000);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, LOW);
  delay(3000);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, LOW);
  delay(3000);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, LOW);
  delay(3000);
  digitalWrite(Relay4, HIGH);
  digitalWrite(Relay5, LOW);
  delay(3000);
  digitalWrite(Relay5, HIGH);
  digitalWrite(Relay6, LOW);
  delay(3000);
  digitalWrite(Relay6, HIGH);
  digitalWrite(Relay7, LOW);
  delay(3000);
  digitalWrite(Relay7, HIGH);
}


void relayOff(){
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
  digitalWrite(Relay5, HIGH);
  digitalWrite(Relay6, HIGH);
  digitalWrite(Relay7, HIGH);
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  relayOnAndOff();
  delay(1000);
}
