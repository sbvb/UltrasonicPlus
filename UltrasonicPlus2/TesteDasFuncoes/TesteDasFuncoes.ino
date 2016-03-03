#include <Ultrasonic.h>
#include <With_Filter.h>

Ultrasonic example (12,13);
With_Filter example1(12,13);
void setup() {
  Serial.begin(9600);
}

void loop() {
  
 long a = pulseIn(13, HIGH);
  
 long timing = example.timing();
 example.convert(1);
 example1.filter(0.7);
 example1.digital_result();
 example1.after_filter_cm();
 example1.after_filter_in();

 
 Serial.print("time : ");
 Serial.print(example.timing());
 Serial.print(",");
 Serial.print("Filter : ");
 Serial.print(example1.filter(0.7));
 Serial.print(",  ");
 Serial.println(a);
 delay(500);

}
