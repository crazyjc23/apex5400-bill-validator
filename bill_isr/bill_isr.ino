/*developed by julius placido
 * january 28, 2017
 * email: simple.gui2018gmail.com
 * info:
 * sample program for apex5400 bill acceptor using ISR
 * "developed by students by student"
 * pin config
 * apex 5400:
 * pin 1: low level credit line output
 * pin 4: dc power ground
 * pin 11: dcc power 12 volts
 * opto coupler pc817:
 * pin1 to +12volts pull_up with 1k ohm resistor
 * pin 2 to pin 1 of apex 5400 bill validator
 * pin 3 to arduino ground
 * pin 4 to arduino digital pin 18
 * note** base on my experience it is better to connect the ground pin of the 12 volts
 * supply to arduino only if you are using bill validator with a coin collector :D
 */
int pulse = 18;
volatile int state = HIGH;
volatile int pulse_count = -1;
unsigned long last_change = millis();
int total=0;

int new_peso = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pulse, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulse), bill_ISR, CHANGE );
}
void bill_ISR() {
  //state = !state;
  pulse_count = pulse_count + 1;
  last_change = millis();
}
void loop() {
  unsigned long int now = millis();
  Serial.print(" raw_value: ");
  Serial.print(pulse_count);
  if ( (now - last_change) > 1000) {
    //Serial.print("reset");
    if ((pulse_count / 2) == 20) {
      Serial.print(" 20");
      new_peso=20;
      pulse_count = 0;
    }
    if ((pulse_count / 2) == 50) {
      Serial.print(" 50");
      new_peso=50;
      pulse_count = 0;
    }
    if ((pulse_count / 2) == 100) {
      Serial.print(" 100");
      new_peso=100;
      pulse_count = 0;
    }
    //add more condition as required

  }
  if(new_peso>1){
    total=total+new_peso;
    new_peso=0;
  }
    Serial.print(" new_value:");
    Serial.print(new_peso);
    Serial.print(" total_value: ");
    Serial.println(total);

}
