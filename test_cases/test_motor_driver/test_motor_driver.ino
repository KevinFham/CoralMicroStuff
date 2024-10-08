// Define the control inputs
#define MOT_A1_PIN A3
#define MOT_A2_PIN A4
#define MOT_B1_PIN 5
#define MOT_B2_PIN 4

// Encoder pins
#define encoderPinA1 21
#define encoderPinA2 20
#define encoderPinB1 19
#define encoderPinB2 18


void setup(void)
{
  // Set all the motor control inputs to OUTPUT
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  // pinMode(MOT_B1_PIN, OUTPUT);
  // pinMode(MOT_B2_PIN, OUTPUT);

  // pinMode(encoderPinA1, INPUT);
  // pinMode(encoderPinA2, INPUT);
  // pinMode(encoderPinB1, INPUT);
  // pinMode(encoderPinB2, INPUT);

  // digitalWrite(encoderPinA1, HIGH);
  // digitalWrite(encoderPinA2, HIGH);
  // digitalWrite(encoderPinB1, HIGH);
  // digitalWrite(encoderPinB2, HIGH);

  // Turn off motors - Initial state
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  // digitalWrite(MOT_B1_PIN, LOW);
  // digitalWrite(MOT_B2_PIN, LOW);

  // Initialize the serial UART at 9600 baud
  Serial.begin(115200);
}

void loop(void)
{
  for(int i = 0; i < 255; i++){
    set_motor_pwm(i, MOT_A1_PIN, MOT_A2_PIN);
    Serial.print("="); Serial.println(i);
    delay(50);
  }
  // int a1 = digitalRead(encoderPinA1);
  // int a2 = digitalRead(encoderPinA2);
  // int b1 = digitalRead(encoderPinB1);
  // int b2 = digitalRead(encoderPinB2);

  // Serial.print(a1*5 , a2*5); 
  // Serial.print(b1*5 , b2*5); 


  // Generate a fixed motion sequence to demonstrate the motor modes.
  // Ramp speed up.
  // for (int i = 0; i < 11; i++) {
  //   spin_and_wait(25*i, 25*i, 1000);
  // }
  // // Full speed forward.
  // spin_and_wait(255,255,5000);

  // // Ramp speed into full reverse.
  // for (int i = 0; i < 21 ; i++) {
  //   spin_and_wait(255 - 25*i, 255 - 25*i, 1000);
  // }
  // spin_and_wait(0,0,2000);
  // Full speed reverse.
  // spin_and_wait(-255,-255,5000);

  // // Stop.
  // spin_and_wait(0,0,2000);

  // // Full speed, forward, turn, reverse, and turn for a two-wheeled base.
  // spin_and_wait(255, 255, 2000);
  // spin_and_wait(0, 0, 1000);
  // spin_and_wait(-255, 255, 2000);
  // spin_and_wait(0, 0, 1000);
  // spin_and_wait(-255, -255, 2000);
  // spin_and_wait(0, 0, 1000);
  // spin_and_wait(255, -255, 2000);
  // spin_and_wait(0, 0, 1000);
}

/// Set the current on a motor channel using PWM and directional logic.
///
/// \param pwm    PWM duty cycle ranging from -255 full reverse to 255 full forward
/// \param IN1_PIN  pin number xIN1 for the given channel
/// \param IN2_PIN  pin number xIN2 for the given channel
void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}

/// Set the current on both motors.
///
/// \param pwm_A  motor A PWM, -255 to 255
/// \param pwm_B  motor B PWM, -255 to 255
void set_motor_currents(int pwm_A, int pwm_B)
{
  set_motor_pwm(pwm_A, MOT_A1_PIN, MOT_A2_PIN);
  set_motor_pwm(pwm_B, MOT_B1_PIN, MOT_B2_PIN);

  // Print a status message to the console.
  Serial.print("Set motor A PWM = ");
  Serial.print(pwm_A);
  Serial.print(" motor B PWM = ");
  Serial.println(pwm_B);
}

/// Simple primitive for the motion sequence to set a speed and wait for an interval.
///
/// \param pwm_A  motor A PWM, -255 to 255
/// \param pwm_B  motor B PWM, -255 to 255
/// \param duration delay in milliseconds
void spin_and_wait(int pwm_A, int pwm_B, int duration)
{
  set_motor_currents(pwm_A, pwm_B);
  delay(duration);
}
