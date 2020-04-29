#include <Wire.h>
#include <Servo.h>
#include <trajfactory.h>

// Address of slave.
#define SLAVE_ADDR 8

// Pin definitions.
#define SERVO_PIN 9

// Limits of servo.
#define SERVO_MIN 2400
#define SERVO_MAX 550

// Init trajectory generation and current pointer.
TrajFactory tf = TrajFactory();
Trajectory* traj_ptr = 0;

// Init servo class.
Servo servo;

// Init current ventilator params.
int rr;
float ie;
int setpoint;
float hold;
int delta_t;
char state;

void setup() {

  // Join i2c bus with address SLAVE_ADDR.
  Wire.begin(SLAVE_ADDR);

  // Register callback function for i2c receive.
  Wire.onReceive(recieveTraj);

  // Start serial output for trajectory monitoring.
  Serial.begin(9600);

  // Attach servo.
  servo.attach(SERVO_PIN);

  // Set state to off.
  state = 'X';
}

void loop() {
  // Run device in different modes.
  switch (state) {
    // immediate assist, push all the way with the current config, then continue as normal



    // Device is on, continue following trajectory.

    case 'O': 
      moveTo(traj_ptr->nextStep(), traj_ptr->getDeltaTime());
      //delay(100);
      break;
    

    // Device has been instructed to shutdown.
    case 'X':
      stop();
      break;


    // Device has recieved a new trajectory, load and start.
    case 'L':

      // Stop motion.
      stop();

      // If assigned ptr, delete contents
      if (traj_ptr != 0) {
        delete traj_ptr;
      }

      // Build new trajectory
      traj_ptr = tf.build(rr, ie, setpoint, hold, delta_t);

      // Set device on.
      state = 'O';
      break;
    
    case 'A':
        int cur_pos = traj_ptr->nextStep();
                 // Serial.println("-------");
        //Serial.println("cur_pos");
        //Serial.println(cur_pos);
        
        int next_pos;
        do{
          next_pos = traj_ptr->nextStep();
          //Serial.println("next_pos");
          //Serial.println(next_pos);
          //Serial.println("-------");
        } while((next_pos < cur_pos));
        moveTo(next_pos, traj_ptr->getDeltaTime());
        /*
      //skip all decreasing movements, get to the next push in movement
        int cur_pos;
        int next_pos = traj_ptr->nextStep();
        do{
          cur_pos = next_pos;
          next_pos = traj_ptr->nextStep();
        }while(cur_pos > next_pos);
       */
      //moveTo(SERVO_MIN+1, 1000);
      state = 'O';
      break;
    //case 'A':
      //stop();
      //break;

      /*
      int cur_pos = traj_ptr->nextStep();
      while(cur_pos > traj_ptr->nextStep() ){
        cur_pos = traj_ptr->nextStep();
      }
            break;
                  moveTo(traj_ptr->nextStep(), traj_ptr->getDeltaTime());
                  */



    
    /*
      //skip all decreasing movements, get to the next push in movement
      int cur_pos = traj_ptr->nextStep();
     while(cur_pos > traj_ptr->nextStep() ){
        cur_pos = traj_ptr->nextStep();
     }
     state = 'O';
     */
  }
}

void moveTo(int pos, int delta_t){

  // Write current position instruction to console.
  Serial.println(pos);

  // Move the servos to next setpoint and wait delta time.
  servo.writeMicroseconds(SERVO_MIN-pos);
  delay(delta_t);
}

void stop(){

  // If we have already generated a trajectory, follow it till the end.
  if (traj_ptr != 0) {
    while (traj_ptr->getCurrentStep() != 0) {
      moveTo(traj_ptr->nextStep(), traj_ptr->getDeltaTime());
    }
  // If not, got to 0 position.
  } else {
    moveTo(0, 100);
  }
}

void recieveTraj(int num_entries) {

  // Read the state from incoming transmission.
  char recieved_state = Wire.read();

  // Either change machine state or load new settings.
  switch (recieved_state) {
    case 'X':
      state = 'X';
      break;
    case 'A':
      state = 'A';
      break;
    case 'L':
      state = 'L';


      // Load new params
      byte high = Wire.read();
      byte low = Wire.read();
      setpoint = (high << 8) | low;

      rr = Wire.read();

      byte inhale = Wire.read();
      byte exhale = Wire.read();
      ie = float(inhale) / exhale;

      byte hold_s = Wire.read();
      byte hold_dec = Wire.read();
      hold = hold_s + hold_dec/100.0;

      delta_t = Wire.read();

      break;
  }
}
