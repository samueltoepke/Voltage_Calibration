// Samuel Lee Toepke
// samueltoepke@gmail.com
// Spring 2015
// Voltage_Example.pde: A voltage sensor for the Max32 to show analog calibration. Uses a standard voltage divider
//   to get voltage from 0V to ~12V. R1 = 4.7k, R2 = (1k+330). http://en.wikipedia.org/wiki/Voltage_divider

float v_in       = 0.0;
float v_in_cal   = 0.0;
float v_out      = 0.0;
float v_sens     = 0.0;

float R1         = 4700.0; 
float R2         = 1330.0; 

float max_v      = 3.3; 
int   resolution = 1024.0; //10 bit ADC resolution...2^10 == 1024.

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  
  // 1. Get voltage from ADC.
    v_out    = analogRead(A0);
  
  // 2. Convert voltage per uC resolution and maximum input voltage.
    v_sens   = v_out * max_v / resolution;
    
  // 3. Apply voltage divider.
    v_in     = v_sens * ((R1+R2)/R2);

  // 4. Calibrate.
    float slope_modifier  = 0.9791; 
    float offset_modifier = 0.0667; 
    v_in_cal = (v_in * slope_modifier) + offset_modifier;
  
  // 5. Display the result.
    Serial.println("********************");
    Serial.println("Input Voltage:");
    Serial.println(v_sens);
    Serial.println("Calibrated Voltage:");
    Serial.println(v_in_cal);
  
  // 6. Delay execution for 1000 ms.
    delay(1000); 
}
