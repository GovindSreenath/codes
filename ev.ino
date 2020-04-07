#define sensorPin A1
#define valvePin 1
#define solenoidPin1 2
#define solenoidPin2 3
int analogOutputRange[2] = {0, 1023};
int sensorReading;

void setup() {
  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);  
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); //Use an LED to Check ValveLogic
  pinMode(sensorPin, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  digitalWrite(solenoidPin1, HIGH);    //Switch Solenoid1 ON
  digitalWrite(solenoidPin2, LOW);    ////Switch Solenoid2 OFF
  delay(1000);                      //Wait 1 Second
  digitalWrite(solenoidPin1, LOW);     //Switch Solenoid1 OFF
  digitalWrite(solenoidPin2, HIGH);    //Switch Solenoid2 ON
  delay(1000); 
  
  sensorReading = analogRead(sensorPin); //Values from 0 to 1023
  calculatePascal(sensorReading);
  delay(500);
}

void calculatePascal(float reading){
  //Assuming VCC and Vout in scale of 0 to 1
  float actualPascalOutput = ((reading/analogOutputRange[1]) - 0.1)/0.75;
  float  covertedPsiOutput = pascalToPsiCoversion(actualPascalOutput);
  //if(actualPascalOutput <=0){
  //  actualPascalOutput = 0;  
  //}
  checkExecuteValve(actualPascalOutput, covertedPsiOutput);
  printPressure(actualPascalOutput, covertedPsiOutput);
}

float pascalToPsiCoversion(float pascal){
  return pascal * 145.037738; //1MPa = 145.037738Psi
}


void printPressure(float pascal, float psi){
  Serial.print(pascal);
  Serial.print("MPa ");
  Serial.print(psi);
  Serial.print("Psi");
  Serial.println("");
}

void checkExecuteValve(float pascal, float psi){
  if (pascal <= 0.0233){
    digitalWrite(sensorPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Turned On Valve");
  }
  if (pascal >= 0.0333){
    digitalWrite(sensorPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Turned Off Valve");
  }
  
}
