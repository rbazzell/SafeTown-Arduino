#define CLK 16
#define DT  15
#define SW  2
#define LED 22

int counter = 0;
int currStateCLK;
int lastStateCLK;
String currDir = "CW";
unsigned long lastButtonPress = 0;
String output = "";

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.begin(9600);

  lastStateCLK = digitalRead(CLK);
  while(!Serial); //wait for serial to connect
  Serial.println("START");
}

void loop() {
  currStateCLK = digitalRead(CLK);
  if (currStateCLK != lastStateCLK && currStateCLK == 1) {
    if (digitalRead(DT) != currStateCLK) {
      counter --;
      currDir = "CCW";
    } else {
      counter ++;
      currDir = "CW";
    }
    output = "Direction: " + String(currDir) + " | Counter: " + String(counter);
    Serial.println(output);
    lastStateCLK = currStateCLK;
  }
  delay(5);
  if(currDir == "CW") {
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(LED, LOW);
    }

  int btnState = digitalRead(SW);

  if (btnState == HIGH) {
      if (millis() - lastButtonPress > 50) {
          Serial.println("Button pressed!");
      }
      lastButtonPress = millis();
  }
}
