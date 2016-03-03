#include <Ultrasonic.h>
#include <With_Filter.h>

Ultrasonic example (11,12);
With_Filter example1(11,12);
void setup() {
  Serial.begin(9600);
}

void loop() {
  
 long a = pulseIn(2, HIGH, 4350);
  
 long timing = example.timing();
 example.convert(&timing,1);
 double filter = example1.filter(0.7,&timing);
 example1.digital_result();
 example1.after_filter_cm();
 example1.after_filter_in();

 
 Serial.print("time : ");
 Serial.print(timing);
 Serial.print(",");
 Serial.print("Convertion : ");
 Serial.print( example.convert(&timing,1));
 Serial.print(",");
 Serial.print("Filter : ");
 Serial.print(filter);
 Serial.print(",  ");
 Serial.println(a);
 delay(500);

}
